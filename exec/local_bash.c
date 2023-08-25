#include <stdlib.h>
//malloc

#include <unistd.h>
//read
//execvp

#include <stdio.h>
//printf

#include <errno.h>
//errno

#include <sys/wait.h>
//wait

#define N 48
#define BUS 512

static void buf_to_argv (char *buf, char **argv);

main ()
{
	char *buf, **argv;
	ssize_t bytes;
	int status;

	buf = (char *) malloc (sizeof (char) * BUS);
	while ( (bytes = read(STDIN_FILENO, buf, BUS)) > 0 )
	{
		if (fork() == 0)
		{
			argv = (char**) malloc (sizeof (char *) * N);
			buf_to_argv (buf, argv);

			if ( execvp(argv[0], argv) )
			{
				printf ("execvp: error\n");
				_exit (errno);
			}
		}
		else
		{
			wait (&status);
		}
	}

	if ( bytes == -1 )
	{	//error on read
		printf ("read -> -1\n");
	}
}

static void buf_to_argv (char *buf, char **argv)
{
	int i, j;
	int word, low;
	int *flag_alloc;

	flag_alloc = &j;
	word = 0;
	for (i=j=0; word<N && i<BUS; i++)
	{
		if ((*flag_alloc) == 0)
		{
			argv[word] = malloc (sizeof (char) * BUS);
		}

		if (buf[i] == ' ')
		{
			argv[word][j] = '\0';
			word++;
			j = 0;
		}
		else if (buf[i] == '\n')
		{
			argv[word][j] = '\0';
			word++;
			break;
		}
		else
		{
			argv[word][j++] = buf[i];
		}
	}
}
