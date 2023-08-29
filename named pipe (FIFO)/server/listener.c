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
       size_t bytes;
       char buf[BUS];

       int sv_input,
           sv_output,
           sv_log;
       

       if ( mkfifo ("sv_input", 0666) == -1)
       {
              perror ("mkfifo(char*, mode_t)");
              if (errno != EEXIST)
                     exit (-1);
       }

       if ( mkfifo ("sv_output", 0666) == -1)
       {
              perror ("mkfifo(char*, mode_t)");
              if (errno != EEXIST)
                     exit (-1);
       }

       sv_input = open ("sv_input", O_RDONLY);
       if (sv_input == -1)
       {
              perror ("open (\"sv_input\", O_RDONLY)");
              exit (-1);
       }

       sv_output = open ("sv_output", O_WRONLY);
       if (sv_output == -1)
       {
              perror ("open (\"sv_output\", O_WRONLY)");
              exit (-1);
       }

       sv_log = open ("sv_log", O_WRONLY | O_APPEND | O_CREAT, 0666);
       if (sv_log == -1)
       {
              perror ("open (\"sv_log\")");
              exit (-1);
       }

       for (;;) //server
       {
              char *a = "queued\n"; //silly answear
              while ( (bytes = read (sv_input, buf, BUS)) > 0 ) //read request
              {
                     write (sv_log, buf, bytes); //execute action
                     //open fifo answear
                     write (sv_output, a, 7); //silly send
                     //close fifo answear
              }
       }

}
