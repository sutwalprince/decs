#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() 

{

  int ret = fork() ;
  if(ret > 0){
    wait(NULL);
    // pid_t pid = getpid();
    // printf("I am Parent ") ;
    // printf("Parent ID: %d\n", pid);
  }else if(ret == 0){
    printf("I am Child ") ;
    pid_t pid = getpid();
    printf("Process ID: %d\n\n", pid);
    execlp("ls", "ls", "-l",  (char *)NULL);

  }else{
    printf("Fork failed") ;
  }
  return 0;
}


