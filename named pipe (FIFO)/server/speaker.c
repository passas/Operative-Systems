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

#include <string.h>
//strlen

#define BUS 4906

main (int argc, char *argv[])
{      
       size_t bytes;
       char buf[BUS];

       int sv_input,
           sv_output;

       sv_input = open ("sv_input", O_WRONLY);
       if (sv_input == -1)
       {
              perror ("open (\"sv_input\", O_WRONLY)");
              exit (-1);
       }

       sv_output = open ("sv_output", O_RDONLY);
       if (sv_output == -1)
       {
              perror ("open (\"sv_output\", O_RDONLY)");
              exit (-1);
       }

       //request
       write (sv_input, argv[1], strlen(argv[1]));

       //answear
       bytes = read (sv_output, buf, BUS);
       
       //answear received -> terminal
       write (1, buf, bytes);

       //end connection
       close (sv_output);
       close (sv_input);
}
