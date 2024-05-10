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
    char scanned[16];
    pthread_mutex_t mutex;
    pthread_cond_t scanned_cond;

    char response; // 'Y' or 'N' (or '\0' at first)
    pthread_cond_t response_cond;
} shm_card_reader;

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
    int len = strlen(msg);
    if (send(fd, msg, len, 0) != len) {
        fprintf(stderr, "send did not send all data\n");
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 6) {
        fprintf(stderr,
                "Usage: {id} {shared memory path} {shared memory offset} {overseer address:port}\n");
        exit(1);
    }


    const char *id = argv[1];
//    int wait_time = atoi(argv[2]);
    const char *shm_path = argv[3];
    int shm_offset = atoi(argv[4]);
    const char delim[2] = ":";
    const char *address = strtok(argv[5], delim);
    const char *port = strtok(NULL, delim);


    // TCP Client
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
        perror("socket()");
        return 1;
    }
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    if (inet_pton(AF_INET, address, &addr.sin_addr) != 1) {
        perror("inet_pton");
    }
    uint16_t res;
    str_to_uint16(port, &res);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(res);
    // connect
    if (connect(fd, (struct sockaddr *) &addr, sizeof(addr)) == -1) {
        perror("connect()");
        return 1;
    }

    char contact_message[25];
    strcpy(contact_message, "CARDREADER ");
    strcat(contact_message, id);
    strcat(contact_message, " HELLO#");

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
    shm_card_reader *shared = (shm_card_reader *) (shm + shm_offset);


    pthread_mutex_lock(&shared->mutex);

    for (;;) {
        if (shared->scanned[0] != '\0') {
//            Read Scan Code into buffer
            char buff[17];
            memcpy(buff, shared->scanned, 16);
            buff[16] = '\0';

            char scanned_message[50];
            strcpy(scanned_message, "CARDREADER ");
            strcat(scanned_message, id);
            strcat(scanned_message, " SCANNED ");
            strcat(scanned_message, buff);
            strcat(scanned_message, "#");

//            Send Scanned Code to Overseer
            int fd = socket(AF_INET, SOCK_STREAM, 0);
            if (fd == -1) {
                perror("socket()");
                return 1;
            }
            struct sockaddr_in addr;
            memset(&addr, 0, sizeof(addr));
            if (inet_pton(AF_INET, address, &addr.sin_addr) != 1) {
                perror("inet_pton");
            }
            uint16_t res;
            str_to_uint16(port, &res);
            addr.sin_family = AF_INET;
            addr.sin_port = htons(res);
            // connect
            if (connect(fd, (struct sockaddr *) &addr, sizeof(addr)) == -1) {
                perror("connect()");
                return 1;
            }

            sendMessage(fd, scanned_message);

            int len = 10;
            char *resv_msg;
            resv_msg = malloc(len + 1);
            recv(fd, resv_msg, len, 0);
            resv_msg[len] = '\0';

            shutdown(fd, SHUT_RDWR);
            close(fd);

            if (strcmp(resv_msg, "ALLOWED#") == 0) {
                shared->response = 'Y';
            } else {
                shared->response = 'N';
            }

            free(resv_msg);

            pthread_cond_signal(&shared->response_cond);
        }
        pthread_cond_wait(&shared->scanned_cond, &shared->mutex);
    }
    close(shm_fd);
    return 0;
}