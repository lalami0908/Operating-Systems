#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>
 
void *avg_func(void *ptr);
void *min_func(void *ptr);
void *max_func(void *ptr);

int cnt = 0;
int avg = 0;        
int min = INT_MAX;
int max = INT_MIN;

int main(int argc, char *argv[])
{
    while(argc <=1)
    {
        printf("Incorrect input. Please enter one or more inputs.\n");
        exit(0);
	}

    cnt = argc-1;
    int* copy = (int *)malloc(cnt * sizeof(int));


    for(int i = 0 ; i < (argc -1); i++)
        copy[i] = atoi(argv[i+1]);
    
        
    pthread_t thread1, thread2, thread3;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
   
    /* Create independent threads each of which will execute appropriate function*/
    pthread_create(&thread1, NULL, avg_func, (void *)copy);
    pthread_create(&thread2, NULL, min_func, (void *)copy);
    pthread_create(&thread3, NULL, max_func, (void *)copy);
   
    /* Wait till threads are complete before main continues. */
 
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
 
    printf("The average:  %d\n", avg);
    printf("The minimum:  %d\n", min);
    printf("The maximum:  %d\n", max);
 
    exit(EXIT_SUCCESS);
}
 
void *avg_func(void *ptr)
{
    int* copy = (int*) ptr;
    for(int i = 0; i < cnt; i++)
        avg += copy[i];    
                                  
    avg = avg / cnt;         
}

void *min_func(void *ptr)
{
    int* copy = (int*) ptr;
    for(int i = 0; i < cnt; i++)
    {
        if(min > copy[i])
            min = copy[i];
    }
}

void *max_func(void *ptr)
{
    int* copy = (int*) ptr;
    for(int i = 0; i < cnt; i++)
    {
        if(max < copy[i])
            max = copy[i];
    }
}