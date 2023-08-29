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

       fifo = open ("fifo", O_RDONLY);
       if (fifo == -1)
       {
              perror ("open (\"fifo\", O_RDONLY)");
              exit (-1);
       }

       while ( (bytes = read (fifo, buf, BUS)) > 0 )
       {
              write (1, buf, bytes);
       }

       close (fifo);

}
