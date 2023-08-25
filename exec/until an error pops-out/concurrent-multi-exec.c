#include <sys/types.h>
#include <unistd.h>
//fork

#include <unistd.h>
//execl

#include <sys/wait.h>
//wait

#include <stdio.h>
//printf

int get_prog (int pid, int prog[], int n);

/* This program only contemples a finite number of arguments.
* It it passed in a static environment.
*/main (int argc, char *argv[])
{
	int i;				//index for argv[][]
	int status; 		//status of exit processes

	int times[argc];	//number of executions
	int pid,			//child process id
		prog,			//argv[prog]
		prog_pid[argc]; //prog -> pid :to save the work of an HashTable (should it be pid -> prog)

	//init aux data struct.
	for (i=1; i<argc; i++)
	{
		times[i] = 0;
		prog_pid[i] = -1;
	}
	
	for (i=1; i<argc; i++)
	{   //spawn argc-1 processes: concurrency
		if ( (pid = fork()) == 0 )
		{	
			//exec program
			if ( execl (argv[i], argv[i], NULL) )
				_exit (1); //error
			else 
				_exit (0); //success
		}
		else
		{	//father increases prog. execution
			times[i]++;
			//father associate prog. to a pid
			prog_pid[i] = pid;
		}
	}
	
	
	i=1;
	while ( i<argc )
	{ //wait for argc-1 spawned processes: concurrency
		pid = wait (&status);

		if ( WIFEXITED(status) && WEXITSTATUS(status) == 0)
		{	//child exited with success code => execl does not returned
			//wich prog. shall be re-executed?
			prog = get_prog (pid, prog_pid, argc);
			if (prog != -1)
			{	//spawn child
				if ( (pid = fork()) == 0 )
				{
					if ( execl (argv[prog], argv[prog], NULL) )
						_exit (1); //error
					else 
						_exit (0); //success
				}
				else
				{	//father increases prog. execution
					times[prog]++;
					//father re-associate prog. to a pid
					prog_pid[prog] = pid;
				}
			}
			else
			{ //prog not found
				i++;	//decrease number of waiting processes
			}
		}
		else	
		{ //child exited with code error => execl returned
			i++; 		//decrease number of waiting processes
		}

	}

	//the number of times that wich prog. executed
	for (i=1; i<argc; i++)
		printf ("%s %d\n", argv[i], times[i]);
}

/*
* To avoid implement an HashTable,
*this function implements a transitive way to map a pid into a program,
*with a data structure that maps a program into a pid.
*
* @ret -1 		 : no mapping
* @ret  1<=i<argc: mapping
*/int get_prog (int pid, int prog[], int n)
{
	int i;
	for (i=1; i<n; i++)
		if (prog[i]==pid)
			return i;
	return -1;
}
