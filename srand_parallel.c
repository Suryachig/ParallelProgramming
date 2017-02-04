/*##########################################
Author: Surya Chigurupati
Project Name: Counting 3's (parallel)
Description: Create an array of 5,000,000
             random numbers and count the
             3's in the array by seperating 
             the array into different threads.
Class: Parallel Programming (Spring17)
Last Modified: 01/31/17 12:50 P.M.
##########################################*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#define MaxTh 8

void count3s_thread(int id);
pthread_t tid[MaxTh];

int t;
int *my_array;
int length;
int count;

struct padded_int
{
  int value;
  char padding[60];
} private_count[MaxTh];

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void count3s()
{
   int i;
   count = 0;
   /* Create t threads */
   for(i = 0; i < t; i++)
   {
      pthread_create(&tid[i], NULL, count3s_thread, i);
   }

   /* Wait for the threads to finish */
   for(i = 0; i < t; i++)
   {
      pthread_join(tid[i], NULL);
   }
}

void count3s_thread(int id)
{
   int i;
   /* Divide 5,000,000 by number of threads */
   int threadL = length / t;
   int start = id * threadL;

   /* Count number of 3's */
   for(i = start; i < start+threadL; i++)
   {
      if(my_array[i] == 3)
      {
         private_count[id].value++;
      }
   }
   /* Get count of 3's from each thread and add them up */
   pthread_mutex_lock(&m);
   count += private_count[id].value;
   pthread_mutex_unlock(&m);

}


int main( )
{
   int i;
   /* Declare array size */
   length = 5000000;
   t = 8;

   my_array = (int *)malloc(sizeof(int)*5000000);

   /* Intializes random number generator */
   // This will give you random numbers but the same random numbers everytime.
   // srand(time(NULL)) will give you different random numbers everytime.
   srand(12345);

   for(i = 0; i < length; i++)
   {
      my_array[i] = rand()% 100;
   }

   /* Start Clock */
   clock_t begin = clock();

   /* Run the threads, wait till they finish */
   count3s();

 /* End clock */
 clock_t end = clock();


    /* Print the number of 3's */
    printf("The number of 3's is %d\n", count);



    /*Print how long the program took to run */
    printf("\nTime Elapsed: %f seconds\n", (double)(end - begin) / CLOCKS_PER_SEC);

   return 0;
}


/*########################################################
            Computer configuration
   64-bit
   CPU(s): 4
   Thread(s) per core: 2
   Core(s) per socket: 2
   Socket(s): 1
   Vendor ID: GenuineIntel
   Model Name: Intel(R) Core(TM) i7-5500U CPU @ 2.40GHz
########################################################*/

/*###############################################
      Performance Graph

Average rumtime serial is 0.01090448 (tested 50 times)
Average rumtime T2 is 0.01141862 (tested 50 times)
Average rumtime T4 is 0.0105332 (tested 50 times)
Average rumtime T8 is 0.00800096 (tested 50 times)
#################################################*/

