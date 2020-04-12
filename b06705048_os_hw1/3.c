#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> //for function write

#include<sys/stat.h>
#include<fcntl.h> // for function open()
#include<stdlib.h>


#define BUFFER_SIZE 1000
#define READ_END 0
#define WRITE_END 1

int main(int argc, char *argv[])
{
   char write_msg[BUFFER_SIZE];
   char read_msg[BUFFER_SIZE];
   int fd[2];
   pid_t pid;

   // create a pipe
   if(pipe(fd) == -1) 
   {
      fprintf(stderr, "Pipe failed");
      return 1;
   }

   if( argc != 3 ) 
   {
      printf( "Enter two file names." );
      exit(1);
   }
   int copyFile = open( argv[1], O_RDONLY ); 
   int targetFile = open( argv[2], O_CREAT |  O_WRONLY, 0666); 

   if ( copyFile  == -1 || targetFile == -1) 
   {
      printf( "Opening file failed." );
      exit(1);
   }

   pid = fork ();

   if (pid < 0) 
   {
      fprintf(stderr, "Fork failed");
      return 1;
   }

   if(pid > 0) 
   {  // parent process
      close(fd[READ_END]);
   //   printf("parent sending message\n");


      while( read( copyFile, write_msg, BUFFER_SIZE) > 0 )  // read from the copyFile
      {
         write(fd[WRITE_END], write_msg, strlen(write_msg) + 1); // write into the pipe
      }

      close(fd[WRITE_END]);
   } 
   else 
   {  // child process
      close(fd[WRITE_END]);
      read(fd[READ_END], read_msg, BUFFER_SIZE); // read from the pipe
    //  printf("read %s\n", read_msg);
      //Writing to the target fileOpen
      write( targetFile, read_msg, strlen(read_msg)); // write into the targetFile
      close(fd[READ_END]);
   }
   return 0;
}
