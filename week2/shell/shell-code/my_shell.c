#include  <stdio.h>
#include  <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>


#define MAX_INPUT_SIZE 1024
#define MAX_TOKEN_SIZE 64
#define MAX_NUM_TOKENS 64
#define MAX_BACKGROUND_PROCESSES 64

using namespace std;
/* Splits the string by space and returns the array of tokens
*
*/
char **tokenize(char *line)
{
  char **tokens = (char **)malloc(MAX_NUM_TOKENS * sizeof(char *));
  char *token = (char *)malloc(MAX_TOKEN_SIZE * sizeof(char));
  int i, tokenIndex = 0, tokenNo = 0;

  for(i =0; i < strlen(line); i++){

    char readChar = line[i];

    if (readChar == ' ' || readChar == '\n' || readChar == '\t'){
      token[tokenIndex] = '\0';
      if (tokenIndex != 0){
	tokens[tokenNo] = (char*)malloc(MAX_TOKEN_SIZE*sizeof(char));
	strcpy(tokens[tokenNo++], token);
	tokenIndex = 0; 
      }
    } else {
      token[tokenIndex++] = readChar;
    }
  }
 
  free(token);
  tokens[tokenNo] = NULL ;
  return tokens;
}

void signalHandler(int sig) {
	printf("\n");
    return ;
}

int main(int argc, char* argv[]) {
	char  line[MAX_INPUT_SIZE];            
	char  **tokens;              
	int i;
	int arr_top = -1 ;
	int background_processes[MAX_BACKGROUND_PROCESSES] ;
	while(1) {			
		// signal(SIGINT,signalHandler);  
		struct sigaction act = { 0 };
		act.sa_handler = &signalHandler;
		sigaction(SIGINT,&act,NULL);


		/* BEGIN: TAKING INPUT */
		char cwd[256];
		getcwd(cwd, sizeof(cwd));
		bzero(line, sizeof(line));
		printf("%s$ " , cwd);
		scanf("%[^\n]", line);
		getchar();
		
		line[strlen(line)] = '\n'; //terminate with new line
		tokens = tokenize(line);

		//do whatever you want with the commands, here we just print them
		
		int process_finished = waitpid(-1 , NULL , WNOHANG ) ;
		if(process_finished > 0){
			printf("process with pid %d finished its execution.\n" , process_finished) ;
		}

		bool is_background_process = false ;
		for(i=0;tokens[i]!=NULL;i++){
			if(strcmp(tokens[i] , "&") == 0) {
				is_background_process = true ;
				tokens[i] = NULL ;
			}
		}
		
		if(tokens[0] == NULL ){
			// do nothing
		}
		else if(strcmp(tokens[0] , "exit") == 0 ){
			free(tokens);
			for(int i = 0 ; i < arr_top ; i++){
				kill(background_processes[i] , 9);
			}
			break ;
		}
		else if(strcmp(tokens[0] , "cd") == 0 ){
			if(chdir(tokens[1]) != 0){
				printf("Directory not found.\n");
			}
		}else if(is_background_process ){
			int child_pid = fork() ;
			if(child_pid > 0){
				// parent process
				background_processes[++arr_top] = child_pid ;
				printf("Background process started with PID %d\n" , child_pid) ;
				// int returnstatus ;
				// wait(&returnstatus) ;
				// int ws = WEXITSTATUS(returnstatus);
				// if(ws != 0) printf("Process exited with status %d\n" , ws);
				// printf("Command successfully completed \n");
				
			}else if(child_pid == 0){
				// child process
				setpgid(0 , 0) ;
				if(execvp(tokens[0], tokens) == -1){
					exit(1) ;
				}
			}else{
				printf("Fork failed\n") ;
			}
		}
		else{
			int child_pid = fork() ;
			if(child_pid > 0){
				int returnstatus ;
				wait(&returnstatus) ;
				int ws = WEXITSTATUS(returnstatus);
				if(ws != 0) printf("Process exited with status %d\n" , ws);
				// printf("Command successfully completed \n");
				
			}else if(child_pid == 0){
				// child process
				if(execvp(tokens[0], tokens) == -1){
					exit(1) ;
				}
			}else{
				printf("Fork failed\n") ;
			}
		}
		
		
			
			// Freeing the allocated memory	
			for(i=0;tokens[i]!=NULL;i++){
				free(tokens[i]);
			}
			free(tokens);
			
		}
		
		
		
	return 0;
}
