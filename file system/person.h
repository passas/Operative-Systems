#ifndef PERSON_H
#define PERSON_H

typedef struct person *Person;

/*
* Byte size of the struct.
*/size_t sizeof_Person ();

/*
* It allocates memory to a Person.
*
* @ret 0: succsessfull, p have a new Person.
* @ret 1: memory allocation failed, p have a NULL pointer.
*/int new_Person (int id, int age, const char *name, Person *p);

/*
* Returns the intern name of a Person. The original address!
*/char *getName_Person (Person p);

/*
* Set the age of a Person/
*/void setAge_Person (int age, Person *p);

/*
* It allocates a string in memory and passes it in arg str.
*
* @arg str A pointer to the string allocation.
*
* @ret -1: no Person to string
* @ret 0: susccess, str suffered an allocation!
* @ret 1: allocation failed
*/int str_Person (Person p, char **str);

#endif
