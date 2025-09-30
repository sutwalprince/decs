#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
  
char * c1 = argv[1] ;
char * c2 = argv[2] ;
if(argv[1] == NULL || argv[2] == NULL) printf("Incorrect number of arguments \n.") ;
else{
    int returnstatus ;
    int child_pid = fork() ;
    if(child_pid > 0){
      waitpid(child_pid , &returnstatus , 0) ;
      printf("Command successfully completed \n %d" , returnstatus);
     
    }else if(child_pid == 0){
      
      execlp(argv[1], argv[1], argv[2],  (char *)NULL);
    }else{
      printf("Fork failed") ;
    }
  }
  return 0;
}


