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

typedef struct {
    char status; // '-' for inactive, '*' for active
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} shm_callpoint;

typedef struct {
    char header[4]; // {'F', 'I', 'R', 'E'}
} fire_emergency_datagram;

int main(int argc, char *argv[]) {
    bool fire_state_lock = false;
    if (argc < 4) {
        fprintf(stderr,
                "Usage: {resend delay (in microseconds)} {shared memory path} {shared memory offset} {fire alarm unit address:port}\n");
        exit(1);
    }

    int resend_delay = atoi(argv[1]) * 1000;
    const char *shm_path = argv[2];
    int shm_offset = atoi(argv[3]);

    const char delim[2] = ":";

    const char *fire_alarm_unit_address = strtok(argv[4], delim);
    int fire_alarm_unit_port = atoi(strtok(NULL, delim));

    //  Shared Memory
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
    shm_callpoint *shared = (shm_callpoint *) (shm + shm_offset);

    // Send Message over UDP
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd == -1) {
        perror("socket()");
        return 1;
    }
    struct sockaddr_in dest_addr;
    socklen_t dest_addr_len = sizeof(dest_addr);
    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(fire_alarm_unit_port);
    if (inet_pton(AF_INET, fire_alarm_unit_address, &dest_addr.sin_addr) != 1) {
        perror("inet_pton");
        exit(1);
    }

    // Setup sleep time
    struct timespec ts;
    ts.tv_nsec = resend_delay;

    // Message setup
    char buff[4] = {"FIRE"};

    for (;;) {
        pthread_mutex_lock(&shared->mutex);
        char current_state = shared->status;
        pthread_mutex_unlock(&shared->mutex);
        if (strcmp(&current_state, "*")) {
            fire_state_lock = true;
        }
        if (fire_state_lock == true) {
            sendto(fd, buff, strlen(buff), 0, (struct sockaddr *) &dest_addr, sizeof(dest_addr));
        }
        nanosleep(&ts, &ts);
    }
}
