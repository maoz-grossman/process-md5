#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>

int processes[5];
int index;

//signal handler
int sigCatcher(){
	signal(SIGINT,sigCatcher);
	int p = getpid();
	printf("PID %d caught one\n",p);
	if(index >= 0)
		kill(processes[index],SIGINT);
}


int main(){
	int status;
	int pid;
	int counter;
	
	signal(SIGINT, sigCatcher);
	
	//main loop
	while(counter<5){
		if((pid=fork())<0){//eror
			printf("eror in fork");
			exit(1);
		}
		else if(pid == 0){
			printf("PID %d ready\n",getpid());
			index = counter-1;
			pause();
			exit(0);
		}
		else//parent
			processes[counter] = pid;
		counter++;
	}
	
	sleep(1);
	kill(processes[4],SIGINT);
	sleep(1);
	
	int collectChild;
	counter=0;
	
	while(counter<5){
		collectChild = wait(&status);
		printf("%d id dead\n",collectChild);
		counter++;
	}
	exit(0);
}
