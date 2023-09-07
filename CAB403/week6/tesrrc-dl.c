#include <pthread.h>
#include <stdio.h>
#include <string.h> /* String handling */

void *addMillion(void *arg);

int globalVar = 0;

pthread_mutex_t lock;

int main(int argc, char *argv[]) {
    pthread_t thread1, thread2, thread3;

    if (pthread_create(&thread1, NULL, addMillion, NULL) != 0) {
        perror("pthread_created");
        return 1;
    }

    pthread_create(&thread1, NULL, addMillion, NULL);
    pthread_create(&thread2, NULL, addMillion, NULL);
    pthread_create(&thread3, NULL, addMillion, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    printf("\n\nTotal for globalVar = %d\n", globalVar);
    return 0;
}

void *addMillion(void *ptr) {
    if (pthread_mutex_lock(&lock) != 0) {
        perror("pthread_mutex_lock");
        return NULL;
    }

    for (int i = 0; i < 10000000; i++) {
        globalVar++;
    }

    if (pthread_mutex_unlock(&lock) != 0) {
        perror("pthread_mutex_lock");
        return NULL;
    }

    return NULL;
}