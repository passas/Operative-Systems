#include <stdlib.h>
#include <stdio.h>

 #include <unistd.h>
//alarm

#include <signal.h>
//signal

#define SECS 1

int sig_int = 0;
unsigned int seconds = 0;

void sig_handler (int sig)
{
	if (sig == SIGINT) //ctrl + c
	{
		sig_int++;
		printf (" %d s\n", seconds);
	}
	else if ( sig == SIGQUIT ) //ctrl + '\'
	{
		printf (" %d\n", sig_int);
		exit (0);
	}
	else if ( sig == SIGALRM )
	{
		seconds += SECS;
	}
}

main ()
{
	if ( signal (SIGINT, sig_handler) == SIG_ERR )
	{
		perror ("signal (SIGINT,...)");
	}
	if ( signal (SIGQUIT, sig_handler) == SIG_ERR )
	{
		perror ("signal (SIGQUIT,...)");
	}
	if ( signal (SIGALRM, sig_handler) == SIG_ERR )
	{
		perror ("signal (SIGALRM,...)");
	}

	while (1)
	{
		alarm (SECS);
		pause();
	}
}
