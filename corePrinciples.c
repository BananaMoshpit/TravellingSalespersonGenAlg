// This is a mathematical algorithm known as Fisher-Yates Shuffling
// The following code was copied and adapted from:
//  https://www.geeksforgeeks.org/shuffle-a-given-array-using-fisher-yates-shuffle-algorithm/

#include <stdio.h> 
#include <stdlib.h> 
/* PATH SIZE IS ASSUMED 10 */

#include <time.h> 
  

// C Program to shuffle a given array 
  
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
  
// A utility function to swap to integers 
void swap (int *a, int *b) 
{ 
    int temp = *a; 
    *a = *b; 
    *b = temp; 
} 
  
// A utility function to print an array 
void  printArray(int* arr, int arraySize) 
{ 
    for (int i = 0; i < arraySize; i++) 
        printf("%d ", arr[i]); 
    printf("\n"); 
} 
  
// A function to generate a random permutation of arr[] 
void randomize ( int **chromossome, int arraySize ) 
{   
    // int arr[9] = {1, 2, 3, 4, 5, 6, 7, 8}; 

    // chromossome = arr;
    
//    if ( !(*chromossome = calloc( arraySize, sizeof(int) )) )
//     printf("ERROR \n");
    
    for (int i = 0; i < arraySize; i++)
    {
        (*chromossome)[i] = i;
    }
    

    
    // Use a different seed value so that we don't get same 
    // result each time we run this program 

  
    // Start from the last element and swap one by one. We don't 
    // need to run for the first element that's why i > 0 
    for (int i = arraySize-1; i > 0; i--) 
    { 
        // Pick a random index from 0 to i 
        int j = rand() % (i+1); 
  
        // Swap chromossome[i] with the element at random index 
        swap(&chromossome[0][i], &chromossome[0][j]); 
    } 
    // chromossome = arr;

    printArray( *chromossome, arraySize);
    
} 
  
// Driver program to test above function. 
int main() 
{
    int arraySize = 10; 
    int** population;
    int populationSize = 1000;
    
    
    population = (int**)malloc(sizeof(int*) * populationSize);

    for (int i = 0; i < populationSize; i++)
    {
        if ( population[i] = calloc( arraySize, sizeof(int) ) ){
            randomize(&population[i], arraySize);
            // printArray( population[i] , arraySize );   
        }
    }

    return 0; 
} 

/*


p { population[1], population[2], population[3], population[4], population[5], population[6]}
 p chromossome




*/