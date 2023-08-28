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

	if ( pipe(pipe_fd) == -1 )
	{
		perror ("int pipe (int pipefd[2])");
		exit (-1);
	}

	if ( fork () == 0 )
	{
		close (pipe_fd[0]);

		while ( ( bytes = read (0, buf, BUS) ) > 0 )
			write (pipe_fd[1], buf, bytes);
		close (pipe_fd[1]);

		_exit (0);
	}
	else
	{
		close (pipe_fd[1]);

		while ( ( bytes = read (pipe_fd[0], buf, BUS) ) > 0 )
			write (1, buf, bytes);
		close (pipe_fd[0]);

		wait (NULL);
	}
}
