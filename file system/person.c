#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//open
#include <unistd.h>
//lseek
//write
//read

#include <stdlib.h>
//atoi

#include <string.h>
//

#include <stdio.h>
//printf

#include "person.h"
//typedef struct person *Person;

static void insert (char name[], char age[]);
static void update (char name[], char age[]);
static void update_id (int id, char age[]);
static void cat ();

#define FILE_NAME "persons.bin"

int main (int argc, char *argv[])
{
	if (argc == 2)
	{
		if ( strcmp (argv[1], "-cat") == 0 ) //cat file into stdin
		{
			cat ();
		}
	}

	else if (argc == 4)
	{
		if ( strcmp (argv[1], "-i") == 0) //insert
		{
			insert (argv[2], argv[3]);
		}
	
		else if ( strcmp (argv[1], "-u") == 0 ) //update
		{
			int id;

			id = atoi (argv[2]);
			if (!id)
				update (argv[2], argv[3]);
			else
				update_id (id, argv[3]);
		}
	}

	_exit (0);
}

static void insert (char name[], char age[])
{
	int file;
	off_t byte;	//int
	ssize_t bytes; 
	struct stat file_stat;

	file = open (FILE_NAME, O_CREAT | O_CLOEXEC | O_WRONLY | O_APPEND, 0666);
	if (file == -1) //not opened
	{
		return;
	}

	else
	{
		int error;
		Person p; int id;

		if ( fstat(file, &file_stat) == 0 ) //success
			id = (file_stat.st_size / sizeof_Person ()) + 1;
		else
			id = 0;

		error = new_Person (id, atoi(age), name, &p);
		if (!error)
		{
			bytes = write (file, p, sizeof_Person());
		}

		if ( fstat(file, &file_stat) == 0 ) //success
		{
			printf ("register %ld\n", file_stat.st_size / sizeof_Person () );
		}
		close (file);
	}

}

static void update (char name[], char age[])
{
	int file;
	int error;
	ssize_t bytes;
	Person p;

	file = open (FILE_NAME, O_RDWR);
	if (file == -1)
	{
		return;
	}

	else {
		error = new_Person (0, 0, "", &p);

		if (!error)
		{
			while ( ( bytes = read (file, p, sizeof_Person()) ) > 0 )
			{
				if ( strcmp(getName_Person(p), name) == 0 ) //match
				{
					setAge_Person (atoi(age), &p);

					lseek (file, (-1) * sizeof_Person(), SEEK_CUR);
					bytes = write (file, p, sizeof_Person());
					if (bytes == -1)
					{
						printf ("error on update\n");
					}
					break; //end of read cycle / entry search
				}
			}
			free (p);
		}
	
		close (file);
	}
}

static void update_id (int id, char age[])
{
	int file;
	int error;
	ssize_t bytes;
	Person p;

	file = open (FILE_NAME, O_RDWR);
	if (file == -1)
	{
		return;
	}

	else {
		error = new_Person (0, 0, "", &p);

		if (!error)
		{
			lseek (file, (id-1) * sizeof_Person(), SEEK_SET);

			bytes = read (file, p, sizeof_Person());
			if (bytes)
			{
				setAge_Person (atoi(age), &p);

				lseek (file, (-1) * sizeof_Person(), SEEK_CUR);
				bytes = write (file, p, sizeof_Person());
				if (bytes == -1)
				{
					printf ("error on update\n");
				}
			}
			free (p);
		}
		close (file);
	}
}

static void cat ()
{
	int file;
	int error;
	ssize_t bytes;
	Person p; char *str;
	
	file = open (FILE_NAME, O_RDONLY, 0666);
	if (file == -1) //not openned
	{
		return;
	}

	else
	{
		error = new_Person (0, 0, "", &p);

		if (!error)
		{
			while ( ( bytes = read (file, p, sizeof_Person()) ) > 0 )
			{
				if ( str_Person (p, &str) == 0 )
				{
					//sprintf (str, "%s\n", str);
					//write (STDIN_FILENO, str, strlen(str));
					printf ("%s\n", str);
					free (str);
				}
			}
			free (p);
		}
	
		close (file);
	}
}
