#include <pthread.h>
#include <stdio.h>
int global_counter = 0;
pthread_mutex_t lock;
void *counter(void *arg)
{
    for(int i = 0 ; i < 1000 ;i++){
        pthread_mutex_lock(&lock);
        global_counter++;
        pthread_mutex_unlock(&lock);
    }
}

int main()
{
    int N = 10 ;
    pthread_t threads[N];
    int thread_nums[N];
    pthread_mutex_init(&lock, NULL);
    
    for (int i = 0; i < N; i++){
        pthread_create(&threads[i], NULL, counter, NULL);
    }

    for (int i = 0; i < N; i++){
        pthread_join(threads[i], NULL);
    }
    printf("counter = %d\n" , global_counter);
    pthread_mutex_destroy(&lock);
    return 0;
}