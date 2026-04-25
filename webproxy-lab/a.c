#define _XOPEN_SOURCE 700
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
// thread option
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutexattr_t attr;

void *thread_func(void *arg) {
    int *shared_data = (int *)arg;
    pthread_mutex_lock(&lock);
    *shared_data += 1;
    printf("thread: %d\n", *shared_data);
    pthread_mutex_unlock(&lock);

    return NULL;
}

int main() {
    pthread_t tid1, tid2;
    int *shared_data = malloc(sizeof(int));
    *shared_data = 1;

    printf("before: %d\n", *shared_data);

    pthread_create(&tid1, NULL, thread_func, shared_data);
    pthread_create(&tid2, NULL, thread_func, shared_data);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    printf("after: %d\n", *shared_data);

    free(shared_data);
    pthread_mutex_destroy(&lock);
    return 0;
}