#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define N 3

pthread_mutex_t lock;
pthread_cond_t cond[N];
int x = 3 ;
int turn = 0; //

void *print_thread_message(void *arg)
{
  int thread_num = *(int *)arg;

  while (x > 0)
  {
    pthread_mutex_lock(&lock);
    x--;
    while (turn != thread_num)
    {
      pthread_cond_wait(&cond[thread_num], &lock);
    }

    printf("I am thread %d\n", thread_num);
    fflush(stdout);

    turn = (turn + 1) % N;

    pthread_cond_signal(&cond[turn]); 
    pthread_mutex_unlock(&lock);
  }
}

int main()
{

  pthread_t threads[N];
  int thread_nums[N];
  for (int i = 0; i < N; i++)
    thread_nums[i] = i;

  // Create N threads
  for (int i = 0; i < N; i++)
    pthread_create(&threads[i], NULL, print_thread_message, &thread_nums[i]);

  // Wait for all threads (though in this case, the threads run forever)
  for (int i = 0; i < N; i++)
    pthread_join(threads[i], NULL);

  return 0;
}


















// #include <stdio.h>
// #include <pthread.h>
// #include <stdlib.h>
// #include <unistd.h>

// #define N 7

// pthread_mutex_t lock;
// pthread_cond_t cond;
// int x = 1000 ;
// int turn = 0; //

// void *print_thread_message(void *arg)
// {
//   int thread_num = *(int *)arg;

//   while (x--)
//   {
//     pthread_mutex_lock(&lock);

//     while (turn != thread_num)
//     {
//       pthread_cond_wait(&cond, &lock);
//     }

//     printf("I am thread %d\n", thread_num);
//     fflush(stdout);

//     turn = (turn + 1) % N;

//     pthread_cond_broadcast(&cond); 
//     pthread_mutex_unlock(&lock);
//   }
// }

// int main()
// {

//   pthread_t threads[N];
//   int thread_nums[N];
//   for (int i = 0; i < N; i++)
//     thread_nums[i] = i;

//   // Create N threads
//   for (int i = 0; i < N; i++)
//     pthread_create(&threads[i], NULL, print_thread_message, &thread_nums[i]);

//   // Wait for all threads (though in this case, the threads run forever)
//   for (int i = 0; i < N; i++)
//     pthread_join(threads[i], NULL);

//   return 0;
// }
