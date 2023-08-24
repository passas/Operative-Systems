#include <unistd.h>
#include <sys/wait.h>

#include <stdlib.h>
//malloc
//free

#include <stdio.h>
//printf

#define I 100
#define J 10000000//0

typedef struct matrix
{
	int **m;	
} Matrix;

void init_Matrix (Matrix *m);
void putit_Matrix (int i, int j, Matrix *m);
void free_Matrix (Matrix *m);

main ()
{
	//Setting playfield
	Matrix m;
	int i, j; int space;

	init_Matrix (&m);	//all 0's
	// m[i][j] = 1;
	for (space = 2, i=I-2, j=J-2; i>=0 && j>=0 ; i-=space ,j-=space)
	{
		putit_Matrix (i, j, &m);
		printf ("m[%d][%d] = %d;\n", i, j, m.m[i][j]);
		space *= 2;
	}

	//Program itself
	int N;
	int child, status;

	N = I;
	for (i=0; i<N; i++)
		if ( fork () == 0 )
		{
			//printf ("-(%d) m[%d][] searching...\n", getpid(), i);
			for (j=0; j<J; j++)
				if (m.m[i][j] == 1)
					_exit (1);	//end son
			_exit (0);	//end son
		}

	//dad only
	for (int i=0; i<N; i++)
	{	
		child = wait (&status);
		
		if (WIFEXITED(status))
			printf ("(%d) Wait: son=%d status=%s\n", getpid(), child, WEXITSTATUS(status)==1?"found":"not found");
	}

	free_Matrix (&m);

}

void init_Matrix (Matrix *m)
{
	(*m).m = (int **) malloc (sizeof (int*) * I);
	for (int i=0; i<I; i++)
	{
		(*m).m[i] = (int *) malloc (sizeof (int) * J);
		for (int j=0; j<J; j++)
			(*m).m[i][j] = 0;
	}
}

void putit_Matrix (int i, int j, Matrix *m)
{
	(*m).m[i][j] = 1;
}

void free_Matrix (Matrix *m)
{
	for (int i=0; i<I; i++)
		free ( (*m).m[i] );
	free ( (*m).m );
}
