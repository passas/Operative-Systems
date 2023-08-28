#include <stdlib.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>
//dup

#include <stdio.h>
//perror

#define BUS 4096

#define INPUT "dup-fork.c"
#define OUTPUT "output.txt"
#define ERRORS "errors.txt"

main ()
{
	int status;
	size_t bytes;
	char buf[BUS];
	int input, output, error;

	input = open (INPUT, O_RDONLY);
	output = open (OUTPUT, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	error = open (ERRORS, O_WRONLY | O_CREAT, 0666);

	if ( input == -1)
	{
		perror (INPUT);
		exit (-1);
	} 
	if ( output == -1)
	{
		perror (OUTPUT);
		close (input);
		exit (-1);
	}
	if ( error == -1)
	{
		perror (ERRORS);
		close (input);
		close (output);
		exit (-1);
	}

	if ( dup2 (input, 0) != STDIN_FILENO )
	{
		perror ("STDIN duplication");
		close (input);
		close (output);
		close (error);
		exit (-1);
	}
	if ( dup2 (output, 1) != STDOUT_FILENO )
	{
		perror ("STDOUT duplication");
		close (input);
		close (output);
		close (error);
		exit (-1);
	}
	if ( dup2 (error, 2) != STDERR_FILENO )
	{
		perror ("STDERR duplication");
		close (input);
		close (output);
		close (error);
		exit (-1);
	}

	if (fork()==0)
	{	while ( (bytes = read (0, &buf, BUS)) > 0 )
		{
			write (1, buf, bytes);
		}
		_exit( 0 );	//implicit close fd's
	}
	else
	{
		wait (&status);
		
		//char *welcome = "\n- stdin -\n";
		//write (1, welcome, BUS);	
		//write (1, welcome, 12);
	}

}
