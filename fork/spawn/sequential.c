/*
 10 x (x1 father x1 child) single-descendent
*/

#include <unistd.h>
#include <sys/wait.h>

#include <stdio.h>
//printf

#define MAX 10

main ()
{
	pid_t pid, child;
	int status;
	int n;

	n=0;
	for (int i=0; i<MAX; i++)
	{	
		++n;
		if ( (pid = fork ()) == 0 )
		{	//son
			printf ("-(%d) dad: %d\n", getpid(), getppid());

			_exit (n);
		}
		else
		{	//dad
			child = wait (&status);
			
			if (WIFEXITED(status))
				printf ("(%d) Wait: son=%d status=%d\n", getpid(), child, WEXITSTATUS(status));
		}
	}

}
