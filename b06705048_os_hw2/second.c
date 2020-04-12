#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int input = 0;
int incircle  = 0;

void *count(void *X)
{ 
    /* initialize random numbers */
    for (int i = 0; i < input; i++)
    {	
        double X = (double) rand() / RAND_MAX;
        double Y = (double) rand() / RAND_MAX;
    //    printf("%f\n", X);
    //    printf("%f\n", Y);

        if (X * X + Y * Y <= 1)// use pow() need: gcc xxx.c -lm -o xxx
            incircle++;
    }
    return NULL;
}

int main()
{
    srand(time(NULL));
    pthread_t thread;
    do
	{
        printf("Please enter a positive number for the amount of points\n");
        scanf("%d", &input);  	
	}
    while (input <= 0);
   
  
    pthread_create(&thread, NULL, &count, NULL);
    pthread_join(thread, NULL);

    double pi = 4.0 * incircle / input;
    printf("The approximate value of pi for the desired amount of points (%d) is: %f \n", input, pi);  
    return 0;
}