#include <pthread.h>
#include <stdio.h>
int global_counter = 0;
void *counter(void *arg)
{
    printf("I am thread %d\n" , *(int * )arg ) ;
}

int main()
{
    int N = 10 ;
    pthread_t threads[N];
    int thread_nums[N];
    for(int i = 0; i < N; i++)
      thread_nums[i] = i;

    for (int i = 0; i < N; i++){
        pthread_create(&threads[i], NULL, counter, (void *) &thread_nums[i]);
    }

    for (int i = 0; i < N; i++){
        pthread_join(threads[i], NULL);
    }
    printf("I am main thread\n" ) ;
    
    return 0;
}