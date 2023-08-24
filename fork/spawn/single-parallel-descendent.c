/*
 x10 single-descendent
*/

#include <unistd.h>
#include <sys/wait.h>

#include <stdio.h>
//printf

#define MAX 10

void _fork (int n)
{
	if (n<=MAX)
	{	
		if ( fork () == 0 )
		{
			printf ("-(%d) dad: %d\n", getpid(), getppid());
			_fork (n+1);
			_exit (n);
		}
		else
		{ //dads
			pid_t child;
			int status;

			child = wait (&status);
			
			if (WIFEXITED(status))
				printf ("(%d) Wait: son=%d status=%d\n", getpid(), child, WEXITSTATUS(status));
		}
		
	}
	else
	{
		return;
	}
}
main ()
{
	pid_t child;
	int status;
	int n;

	n = 1;
	_fork (n);
}
