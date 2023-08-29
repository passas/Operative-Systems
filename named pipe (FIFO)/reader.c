#include <sys/types.h>
#include <sys/stat.h>
//mkfifo

#include <fcntl.h>
//open

#include <unistd.h>
//read write

#include <stdlib.h>
//exit

#include <stdio.h>
//perror

#include <errno.h>
//errno

#define BUS 4906

main ()
{
       int fifo;
       size_t bytes;
       char buf[BUS];

       if ( mkfifo ("fifo", 0666) == -1)
       {
              perror ("mkfifo(char*, mode_t)");
              if (errno != EEXIST)
                     exit (-1);
       }

       fifo = open ("fifo", O_WRONLY);
       if (fifo == -1)
       {
              perror ("open (\"fifo\", O_WRONLY)");
              exit (-1);
       }

       while ( (bytes = read (0, buf, BUS)) > 0 )
       {
              write (fifo, buf, bytes);
       }

       close (fifo);

}
