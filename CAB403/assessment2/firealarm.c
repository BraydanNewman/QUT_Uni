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
#include <time.h>
#include <inttypes.h>

typedef struct {
    char alarm; // '-' if inactive, 'A' if active
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} shm_firealarm;

typedef struct {
    char header[4]; // {'D', 'O', 'O', 'R'} or {'D', 'R', 'E', 'G'}
    struct in_addr door_addr;
    in_port_t door_port;
} door_message_format;

struct addr_entry {
    struct in_addr sensor_addr;
    in_port_t sensor_port;
};

typedef struct {
    char header[4]; // {'T', 'E', 'M', 'P'}
    struct timeval timestamp;
    float temperature;
    uint16_t id;
    uint8_t address_count;
    struct addr_entry address_list[50];
} tempsensor_message_format;

typedef struct {
    char header[4]; // {'F', 'I', 'R', 'E'}
} callpoint_message_format;

typedef struct {
    struct in_addr door_addr;
    in_port_t door_port;
} fail_safe_security_door;

void sendMessage(int fd, const char *msg) {
    int len = strlen(msg);
    send(fd, msg, len, 0);

}

void add_door_to_list(fail_safe_security_door *door_list, int *door_counter, fail_safe_security_door new_door) {
    for (int i = 0; i < *door_counter; ++i) {
        if (memcmp(&door_list[i], &new_door, sizeof(fail_safe_security_door)) == 0) {
            return;
        }
    }

    door_list[*door_counter] = new_door;
    (*door_counter)++;
}

void send_emerg_to_door(fail_safe_security_door door) {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
        perror("socket()");
    }
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
//    if (inet_pton(AF_INET, *door.door_addr, &addr.sin_addr) != 1) {
//        perror("inet_pton");
//    }
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = door.door_addr.s_addr;
//    addr.sin_addr.s_addr = inet_netof(door.door_addr.s_addr);
    addr.sin_port = htons(door.door_port);
    if (connect(fd, (struct sockaddr *) &addr, sizeof(addr)) == -1) {
        perror("connect()");
    }
    sendMessage(fd, "OPEN_EMERG#");
    printf("SENT OPEN_EMERG#");
}

void send_emerg_to_doors(fail_safe_security_door door_list[], int *door_counter) {
    for (int i = 0; i < *door_counter; ++i) {
        send_emerg_to_door(door_list[i]);
    }
}


int main(int argc, char *argv[]) {
    fail_safe_security_door fail_safe_security_doors[100];
    int fail_safe_security_doors_count = 0;

    if (argc < 4) {
        fprintf(stderr,
                "Usage: {address:port} {temperature threshold} {min detections} {detection period (in microseconds)} {reserved argument} {shared memory path} {shared memory offset} {overseer address:port}\n");
        exit(1);
    }

    const char delim[2] = ":";

    // Get current Address and Port
    const char *current_address = strtok(argv[1], delim);
    const char *str_current_port = strtok(NULL, delim);
    int current_port = atoi(str_current_port);

    // Get Overseer Address and port
    const char *overseer_address = strtok(argv[8], delim);
    int overseer_port = atoi(strtok(NULL, delim));

    // Get Shared Memory variables
    const char *shm_path = argv[6];
    int shm_offset = atoi(argv[7]);

    // Get Other variables
//    int temperature_threshold = atoi(argv[2]);
//    int min_detections = atoi(argv[3]);
//    int detection_period = atoi(argv[4]);

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
    shm_firealarm *shared = (shm_firealarm *) (shm + shm_offset);

    // Bind to current port to start listening for UDP Messages
    int fd_listen = socket(AF_INET, SOCK_DGRAM, 0);
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
    addr_listen.sin_port = htons(current_port);
    if (bind(fd_listen, (struct sockaddr *) &addr_listen, sizeof(addr_listen)) == -1) {
        perror("bind()");
        return 1;
    }

    // For Sending UDP Messages to overseer
    int fd_send_overseer = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd_send_overseer == -1) {
        perror("socket()");
        return 1;
    }
    struct sockaddr_in dest_addr;
    socklen_t dest_addr_len = sizeof(dest_addr);
    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(overseer_port);
    if (inet_pton(AF_INET, overseer_address, &dest_addr.sin_addr) != 1) {
        perror("inet_pton");
        exit(1);
    }


    // Send Overseer an initialisation message
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
    strcpy(contact_message, "FIREALARM ");
    strcat(contact_message, current_address);
    strcat(contact_message, ":");
    strcat(contact_message, str_current_port);
    strcat(contact_message, " HELLO#");
    sendMessage(fd, contact_message);
    shutdown(fd, SHUT_RDWR);
    close(fd);

    for (;;) {
        void *buff[512];
        recvfrom(fd_listen, buff, 512, MSG_WAITALL, (struct sockaddr *) &addr_listen,
                 sizeof(addr_listen));
        char dest[5] = {0};
        memcpy(dest, buff, 4);
        if (strcmp(dest, "TEMP") == 0) {
            tempsensor_message_format *tempsensor_msg = (tempsensor_message_format *) buff;
//            TODO - Not required for group of 1
        } else if (strcmp(dest, "DOOR") == 0) {
//            TODO SOMETHING WRONG
            door_message_format *door_msg = (door_message_format *) buff;
            fail_safe_security_door new_door = {door_msg->door_addr, door_msg->door_port};
            add_door_to_list(fail_safe_security_doors, &fail_safe_security_doors_count, new_door);
            strcpy(door_msg->header, "DREG");
            sendto(fd_send_overseer, door_msg, sizeof(door_msg), 0, (const struct sockaddr *) &dest_addr,
                   dest_addr_len);
        } else if (strcmp(dest, "FIRE") == 0) {
            pthread_mutex_lock(&shared->mutex);
            shared->alarm = "A";
            pthread_mutex_unlock(&shared->mutex);
            pthread_cond_signal(&shared->cond);
            send_emerg_to_doors(fail_safe_security_doors, &fail_safe_security_doors_count);
            for (;;) {
                recvfrom(fd_listen, buff, 512, MSG_WAITALL, (struct sockaddr *) &addr_listen,
                         sizeof(addr_listen));
                char door_reg[5] = {0};
                memcpy(door_reg, buff, 4);
                if (strcmp(door_reg, "DOOR") == 0) {
                    door_message_format *door_msg = (door_message_format *) buff;
                    fail_safe_security_door new_door = {door_msg->door_addr, door_msg->door_port};
                    send_emerg_to_door(new_door);
                }
            }
        }
    }
}