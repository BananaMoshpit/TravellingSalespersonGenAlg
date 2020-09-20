// This is a mathematical algorithm known as Fisher-Yates Shuffling
// The following code was copied and adapted from:
//  https://www.geeksforgeeks.org/shuffle-a-given-array-using-fisher-yates-shuffle-algorithm/

#include <stdio.h> 
#include <stdlib.h> 
/* PATH SIZE IS ASSUMED 10 */

#include <time.h> 
  
// A utility function to swap to integers 
void swapPlaces (int *indexA, int *indexB) 
{ 
    int aux = *indexA; 
    *indexA = *indexB; 
    *indexB = aux; 
} 
  
// A utility function to print an array 
void printArray (int* chromossome) 
{ 
    int i;
    int size = sizeof(chromossome)/ sizeof(chromossome[0]);
    size = 10;
    for (int i = 0; i < size; i++) 
        printf("%d ", chromossome[i]); 
    printf("\n"); 
} 
  
// A function to generate a random permutation of chromossome* 
void FisherYatesShuffle(int** chromossome);

void FisherYatesShuffle(int** chromossome) 
{ 
    int size = 10;
    // int size = sizeof(chromossome)/ sizeof(chromossome[0]);

    int aux[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; 

    *chromossome = (int*)calloc( 20, sizeof(int) );
    *chromossome = aux;

    // Use a different seed value so that we don't get same 
    // result each time we run this program 
    srand ( time(NULL) ); 
  
    // Start from the last element and swap one by one. We don't 
    // need to run for the first element that's why i > 0 
    for (int i = size-1; i > 0; i--) 
    { 

        // Pick a random index from 0 to i 
        int j = rand() % (i+1); 
  
        // Swap chromossome[i] with the element at random index 
        swapPlaces( &(chromossome[0][i]), &(chromossome[0][j])); 
        
    } 
        // printArray(*chromossome);
        // printf("chromossome generated\n");

    

} 
  
// Driver program to test above function. 
int main() 
{ 
    int **population  ; 
    
    int chromossome[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; 
    int* ay;
    ay = chromossome;
    
    int i;
  
    population = (int**)malloc( sizeof(int*) * 20 );

    for ( i = 0 ; i < 10; i++)
    {
    
        FisherYatesShuffle(&(population[i])); 
        printArray(population[i]);
    
    }

//     for ( i = 0 ; i < 10; i++)
//     {
    
//         printArray(population[i]);
    
//     }
    return 0; 
} 
/*


p { population[1], population[2], population[3], population[4], population[5], population[6]}
 p chromossome




*/