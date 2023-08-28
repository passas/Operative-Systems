#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//open

#include <unistd.h>
//dup

#include <stdio.h>
//perror

#define BUS 4096

#define INPUT "stdin_stdout_stderr.c"
#define OUTPUT "output.txt"
#define ERRORS "errors.txt"

main ()
{
	size_t bytes;
	char buf[BUS];
	int input, output, error;

	input = open (INPUT, O_RDONLY);
	output = open (OUTPUT, O_WRONLY | O_CREAT, 0666);
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


	while ( (bytes = read (0, &buf, BUS)) > 0 )
	{
		write (1, buf, bytes);
	}

	close (input);
	close (output);
	close (error);
}
