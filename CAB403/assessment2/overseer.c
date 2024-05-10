#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <stdbool.h>
#include <errno.h>
#include <time.h>
#include <inttypes.h>


typedef struct {
    char security_alarm; // '-' if inactive, 'A' if active
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} shm_overseer;

typedef struct {
    int id;
    char address[10];
    int port;
} door_component;

typedef struct {
    char address[10];
    int port;
} firealarm_component;

typedef struct {
    int cardreaders[100];
    int cardreaders_len;
    door_component secure_doors[20];
    int secure_doors_len;
    door_component safe_doors[20];
    int safe_doors_len;
    pthread_mutex_t mutex;
} system_components;

struct arg_struct {
    system_components *system_components;
    int client_sock;
};

struct adder_port {
    char address[10];
    int port;
    system_components *system_components;
};

const int MAX_MESSAGE_LENGTH = 100;

char *authorisation_file;
char *connections_file;
int door_open_duration;

system_components all_system_components;

bool fire_alarm_lock = false;


int create_tcp_server_fd(int listen_port) {
    int fd_listen = socket(AF_INET, SOCK_STREAM, 0);
    int opt_enable = 1;
    setsockopt(fd_listen, SOL_SOCKET, SO_REUSEADDR, &opt_enable, sizeof(opt_enable));
    setsockopt(fd_listen, SOL_SOCKET, SO_REUSEPORT, &opt_enable, sizeof(opt_enable));
    struct sockaddr_in addr_listen;
    memset(&addr_listen, 0, sizeof(addr_listen));
    addr_listen.sin_addr.s_addr = htonl(INADDR_ANY);
    addr_listen.sin_family = AF_INET;
    addr_listen.sin_port = htons(listen_port);
    bind(fd_listen, (struct sockaddr *) &addr_listen, sizeof(addr_listen));
    listen(fd_listen, 20);
    return fd_listen;
}

int create_tcp_client_fd(char *address, int *port) {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    inet_pton(AF_INET, address, &addr.sin_addr);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    connect(fd, (struct sockaddr *) &addr, sizeof(addr));
    return fd;
}

char *check_cardreader_scan(int cardreader_id, char *scanned_code) {
    scanned_code[strlen(scanned_code) - 1] = '\0';
    FILE *fp_auth;
    FILE *fp_connections;
    char auth_line[100];
    bool auth_found = false;
    char connections_line[100];
    bool connections_found = false;
    const char delim[2] = " ";
    fp_auth = fopen(authorisation_file, "r");
    while (fgets(auth_line, sizeof(auth_line), fp_auth) != NULL) {
        if (strstr(auth_line, scanned_code) != NULL) {
            auth_found = true;
            break;
        }
    }
    int length = snprintf(NULL, 0, "%d", cardreader_id);
    char *str_cardreader_id = malloc(length + 1);
    snprintf(str_cardreader_id, length + 1, "%d", cardreader_id);
    char *door_id = "";
    fp_connections = fopen(connections_file, "r");
    while (fgets(connections_line, sizeof(connections_line), fp_connections) != NULL) {
        strtok(connections_line, delim);
        char *cardreader_id = strtok(NULL, delim);
        if (strstr(cardreader_id, str_cardreader_id) != NULL) {
            door_id = strtok(NULL, delim);
            door_id[strlen(door_id) - 1] = '\0';
            connections_found = true;
            break;
        }
    }
    if (auth_found && connections_found && strstr(auth_line, door_id) != NULL) {
        return door_id;
    } else {
        return "";
    }
}

void send_tcp_message(int fd, char *message) {
    int len = strlen(message);
    send(fd, message, len, 0);
}

void read_tcp_message(int fd, char *full_message) {
    ssize_t data_rev;
    size_t message_index = 0;
    while (message_index < 100 && (data_rev = read(fd, &full_message[message_index], 1) >= 0)) {
        if ('#' == full_message[message_index] || 0x0a == full_message[message_index]) {
            break;
        }
        message_index++;
    }
}

door_component *find_door_with_id(int door_id, system_components *system_components) {
    printf("FINDING DOORS\n");
    printf("looking for door - %d\n", door_id);
    // Check safe doors
    for (int i = 0; i < system_components->safe_doors_len; ++i) {
        if (system_components->safe_doors[i].id == door_id) {
            printf("FOUND DOOR - %d\n", system_components->safe_doors[i].id);
            return &system_components->safe_doors[i];
        }
    }
    // Check secure doors
    for (int i = 0; i < system_components->secure_doors_len; ++i) {
        if (system_components->secure_doors[i].id == door_id) {
            printf("FOUND DOOR - %d\n", system_components->safe_doors[i].id);
            return &system_components->secure_doors[i];
        }
    }
    return NULL;
}

void display_doors(system_components *system_components) {
    pthread_mutex_lock(&system_components->mutex);
    printf("\nSAFE DOORS\n{id}\t{address}\t{port}\n");
    for (int i = 0; i < system_components->safe_doors_len; ++i) {
        printf("%d\t", system_components->safe_doors[i].id);
        printf("%s\t", system_components->safe_doors[i].address);
        printf("%d\n", system_components->safe_doors[i].port);
    }
    printf("\nSECURE DOORS\n{id}\t{address}\t{port}\n");
    for (int i = 0; i < system_components->secure_doors_len; ++i) {
        printf("%d\t", system_components->secure_doors[i].id);
        printf("%s\t", system_components->secure_doors[i].address);
        printf("%d\n", system_components->secure_doors[i].port);
    }
    pthread_mutex_unlock(&system_components->mutex);
}

void *handle_tcp_incoming_connection(void *context) {
    struct arg_struct *thread_args = context;

    const char delim[2] = " ";
    const char adder_delim[2] = ":";

    // Get message data
    char msg[100] = {0};
    read_tcp_message(thread_args->client_sock, msg);
    printf("MESSAGE REV - %s\n", msg);

    if (strncmp("CARDREADER", msg, strlen("CARDREADER")) == 0) {
        if (strstr(msg, "HELLO#") != NULL) {
            // ADD CARDREADER TO LIST
            printf("ADDING CARDREADER TO LIST\n");
            strtok(msg, delim);
            int id = atoi(strtok(NULL, delim));
            pthread_mutex_lock(&thread_args->system_components->mutex);
            thread_args->system_components->cardreaders[thread_args->system_components->cardreaders_len] = id;
            thread_args->system_components->cardreaders_len++;
            pthread_mutex_unlock(&thread_args->system_components->mutex);
        } else if (strstr(msg, "SCANNED") != NULL) {
            // SCANNED CARD
            printf("GOT SCAN FROM CARDREADER\n");
            strtok(msg, delim);
            int id = atoi(strtok(NULL, delim));
            strtok(NULL, delim);
            char *scanned_code = strtok(NULL, delim);
            scanned_code[strlen(scanned_code) - 1] = '\0';
            char *door_id = check_cardreader_scan(id, scanned_code);
            if (strlen(door_id) == 0) {
                // ACCESS DENIED
                send_tcp_message(thread_args->client_sock, "DENIED#");
            } else {
                // ACCESS ALLOWED
                send_tcp_message(thread_args->client_sock, "ALLOWED#");
                close(thread_args->client_sock);

                door_component *door = find_door_with_id(atoi(door_id), thread_args->system_components);
                if (door == NULL) {
                    printf("CANT FIND DOOR\n");
                    if (thread_args->client_sock) shutdown(thread_args->client_sock, SHUT_RDWR);
                    if (thread_args->client_sock) close(thread_args->client_sock);
                    pthread_exit(0);
                }
                printf("DOOR PORT - %d\n", door->port);
                printf("DOOR ADDRESS - %s\n", door->address);
                int door_controller_fd_client = create_tcp_client_fd(door->address, door->port);
                send_tcp_message(door_controller_fd_client, "OPEN#");
                char opening_message[100] = {0};
                read_tcp_message(door_controller_fd_client, opening_message);
                if (strcmp(opening_message, "OPENING#") == 0) {
                    char message[100] = {0};
                    read_tcp_message(door_controller_fd_client, message);
                    close(door_controller_fd_client);

                    struct timespec ts;
                    ts.tv_nsec = door_open_duration;
                    nanosleep(&ts, &ts);
                    int door_controller_fd_client_close = create_tcp_client_fd(door->address, door->port);
                    send_tcp_message(door_controller_fd_client_close, "CLOSE#");

                }
            }
        }
    } else if (strncmp("DOOR", msg, strlen("DOOR")) == 0) {
        // ADD DOORS TO LIST
        if (strstr(msg, "FAIL_SAFE#") != NULL) {
            printf("ADDING SAFE DOOR TO LIST\n");
            strtok(msg, delim);
            int id = atoi(strtok(NULL, delim));
            char *adder_port = strtok(NULL, delim);

            char *address = strtok(adder_port, adder_delim);
            char *port_str = strtok(NULL, adder_delim);
            int port = atoi(port_str);
            pthread_mutex_lock(&thread_args->system_components->mutex);
            door_component door;
            door.id = id;
            door.port = port;
            strcpy(door.address, address);
            int index = thread_args->system_components->safe_doors_len;
            thread_args->system_components->safe_doors[index].id = id;
            thread_args->system_components->safe_doors[index].port = port;
            strcpy(thread_args->system_components->safe_doors[index].address, address);
            thread_args->system_components->safe_doors_len++;
            pthread_mutex_unlock(&thread_args->system_components->mutex);
        } else if (strstr(msg, "FAIL_SECURE#") != NULL) {
            printf("ADDING SECURE DOOR TO LIST\n");
            strtok(msg, delim);
            int id = atoi(strtok(NULL, delim));
            char *adder_port = strtok(NULL, delim);

            char *address = strtok(adder_port, adder_delim);
            char *port_str = strtok(NULL, adder_delim);
            int port = atoi(port_str);
            pthread_mutex_lock(&thread_args->system_components->mutex);
            thread_args->system_components->secure_doors[thread_args->system_components->secure_doors_len].id = id;
            thread_args->system_components->secure_doors[thread_args->system_components->secure_doors_len].port = port;
            strcpy(thread_args->system_components->secure_doors[thread_args->system_components->secure_doors_len].address,
                   address);
            thread_args->system_components->secure_doors_len++;
            pthread_mutex_unlock(&thread_args->system_components->mutex);
        }

    } else if (strncmp("FIREALARM", msg, strlen("FIREALARM")) == 0) {
        printf("\nRECEIVED FIREALARM MESSAGE\n");
    } else if (strncmp("CAMERA", msg, strlen("CAMERA")) == 0) {
        printf("\nRECEIVED CAMERA MESSAGE\n");
        // Dont have to do as group of 1
    } else if (strncmp("ELEVATOR", msg, strlen("ELEVATOR")) == 0) {
        printf("\nRECEIVED ELEVATOR MESSAGE\n");
        // Dont have to do as group of 1
    } else if (strncmp("DESTSELECT", msg, strlen("DESTSELECT")) == 0) {
        printf("\nRECEIVED DESTSELECT MESSAGE\n");
        // Dont have to do as group of 1
    }
    if (thread_args->client_sock) shutdown(thread_args->client_sock, SHUT_RDWR);
    if (thread_args->client_sock) close(thread_args->client_sock);
    pthread_exit(0);
}


void *TCP_overseer_handler(void *context) {
    struct adder_port *thread_args = context;

    int port = thread_args->port;

    int tcp_server_fd = create_tcp_server_fd(port);

//    system_components all_system_components;
//    all_system_components.cardreaders_len = 0;
//    all_system_components.secure_doors_len = 0;
//    all_system_components.safe_doors_len = 0;

    pthread_mutex_init(&all_system_components.mutex, NULL);
    // For process to handle incoming connection
    // Every connection gets its own thread
    struct sockaddr client_addr;
    socklen_t client_addr_len;
    int client_sock;
    pthread_t client_threadid;
    while ((client_sock = accept(tcp_server_fd, &client_addr, &client_addr_len)) != -1) {
        printf("STARTING NEW THREAD\n");
        struct arg_struct thread_args;
        thread_args.client_sock = client_sock;
        thread_args.system_components = &all_system_components;
        pthread_create(&client_threadid, NULL, handle_tcp_incoming_connection, &thread_args);
    }
}

void UDP_overseer_handler(char *address, int *port) {
    for (;;) {
        printf("TEST");
    }
}


int main(int argc, char *argv[]) {
    if (argc < 9) {
        fprintf(stderr,
                "Usage: {address:port} {door open duration (in microseconds)} {datagram resend delay (in microseconds)} {authorisation file} {connections file} {layout file} {shared memory path} {shared memory offset}\n");
        exit(1);
    }
    const char delim[2] = ":";

    all_system_components.cardreaders_len = 0;
    all_system_components.secure_doors_len = 0;
    all_system_components.safe_doors_len = 0;

    // Overseer Connection
    char *overseer_address = strtok(argv[1], delim);
    char *str_overseer_port = strtok(NULL, delim);
    int overseer_port = atoi(str_overseer_port);

    // Door Open Duration
    door_open_duration = atoi(argv[2]) * 1000;

    // Datagram Resend Delay
//    int datagram_resend_delay = atoi(argv[3]);

    // authorisation file
    authorisation_file = argv[4];

    // connections file
    connections_file = argv[5];

    // layouts file
//    const char *layout_file = argv[6];

    // Shared Memory
//    const char *shm_path = argv[7];
//    int shm_offset = atoi(argv[8]);
//
//    // Shared Memory
//    int shm_fd = shm_open(shm_path, O_RDWR, 0);
//    if (shm_fd == -1) {
//        perror("shm_open()");
//        exit(1);
//    }
//    struct stat shm_stat;
//    if (fstat(shm_fd, &shm_stat) == -1) {
//        perror("fstat()");
//        exit(1);
//    }
//    char *shm = mmap(NULL, shm_stat.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
//    if (shm == MAP_FAILED) {
//        perror("mmap()");
//        exit(1);
//    }
//    shm_overseer *shared = (shm_overseer *) (shm + shm_offset);


    pthread_t client_threadid;
    struct adder_port thread_args;
    thread_args.port = overseer_port;
    strcpy(thread_args.address, overseer_address);

    pthread_create(&client_threadid, NULL, TCP_overseer_handler, &thread_args);

    char command[100];
    for (;;) {
        fgets(command, sizeof(command), stdin);

        if (strncmp("DOOR LIST", command, strlen("DOOR LIST")) == 0) {
            display_doors(&all_system_components);
        } else if (strncmp("DOOR OPEN", command, strlen("DOOR OPEN")) == 0) {
            char *given_id = command + strlen("DOOR OPEN ");
            door_component *door = find_door_with_id(atoi(given_id), &all_system_components);
            if (door == NULL) {
                continue;
            }
            int door_controller_fd_client = create_tcp_client_fd(door->address, door->port);
            send_tcp_message(door_controller_fd_client, "OPEN#");
            close(door_controller_fd_client);
        } else if (strncmp("DOOR CLOSE", command, strlen("DOOR CLOSE")) == 0) {
            char *given_id = command + strlen("DOOR CLOSE ");
            door_component *door = find_door_with_id(atoi(given_id), &all_system_components);
            if (door == NULL) {
                continue;
            }
            int door_controller_fd_client = create_tcp_client_fd(door->address, door->port);
            send_tcp_message(door_controller_fd_client, "CLOSE#");
            close(door_controller_fd_client);
        }
    }


//    TCP_overseer_handler(overseer_address, overseer_port);

//    // Create Process to handle TCP messages.
//    pid_t pid_tcp = fork();
//    if (pid_tcp == 0) {
//        // IN CHILD PROCESS
//        TCP_overseer_handler(overseer_address, &overseer_port);
//        exit(EXIT_SUCCESS);
//    }
//
//    // Create Process to handle UDP messages.
//    pid_t pid_udp = fork();
//    if (pid_udp == 0) {
//        // IN CHILD PROCESS
////        UDP_overseer_handler(overseer_address, overseer_port);
//        exit(EXIT_SUCCESS);
//    }

//    // Wait for both process to finish
//    wait(NULL);
//    wait(NULL);

    exit(EXIT_SUCCESS);
}