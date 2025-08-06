#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int main() {

  int ret = fork() ;
  if(ret > 0){
    pid_t pid = getpid();
    printf("I am Parent ") ;
    printf("Parent ID: %d\n", pid);
  }else if(ret == 0){
    printf("I am Child ") ;
    pid_t pid = getpid();
    printf("Process ID: %d\n", pid);
  }else{
    printf("Fork failed") ;
  }
  return 0;
}


