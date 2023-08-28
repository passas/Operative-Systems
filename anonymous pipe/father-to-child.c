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
	int status;
	size_t byte;
	char buf[BUS];
	int pipe_fd[2];

	if ( pipe(pipe_fd) == -1 )
	{
		perror ("int pipe (int pipefd[2])");
		exit (-1);
	}

	if ( fork () == 0 )
	{
		//close (pipe_fd[1]);
		byte = read (pipe_fd[0], buf, 21);
		write (1, buf, byte);

		_exit (0);
	}
	else
	{
		char *b = "hello. from: father\n"; //21 char's

		strcpy (buf, b);
		write (pipe_fd[1], buf, 21);
		//close (pipe_fd[1]);
		
		wait (&status);
	}
}
