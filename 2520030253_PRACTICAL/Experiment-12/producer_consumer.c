
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int buffer = 0;
sem_t empty, full;

void *producer(void *arg) {
    for (int i = 1; i <= 5; i++) {
        sem_wait(&empty);
        buffer = i;
        printf("Produced: %d\n", buffer);
        sem_post(&full);
    }
    return NULL;
}

void *consumer(void *arg) {
    for (int i = 1; i <= 5; i++) {
        sem_wait(&full);
        printf("Consumed: %d\n", buffer);
        sem_post(&empty);
    }
    return NULL;
}

int main() {
    pthread_t p, c;

    sem_init(&empty, 0, 1);
    sem_init(&full, 0, 0);

    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);

    pthread_join(p, NULL);
    pthread_join(c, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    return 0;
}
