#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define NR_PTS 10000000
#define NR_THREADS 10
#define NR_PTRS_PER_THREAD NR_PTS/NR_THREADS



long circleCount = 0;	/* Global Circle Count */
pthread_t *threads;		/* Thread Identifier Decleration */
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; /* Mutex init */


void *monteCarloPi(void *thread_ID) {

						
	int a =  (int)thread_ID;		/* This threads # */
	long incircle_thread = 0; 		/* # of points in this threads circle */
	unsigned int rand_state = rand(); /* Random Generator */
	
	/* Create NR_PTRS_PER_THREAD # of points */
	for (int i = 0; i < NR_PTRS_PER_THREAD; i++) 
    {
		
    	double x = rand_r(&rand_state) / ((double)RAND_MAX + 1) * 2.0 - 1.0;
		double y = rand_r(&rand_state) / ((double)RAND_MAX + 1) * 2.0 - 1.0;

    //   double x = (double) rand() / RAND_MAX;
    //   double y = (double) rand() / RAND_MAX;	
		
        /* If current point is within the circle */
		if (x * x + y * y < 1) 
        {	
			/* Increase # incircle count */
			incircle_thread++;			
		}
	}

	/* calculate this threads approximation of Pi */
	float Pi = (4. * (double)incircle_thread) / 
				((double)NR_PTRS_PER_THREAD * 1);

	/* Report to the console, this threads calculation of Pi */
	printf("Thread [%d] Reports Pi to be [%f]\n" ,a,Pi);

		pthread_mutex_lock(&mutex);

		circleCount += incircle_thread;

		pthread_mutex_unlock(&mutex);

return NULL;
}


void createThreads(){
	
	int  s; /* Declare Count and ErrorNumber variables */

	threads = malloc(NR_THREADS * sizeof(pthread_t)); /* Allocate space for next thread */

	pthread_attr_t attr; /* Pthread attribute init */
		
	pthread_attr_init(&attr); /* Pthread attribute init */
	
	printf("\n----------------------------------------\n*Creating [%d] Threads\n\n", NR_THREADS);
	
    /* Create 1 thread for each NR_THREADS */
	for (int i = 0; i < NR_THREADS; i++) 	
		s = pthread_create(&threads[i], &attr, monteCarloPi,  (void *) i);

}


void joinThreads(){

	int s; /* Declare Count and Error # Variable
		
	/* Join 1 thread for each NR_THREADS */
	for (int i = 0; i < NR_THREADS; i++) 	
		s = pthread_join(threads[i], NULL);	

	/* Destroy mutex */
	pthread_mutex_destroy(&mutex);
	
	/* Prompt user, all threads joined */
	printf("\n*[%d] Threads Rejoined\n\n", NR_THREADS);
	
	/* Free allocated space used by threads */
	free(threads);
}


int main() {

	float Pi; /* Declare float for final Pi calculation */

	createThreads(); /* Create threads */

	joinThreads(); /* Join threads */
	
	/*Calculate Pi using Monte Carlo method and Global incircle count*/
	Pi = (4. * (double)circleCount) / ((double)NR_PTRS_PER_THREAD * NR_THREADS);
	
	/* Prompt user with final approximation of Pi */
	printf("Final Estimation of Pi: %f\n\n----------------------------------------\n", Pi);
	
return 0;

}