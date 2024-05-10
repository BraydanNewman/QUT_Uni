#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <stdbool.h>
#include <errno.h>

typedef struct {
    char status; // 'O' for open, 'C' for closed, 'o' for opening, 'c' for closing
    pthread_mutex_t mutex;
    pthread_cond_t cond_start;
    pthread_cond_t cond_end;
} shm_door;

bool str_to_uint16(const char *str, uint16_t *res) {
    char *end;
    errno = 0;
    long val = strtol(str, &end, 10);
    if (errno || end == str || *end != '\0' || val < 0 || val >= 0x10000) {
        return false;
    }
    *res = (uint16_t) val;
    return true;
}

void sendMessage(int fd, const char *msg) {
//    printf("\nMEANT TO SEND %s\n", msg);
    int len = strlen(msg);
//    printf("\nMEANT TO SEND LENGTH %d\n", len);
    send(fd, msg, len, 0);
//    printf("\nACTUALLY SENT LENGTH %d\n", len);
//
//    if (actually_sent != len) {
//        fprintf(stderr, "\nsend did not send all data\n");
//        exit(1);
//    }
}

int main(int argc, char *argv[]) {
    bool door_state_lock = false;
    if (argc < 7) {
        fprintf(stderr,
                "Usage: {id} {address:port} {FAIL_SAFE | FAIL_SECURE} {shared memory path} {shared memory offset} {overseer address:port}\n");
        exit(1);
    }

//    Set up Arg Variables
    const char *id = argv[1];
    const char *fail_safe_config = argv[3];

    const char *shm_path = argv[4];
    int shm_offset = atoi(argv[5]);

    const char delim[2] = ":";

    const char *overseer_address = strtok(argv[6], delim);
    int overseer_port = atoi(strtok(NULL, delim));

    const char *listen_address = strtok(argv[2], delim);
    const char *listen_port_str = strtok(NULL, delim);
    int listen_port = atoi(listen_port_str);

//    Accept Messages
    int fd_listen = socket(AF_INET, SOCK_STREAM, 0);
    if (fd_listen == -1) {
        perror("socket()");
        return 1;
    }
    int opt_enable = 1;
    setsockopt(fd_listen, SOL_SOCKET, SO_REUSEADDR, &opt_enable, sizeof(opt_enable));
    setsockopt(fd_listen, SOL_SOCKET, SO_REUSEPORT, &opt_enable, sizeof(opt_enable));
    struct sockaddr_in addr_listen;
    memset(&addr_listen, 0, sizeof(addr_listen));
    addr_listen.sin_addr.s_addr = htonl(INADDR_ANY);
    addr_listen.sin_family = AF_INET;
    addr_listen.sin_port = htons(listen_port);
    if (bind(fd_listen, (struct sockaddr *) &addr_listen, sizeof(addr_listen)) == -1) {
        perror("bind()");
        return 1;
    }
    if (listen(fd_listen, 10) == -1) {
        perror("listen()");
        return 1;
    }


//    Send Message over TCP to Overseer
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
        perror("socket()");
        return 1;
    }
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    if (inet_pton(AF_INET, overseer_address, &addr.sin_addr) != 1) {
        perror("inet_pton");
    }
    addr.sin_family = AF_INET;
    addr.sin_port = htons(overseer_port);
    if (connect(fd, (struct sockaddr *) &addr, sizeof(addr)) == -1) {
        perror("connect()");
        return 1;
    }
    char contact_message[50];
    strcpy(contact_message, "DOOR ");
    strcat(contact_message, id);
    strcat(contact_message, " ");
    strcat(contact_message, listen_address);
    strcat(contact_message, ":");
    strcat(contact_message, listen_port_str);
    strcat(contact_message, " ");
    strcat(contact_message, fail_safe_config);
    strcat(contact_message, "#");
    sendMessage(fd, contact_message);
    shutdown(fd, SHUT_RDWR);
    close(fd);


    // Shared Memory
    int shm_fd = shm_open(shm_path, O_RDWR, 0);
    if (shm_fd == -1) {
        perror("shm_open()");
        exit(1);
    }
    struct stat shm_stat;
    if (fstat(shm_fd, &shm_stat) == -1) {
        perror("fstat()");
        exit(1);
    }
    char *shm = mmap(NULL, shm_stat.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm == MAP_FAILED) {
        perror("mmap()");
        exit(1);
    }
    shm_door *shared = (shm_door *) (shm + shm_offset);


    struct sockaddr client_addr;
    socklen_t client_addr_len;

    char current_door_status;

    const char CLOSE = 'C';
    const char OPEN = 'O';
    const char CLOSING = 'c';
    const char OPENING = 'o';


    for (;;) {
        pthread_mutex_lock(&shared->mutex);
        current_door_status = shared->status;
        pthread_mutex_unlock(&shared->mutex);

        char *msg;
        int client_fd = accept(fd_listen, &client_addr, &client_addr_len);
        if (client_fd == -1) {
            perror("accept()");
            return 1;
        }
        int len = 128;
        msg = malloc(len + 1);
        recv(client_fd, msg, len, 0);
        msg[len] = '\0';
        if (strcmp(msg, "OPEN#") == 0) {
            if (door_state_lock == false) {
                if (current_door_status == OPEN) {
                    sendMessage(client_fd, "ALREADY#");
                } else if (current_door_status == CLOSE) {

                    sendMessage(client_fd, "OPENING#");
                    pthread_mutex_lock(&shared->mutex);
                    shared->status = OPENING;
                    pthread_cond_signal(&shared->cond_start);
                    pthread_cond_wait(&shared->cond_end, &shared->mutex);
                    pthread_mutex_unlock(&shared->mutex);
                    sendMessage(client_fd, "OPENED#");
                }
            } else {
                sendMessage(client_fd, "SECURE_MODE#");
            }


        } else if (strcmp(msg, "CLOSE#") == 0) {
            if (door_state_lock == false) {
                if (current_door_status == CLOSE) {
                    sendMessage(client_fd, "ALREADY#");
                } else if (current_door_status == OPEN) {
                    sendMessage(client_fd, "CLOSING#");
                    pthread_mutex_lock(&shared->mutex);
                    shared->status = CLOSING;
                    pthread_cond_signal(&shared->cond_start);
                    pthread_cond_wait(&shared->cond_end, &shared->mutex);
                    pthread_mutex_unlock(&shared->mutex);
                    sendMessage(client_fd, "CLOSED#");
                }
            } else {
                sendMessage(client_fd, "EMERGENCY_MODE#");
            }
        } else if (strcmp(msg, "OPEN_EMERG#") == 0) {
            if (current_door_status == CLOSE) {
                door_state_lock = true;
                pthread_mutex_lock(&shared->mutex);
                shared->status = OPENING;
                pthread_cond_signal(&shared->cond_start);
                pthread_cond_wait(&shared->cond_end, &shared->mutex);
                pthread_mutex_unlock(&shared->mutex);
            }

        } else if (strcmp(msg, "CLOSE_SECURE#") == 0) {
            if (current_door_status == OPEN) {
                door_state_lock = true;
                pthread_mutex_lock(&shared->mutex);
                shared->status = CLOSING;
                pthread_cond_signal(&shared->cond_start);
                pthread_cond_wait(&shared->cond_end, &shared->mutex);
                pthread_mutex_unlock(&shared->mutex);
            }
        }
        shutdown(client_fd, SHUT_RDWR);
        close(client_fd);
        free(msg);
    }


}