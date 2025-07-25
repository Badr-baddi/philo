#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void*    routine()
{
    printf("test from threads\n");
    sleep(3);
    printf("ending thread\n");

}

int main(int argc, char **argv)
{
    pthread_t   t1, t2;
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&t1, NULL, &routine, NULL);
    pthread_create(&t2, NULL, &routine, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_mutex_destroy(&mutex);
    return 0;
}