#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>

#define FALSE 0
#define TRUE !FALSE
#define BUFFER_SIZE 5
#define MAX_SLEEP 5.0

typedef struct message_queue
{
    time_t buffer[BUFFER_SIZE];
    int keep_running;
    int position;
    int is_room;
} mq;

void *producer_function(void *arg)
{
    mq *mqueue = arg;
    int sleeptime;
    time_t message;

    srand((unsigned)time(NULL)); /* seed the random number generator.*/

    while (mqueue->keep_running)
    {
        /*
		* The ANSI C standard only states that rand() is a
		* random number generator which generates integers
		* in the range [0,RAND_MAX] inclusive, with RAND_MAX
		* being a value defined in stdlib.h, and RAND_MAX being at least 32767.
		*
		*/
        /*sleeptime = 1 + (int)( MAX_SLEEP * rand() / (RAND_MAX + 1.0) ); */
        sleeptime = (int)(MAX_SLEEP * rand() / (RAND_MAX + 1.0));
        printf("Producer sleeping for %d seconds\n", sleeptime);
        fflush(stdout);
        sleep(sleeptime);

        message = time(NULL);
        printf("Producer produced %s", ctime(&message));

        /* this is the blocking send */

        while (mqueue->is_room == FALSE)
        {
            /* no room */
            printf("Producer Blocked\n");
            fflush(stdout);
            sleep(1);
        }

        printf("Producer UnBlocked\n");
        fflush(stdout);

        mqueue->buffer[mqueue->position++] = message;

        printf("\t\t\t\tItems in buffer: %d\n", mqueue->position);
        fflush(stdout);

        if (mqueue->position == BUFFER_SIZE)
        {
            mqueue->is_room = FALSE;
            printf("Full\n");
            fflush(stdout);
        }
    }
    printf("Producer told to stop.\n");
    fflush(stdout);
    return NULL;
}

void *consumer_function(void *arg)
{
    mq *mqueue = arg;
    time_t message;
    int sleeptime;

    srand((unsigned)time(NULL)); /* seed the random number generator.*/

    while (mqueue->keep_running)
    {
        /*
		* The ANSI C standard only states that rand() is a
		* random number generator which generates integers
		* in the range [0,RAND_MAX] inclusive, with RAND_MAX
		* being a value defined in stdlib.h, and RAND_MAX being at least 32767.
		*
		*/
        /*sleeptime = 1 + (int)( MAX_SLEEP * rand() / (RAND_MAX + 1.0) ); */
        sleeptime = (int)(MAX_SLEEP * rand() / (RAND_MAX + 1.0));

        printf("\t\tConsumer sleeping for %d seconds\n", sleeptime);
        fflush(stdout);
        sleep(sleeptime);

        /* this is the blocking receive */

        printf("\t\tConsumer wants to consume\n");
        fflush(stdout);

        while (mqueue->position == 0)
        {
            /* nothing there so I have to wait */
            printf("\t\tConsumer Blocked\n");
            fflush(stdout);
            sleep(1);
        }

        printf("\t\tConsumer UnBlocked\n");
        fflush(stdout);

        message = mqueue->buffer[--mqueue->position];
        mqueue->is_room = TRUE;

        printf("\t\tConsumer consumed %s", ctime(&message));
        printf("\t\t\t\tItems in buffer: %d\n", mqueue->position);
        fflush(stdout);
    }
    printf("\t\tConsumer told to stop.\n");
    fflush(stdout);
    return NULL;
}
int main() {
    pthread_t producer;
    pthread_t consumer;
    pthread_t consumer1;
    mq messages;
    char ignore_this[80];

    messages.keep_running = TRUE;
    messages.position = 0;
    messages.is_room = TRUE;

    if (pthread_create(&producer, NULL, producer_function, &messages)) {
        printf("error creating thread.");
        abort();
    }
    if (pthread_create(&consumer, NULL, consumer_function, &messages)) {
        printf("error creating thread.");
        abort();
    }
    if (pthread_create(&consumer1, NULL, consumer_function, &messages)) {
        printf("error creating thread.");
        abort();
    }

    fgets(ignore_this, 80, stdin);
    messages.keep_running = FALSE;
    if (pthread_join(producer, NULL))
    {
        printf("error joining producer thread");
        abort();
    }
    if (pthread_join(consumer, NULL))
    {
        printf("error joining consumer thread");
        abort();
    }

    return 0;
}
