#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int main()
{
	pid_t  pid;

    int input = 0;


    while(input == 0 || input < 0)
    {
        printf("Enter a positive number. ");
        scanf("%d", &input);
        if(input < 0 || input == 0)
            printf("It is not a positive number.\n");

    }

	pid = fork(); /* fork another process */

	if (pid < 0)  /* error occurred */
    { 
		fprintf(stderr, "Fork Failed\n");
		return 1;  // exit(1);
	}
	else if (pid == 0)  /* child process */
    { 
    //    printf("child process is working... \n");
		   
        printf("%d",input);
        if(input != 1)
            printf(",");
        

        while (input != 1)
		{
		    if (input % 2 == 0)
			    input = input/2;	
			else 
				input = 3 * input + 1;
			printf("%d",input);
            
            if(input != 1)
                printf(",");
		}	
        printf("\n");	
	//	printf("Children processes is done.\n");

	}
	else /* parent process */
    { 
		/* parent will wait for the child to complete */
		wait(NULL);
		
    //    printf ("Parent process is done.\n");
	}	
	return 0; // exit(0);
}
