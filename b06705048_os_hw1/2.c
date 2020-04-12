#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>


int main()
{
	pid_t  pid;
    const int SIZE = 4096;
    const int buffer_size = SIZE/4;
    const char *name = "OS";

    int input = 0;
    while(input == 0 || input < 0)
    {
        printf("Enter a positive number. ");
        scanf("%d", &input);
        if(input < 0 || input == 0)
            printf("It is not a positive number.\n");
    }
    int shm_fd; 	// shared memory file descriptor
    int *ptr; 	// pointer to shared memory object

    shm_fd = shm_open(name, O_CREAT |O_RDWR, 0666);
    ftruncate(shm_fd,SIZE);
    ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

	pid = fork(); /* fork another process */

	if (pid < 0)  /* error occurred */
    { 
		fprintf(stderr, "Fork Failed\n");
		return 1;  // exit(1);
	}
	else if (pid == 0)  /* child process */
    { 
    //    printf("child process is working... \n");

        ptr[0] = 0; // length - 1 
        int* index = &ptr[0];

        ptr[1] = input;
        ++(*index);       

        while (ptr[*index] != 1)
	    {
            if(((*index) + 1)  == buffer_size)
            {
                printf("Too many computation to show.(run out of shared-memory)\n");
                printf("%d",*index);
                break;
            }

		    if (ptr[*index] % 2 == 0)
			    ptr[(*index)+1] = ptr[*index]/2;	
		    else 
                ptr[(*index)+1] = 3 * ptr[*index] + 1;
            ++(*index);
	    }	      
	}
	else /* parent process */
    { 
		/* parent will wait for the child to complete */
		wait(NULL);
        shm_fd = shm_open(name, O_RDONLY, 0666);
        ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
        

        int now = 0;
        while(now != ptr[0])
        {
            now++;
            printf("%d", ptr[now]);
            if(now != ptr[0])
                printf(",");    
        }
        printf("\n"); 
        shm_unlink(name);
	}	
	return 0; // exit(0);
}
