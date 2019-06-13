#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
//----------------------------------------
//****************************************
//              os ex 1.3
//________________________________________
//
// parent and child processes comunication
// using signls.
// to compile: gcc -o signals signals.c
// to run: ./signals <enter your string>
//****************************************
//----------------------------------------

//---------------------------------------
//          global var
//---------------------------------------
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

//---------------------------------------
//            main function
//---------------------------------------
int main(){
	int status;
	int pid;
	int counter;
	
	signal(SIGINT, sigCatcher);
	
	//main loop
	for(counter=0; counter<5; counter++){
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
	}
	
	sleep(2);
	kill(processes[4],SIGINT);
	sleep(2);
	
	int collectChild;
	counter=0;
	
	while(counter<5){
		collectChild = wait(&status); 		// collect zombies
		printf("%d is dead\n", collectChild);
		counter++;
	}
	exit(0);
}
