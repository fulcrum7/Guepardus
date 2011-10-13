#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
void call_privileged();

int main()
{
	pid_t pid;	
	/* do the fork() to give control to our privileged application */
	/* TODO: vfork is better */	
	pid=fork();	
	switch(pid)
	{
		case -1: /* fork error, should call plan B mode */ 
				break;
		case 0:  /* child process, call privileged application */
				call_privileged();
				break;
		default: 
				break;

	}
	
	/*
	 *  this process should be SystemV init, but before 	run init
	 *  we should do the deffered_init_script to mount normal rootfs
     *  or maybe for smth else
	 */

	/*   do the script */
	system("./defered_init_script");
        /*   ready to start init */
	printf("This is process %d\nStarting the init...\n",getpid());
	/* for debugging */	
	sleep(15);

	/*  change  the image of this process */
	execl("/sbin/init","init");		
	printf("Can't run /init\n"
	       "Sleep and run /bin/sh\n");
	sleep(7);
	execl("/bin/sh","sh");
}


void call_privileged()
{
	/* this is child process */
	printf("Privileged application pid %d\n",getpid());
	/* change the image of this process to priv_app */
    execl("/priv_app","priv_app");
	printf("End of execution\n");
	exit(EXIT_SUCCESS);
}
