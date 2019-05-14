#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int fd[2];
	int fd2[2];
    pid_t pid;
    char buf[257];
	char buf2[257];
    int len, status;
	int len2, status2;

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }
	if (pipe(fd2) == -1) {
	    perror("pipe");
		exit(1);
	}

    switch (pid = fork()) {
        case -1 :
            perror("fork");
            exit(1);
            break;
        case 0 : /* child */
            close(fd[1]);
			close(fd2[0]);
			buf2[0] = '\0';
			write(fd2[1], "from child\n",11);
            write(1, "Child Process:", 15);
            len = read(fd[0], buf, 256);
            write(1, buf, len);
            close(fd2[1]);
			close(fd[0]);
            
			break;
        default :
            close(fd[0]);
			close(fd2[1]);
            buf[0] = '\0';
            write(fd[1], "from parent\n", 12);
			//waitpid(pid, &status, 0);
			//write(1, "Parent Process:", 16);
            waitpid(pid, &status,0);
			write(1, "Parent Process:", 16);
			len2 = read(fd2[0],buf2, 256);
			write(1, buf2, len2);
			close(fd[1]);
			close(fd2[0]);

            //waitpid(pid, &status, 0);
            break;
    }

    return 0;
}
