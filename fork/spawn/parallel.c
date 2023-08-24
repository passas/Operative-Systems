/*
 1 x (x1 father x10 child) parallel-descendent
*/

#include <unistd.h>
#include <sys/wait.h>

#include <stdio.h>
//printf

#define MAX 10

main ()
{
	pid_t child;
	int status;
	int n;

	n=0;
	for (int i=0; i<MAX; i++)
	{
		++n;
		if ( fork () == 0 )
		{	//son
			printf ("-(%d) dad: %d\n", getpid(), getppid());

			_exit (n);
		}
	}

	//dad
	for (int i=0; i<MAX; i++)
	{	
		child = wait (&status);
		
		if (WIFEXITED(status))
			printf ("(%d) Wait: son=%d status=%d\n", getpid(), child, WEXITSTATUS(status));
	}
}
