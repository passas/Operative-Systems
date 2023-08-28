#include <unistd.h>
//pipe
#include <string.h>
//strcpy
#include <stdlib.h>
//exit
#include <stdio.h>
//perror

#include <sys/types.h>
#include <sys/wait.h>
//wait

#define BUS 4096

main ()
{
	size_t bytes;
	char buf[BUS];
	int pipe_fd[2];

	int lines;
	lines = 0;

	if ( pipe(pipe_fd) == -1 )
	{
		perror ("int pipe (int pipefd[2])");
		exit (-1);
	}
	
	if ( fork () == 0 )
	{
		close (pipe_fd[1]); //close writting pipe
		dup2 (pipe_fd[0], 0); //reading pipe from stdin

		while ( ( bytes = read (0, buf, BUS) ) > 0 )
		{
			for (int i=0; i<bytes; i++)
				if (buf[i]=='\n')
					lines++;
		}

		printf ("%d\n", lines);
		_exit (0); 
	}
	else
	{
		close (pipe_fd[0]);
		dup2 (pipe_fd[1], 1); //writting pipe in stdout
		close (pipe_fd[1]);	//close writting pipe

		while ( ( bytes = read (0, buf, BUS) ) > 0 )
			write (1, buf, bytes);
		close (1);	//close writting pipe

		wait (NULL);
	}
}
