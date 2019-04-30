#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

void handler (int signo){
	printf("Signal handler get signal number : %d\n", signo);
	psignal (signo, "Received signal");
	kill (getpid(), SIGQUIT);
	}

int main(void) {
	void (*hand)(int);
	int pid = getpid();
	printf("PID = %d\n", pid);
	hand = signal(SIGINT, handler);
	if (hand ==  SIG_ERR){
		perror("signal");
		exit(1);
	}
	pause();
	return 0;
}
	

