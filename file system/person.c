#include <stdlib.h>
//malloc
//free

#include <string.h>
//strlen
//strdup

#include <stdio.h>
//sprintf

#include "person.h"
//typedef struct person *Person;

struct person
{
	int id;
	char name[75];
	int age;	
};

size_t sizeof_Person ()
{
	return sizeof (struct person);
}

int new_Person (int id, int age, const char *name, Person *p)
{
	int error;
	Person r;

	error = 0;
	r = (Person) malloc (sizeof (struct person));
	if (r)
	{
		r->id = id;
		r->age = age;
		strcpy (r->name, name);
		
		(*p) = r;
	}
	else {
		error = 1;
		(*p) = NULL;
	}

	return error;
}

char *getName_Person (Person p)
{
	return p->name;
}

void setAge_Person (int age, Person *p)
{
	(*p)->age = age;
}

int str_Person (Person p, char **str)
{
	int error;
	char *r;

	error = 0;
	if (!p)
	{
		error = -1;
	}
	else
	{
		r = malloc (sizeof (char) * 200);
		if (!r)
		{
			error = 1;
			(*str) = NULL;
		}
		else
		{
			sprintf (r, "%d: %s %d", p->id, p->name, p->age);
			(*str) = r;
		}
	}

	return error;
}
