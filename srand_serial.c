/*##########################################
Author: Surya Chigurupati
Project Name: Counting 3's (serial)
Description: Create an array of 5,000,000
             random numbers and count the
             3's in the array.
Class: Parallel Programming (Spring17)
Last Modified: 01/29/17 1:41 P.M.
##########################################*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
   int i, n, count;
   int *my_array;
   
   n = 5000000;

   my_array = (int *)malloc(sizeof(int)*5000000);
   
   /* Intializes random number generator */
   // This will give you random numbers but the same random numbers everytime.
   // srand(time(NULL)) will give you different random numbers everytime.
   srand(12345);
    
   count = 0;


   /* Print 5,000,000 random numbers from 0 to 100 */
   /* Count number of 3's in the array */
   for( i = 0 ; i < n ; i++ ) 
   {
        my_array[i] = rand() % 100;

        if(my_array[i]==3)
            count++;
   }

   /* Start clock */
   clock_t begin = clock();

   for( i = 0 ; i < n ; i++ ) 
   {

        if(my_array[i]==3)
            count++;
   }

   /* End clock */
   clock_t end = clock();

        /* Print the number of 3's */
        printf("\nNumber of 3's: " "%d\n" ,  count);


        /*Print how long the program took to run */
        printf("\nTime Elapsed: %f seconds\n", (double)(end - begin) / CLOCKS_PER_SEC);

   free(my_array);
   return count;
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

Average rumtime is 0.01090448 (tested 50 times)
#################################################*/



