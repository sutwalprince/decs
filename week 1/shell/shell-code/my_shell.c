#include  <stdio.h>
#include  <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


#define MAX_INPUT_SIZE 1024
#define MAX_TOKEN_SIZE 64
#define MAX_NUM_TOKENS 64

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


int main(int argc, char* argv[]) {
	char  line[MAX_INPUT_SIZE];            
	char  **tokens;              
	int i;
	
		
	while(1) {			
		/* BEGIN: TAKING INPUT */
		char cwd[256];
		getcwd(cwd, sizeof(cwd));
		bzero(line, sizeof(line));
		printf("%s$ " , cwd);
		scanf("%[^\n]", line);
		getchar();

		// printf("Command entered: %s (remove this debug output later)\n", line);
		// /* END: TAKING INPUT */

		line[strlen(line)] = '\n'; //terminate with new line
		tokens = tokenize(line);
		
		
       //do whatever you want with the commands, here we just print them
		// printf("%s\n" , tokens[0]) ;
		
		if(tokens[0] == NULL){
			// do nothing
		}
		else if(strcmp(tokens[0] , "cd") == 0 ){
			if(chdir(tokens[1]) != 0){
				printf("Directory not found.\n");
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
				if(execvp(tokens[0], tokens) == -1){
					exit(1) ;
				}
			}else{
				printf("Fork failed") ;
			}
		}

		// for(i=0;tokens[i]!=NULL;i++){
		// 	printf("found token %s (remove this debug output later)\n", tokens[i]);
		// }
       
		// Freeing the allocated memory	
		for(i=0;tokens[i]!=NULL;i++){
			free(tokens[i]);
		}
		free(tokens);

	}
	return 0;
}
