#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_LEN 100 /* The maximum length command */

int main(void) {
  	char *args[MAX_LEN / 2 + 1]; /* command line arguments */
  	int should_run =1;	 
	/* flag todetermine when to exit program */
  	
	int background = 0;
	while (should_run){
  		printf("my_shell> ");
    	fflush(stdout);
	
		char *input = (char*)malloc(MAX_LEN*sizeof(char));
		fgets(input, MAX_LEN, stdin);
		if (sizeof(input) < 2){
			free(input);
			goto come_here;
		}
		/*
		printf("INPUT: %s\n", input);
		char *str;
		
		int break_while = 0;
		char p[]="&";
		str = strtok(input, " ");
		while (str != NULL){
			
			if (strcmp(p,str) == 0){
				printf("--------------------\n");
				printf("check '&' -> No waitting \n");
				printf("--------------------\n");
				background = 1;
			}
			
			printf("%s\n", str);
			
			str = strtok(NULL," ");
			break_while ++;
			if (break_while > 15){
				break;
			}
		}			    
		*/
		//do fork
		int pid = fork();
		
		//fork error
		if (pid < 0){
			fprintf(stderr, "Fork failed");
			return 1;
		}

		//child part
		else if(pid == 0){ 
			printf("=============================\n");
			printf("CHILD : ls command\n");
			execl("/bin/ls", "/bin/ls", NULL);
			return 99;
		//	execlp("/bin/ls","ls",NULL);
		//	execvp("/bin/ls",args[0],argv);
		}
		
		//parent part
		else{/*
			if (background == 1){
				printf("--------------------\n");
				printf("check '&' -> No waitting \n");
				printf("--------------------\n");
				return 0;
			}*/
			wait(NULL);
			printf("----------------------------------\n");
			printf("PARENT : child (PID = %d) Complete\n",pid);
			printf("----------------------------------\n");	
		}
		return 0;
  		come_here:
		printf("i'm here~~~\n");
	}
	return 0;
	
}

