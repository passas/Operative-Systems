#include <sys/types.h>
#include <signal.h>
//kill

#include <sys/wait.h>
//wait

#include <unistd.h>
//execlp
//dup2

#include <stdio.h>
//perror

#define MAX 10
#define BUS 4096

int the_one_who_shall_not_be_killed = -1;

/*
* This program focus on establish perceptions of the results via "exec's".
* Will take a word to search and a maximum of 10 files.
* Will execute grep on each file.
* When one process finds the word, the others get shutdown.
*/

void signal_handler (int sig)
{
	if (sig == SIGUSR1)
	{
		if ( the_one_who_shall_not_be_killed == getpid() )
		{
			printf ("SIGUSR1 received, SIGUSR1 ignored\n");
		}
		else
		{
			_exit (0);
		}
		
	}
	else if (sig == SIGCHLD)
	{
		while (waitpid(-1, NULL, WNOHANG) > 0);
		//zombie reaper
	}
}

main (int argc, char *argv[])
{
	size_t bytes;
	char buf[BUS];
	int fifo_fd[2];

	the_one_who_shall_not_be_killed = getpid();
	if ( signal (SIGUSR1, signal_handler) == SIG_ERR )
	{
		perror ("signal (SIGUSR1,...)");
	}
	if ( signal (SIGCHLD, signal_handler) == SIG_ERR )
	{
		perror ("signal (SIGCHLD,...)");
	}

	pipe (fifo_fd);

	for (int i=0; i<MAX && i<(argc-2); i++)
	{
		if ( fork() == 0 )
		{
			dup2 (fifo_fd[1], 1);
			close (fifo_fd[1]);
			if ( execlp ("grep", "grep", argv[1], argv[2+i], NULL) == -1)
				_exit (-1);
			_exit (0);
		}
	}
	
	close (fifo_fd[1]);

	for (int i=0; i<MAX && i<(argc-2); i++)
	{
		wait (NULL);
		
		if ( (bytes = read (fifo_fd[0], buf, BUS)) > 0 )
		{
			//write (1, buf, bytes);
			kill (0, SIGUSR1); //all group processes (including father) must handle the signal
			i = MAX; //only doable because of the zombie reaper who catches the SIGCHLD meantime
		}		
	}		
	
	close (fifo_fd[0]);
}
