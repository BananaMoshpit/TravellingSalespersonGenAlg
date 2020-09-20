#include<stdlib.h>
#include<stdio.h>
#include<time.h>

//chromossome has only 10 but fitness adds return
typedef struct  chromossome  {

int path[10];
long double fitness;
long double probability;
int length;

struct chromossome* next;
int chromossomeKey;
}chromossome;

typedef struct population{
    struct chromossome** chromossomes;
    int populationSize;
}population;



//A matrix containing the distances between every city
// Each index is a city as follows: SP BA RJ Lima Bog. Sant. Carac. BH PoA BsB
int distances [10][10] = { 
 
    {  -1, 17, 3 , 35, 43, 26, 44, 5 , 8 , 9    }, // 0 = SP
    {  17, -1, 20, 31, 47, 11, 51, 22, 8 , 23   }, // 1 = Ba
    {  3 , 20, -1, 38, 45, 29, 45, 3 , 11, 9    }, // 2 = RJ
    {  35, 31, 38, -1, 19, 25, 27, 36, 33, 32   }, // 3 = Lima
    {  43, 47, 45, 19, -1, 43, 10, 43, 46, 37   }, // 4 = Bogotá
    {  26, 11, 29, 25, 43, -1, 49, 30, 19, 30   }, // 5 = Santiago
    {  44, 51, 45, 27, 10, 49, -1, 42, 48, 35   }, // 6 = Caracas
    {  5 , 22, 3 , 36, 43, 30, 42, -1, 13, 6    }, // 7 = BH
    {  8 , 8 , 11, 33, 46, 19, 48, 13, -1, 16   }, // 8 = Pot.Alegre 
    {  9 , 23, 9 , 32, 37, 30, 35, 6 , 16, -1   }, // 9 = Brasília
    // 0   1   2   3   4   5   6   7   8   
                            } ;

//creates given number of random chromossomes
chromossome* initiatePopulation(population *start);

//calculates specific fitness relative to the sum of all path lengths 
//recursive, sum on the way, fitness on the back (specific/total length)
// int evaluateFitnessAndProbability(chromossome* path, int fitnessSum);

// prints chromossome as a path between cities
void printPath(chromossome* path);


chromossome* ANSWER = NULL;
int SHORTESTPATH = 100000;



// helper functions

        // A utility function to print an array 
        void printArray (int* array) ;
        void printArray (int* array) 
        { 
            int size = sizeof(array)/ sizeof(array[0]);
            size = 10;
            for (int i = 0; i < size; i++) 
                printf("%d ", array[i]); 
            printf("\n"); 
        } 

        void printChromossome (chromossome* chromossome) {
        
            printArray( chromossome->path );
            printf(" key:%d fitness:%Lf length:%d probability: %Lf \n", chromossome->chromossomeKey,chromossome->fitness, chromossome->length, chromossome->probability);

        }


        chromossome* createCromossome( );
        void destroyCromossome();

        // A utility function to swap to integers 
        void swapPlaces (int *indexA, int *indexB) ;
        void swapPlaces (int *indexA, int *indexB) 
        { 
            int aux = *indexA; 
            *indexA = *indexB; 
            *indexB = aux; 
        } 



        // A function to generate a random permutation of chromossome* 

// Utility function to alocate chromossomes      
        chromossome* createCromossome(chromossome** new){

            (*new) = (chromossome*)malloc(sizeof(chromossome)) ;


            if( (*new) == NULL )
                printf("Warning: Can't alocate struct. Is the memory sufficient?");

            else
            {
                (*new)->fitness = 0;
                (*new)->probability = 0;
                (*new)->next = NULL;

                for (int i = 0; i < 10; i++)
                {
                    (*new)->path[i] = i;
                }
                
            }

            return *new;
        }


//main functions



chromossome* initiatePopulation (population *start);
chromossome* initiatePopulation (population *start){

    chromossome** chromossome ;
    int i, size = 10;

    printf(">>initiaTINg population\n");

    // Use a different seed value so that we don't get same 
    // result each time we run this program 
    srand ( (long) time(NULL) );

    start->chromossomes = malloc(sizeof(int) * start->populationSize);

     chromossome = (start->chromossomes);
    //Alocates given number of chromossomes
    for ( i = 0; i < start->populationSize; i++)
    {
        createCromossome( chromossome );
        (*chromossome)->chromossomeKey = start->populationSize -i;

        // Start from the last element and swap one by one. We don't 
        // need to run for the first element that's why i > 0 
        for (int i = size-1; i > 0; i--) 
        { 
            // Pick a random index from 0 to i 
            int j = rand() % (i+1); 
    
            // Swap chromossome[i] with the element at random index 
            swapPlaces(&(*chromossome)->path[i], &(*chromossome)->path[j]); 
        } 

        printArray((*chromossome)->path);
        chromossome = &(*chromossome)->next;    /*CAN USE INDEX*/
    }

    // &start->chromossomes
    
    
}

//Reads chromossome->path, seeks data on distances matrix and sums path distance
// sets individuals fitness ( 1/length ) on the way to the last chromossome
// sets idividual probability on the way back
long double evaluateFitnessAndProbability(chromossome* chromossome, long double fitnessSum);
long double evaluateFitnessAndProbability(chromossome* chromossome, long double fitnessSum){
    double length = 0;
    int fromCity;
    int toCity;

printf(">>Evaluating fitness/probability\n");
    if (chromossome != NULL){
        
        
//calculates length of chromossome
        for (int i = 0; i < 9; i ++ )
        {
            fromCity = chromossome->path[i] ;
            toCity = chromossome->path[i + 1] ;
            length += distances [ fromCity ] [ toCity ] ;

        }
        //considers return to original city
        fromCity = chromossome->path[0];
        length += distances [toCity] [fromCity];
        chromossome->length = length;           //needless?

//chromossome is marked as answer if it's the smallest one
        if ( length < SHORTESTPATH ) {
            SHORTESTPATH = length;
            ANSWER = chromossome;

        }
        
        chromossome->fitness = 1000 / length;
        fitnessSum += chromossome->fitness;
      
        fitnessSum = evaluateFitnessAndProbability( chromossome->next, fitnessSum );
      
       if (fitnessSum != 0)
            chromossome->probability = chromossome->fitness / fitnessSum;
        printChromossome(chromossome);
    }

 return fitnessSum;
}


void freeMemory( population* population);
void freeMemory( population* population) {
    chromossome** auxi = population->chromossomes;
    chromossome** auxii;

    if ( population->chromossomes && (*population->chromossomes)->next != NULL)
        auxii = population->chromossomes;

    while ( *auxi != NULL){
        free(*auxi);
        auxi = auxii;

        if(*auxii != NULL)        
            auxii = &(*auxii)->next;
    }
    
    free ( population->chromossomes );
}
// void setProbabilities(population* population);
// void setProbabilities(population* population){
   
//     int fitnessSum = 0;
//     chromossome* aux = population->chromossomes;

//     for (int i = 0; i < population->populationSize; i++)
//     {
//         fitnessSum += population->chromossomes[i]->fitness;
//     }

//     for (int i = 0; i < population->populationSize; i++)
//         population->chromossomes[i]->probability = population->chromossomes[i]->fitness / fitnessSum;
// }

//WORKS!
void reverseArray(int* arr, int start, int end)
{
    int temp;

    while (start < end)
    {
        temp = arr[start];   
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }   
}     

void crossover(chromossome* parent1, chromossome* parent2);
void crossover(chromossome* parent1, chromossome* parent2){

}
//first a very varied breeding, then selected
// mutates chromossome according to option
void mutation( chromossome** chromossome,int opt);
void mutation( chromossome** chromossome,int opt){
    int indexA, indexB;

    switch (opt)
    {
    case 0:
        reverseArray( (*chromossome)->path, 0, 9);
        break;
    case 1:
        indexA = indexB;
        while (indexA == indexB)
        {
            indexA = rand(0,9);
            indexB = rand(0,9);
        }
        
        swapPlaces( )
    default:
        break;
    }
}

//stimulates population quality by replacing
// remarkably unfitting idividuals
//with permutations of desirable ones

void  deathOfTheUnfitting( population* population );
void  deathOfTheUnfitting( population* population ){
    chromossome** aux = population->chromossomes;

    printArray( (*population->chromossomes)->path);
    mutation( aux, 0 );
printArray( (*population->chromossomes)->path);
    // while (ANSWER != NULL && aux != NULL){
    //     if( (*aux)->fitness <= ANSWER->fitness / 2){
    //         *aux = mutation( aux, );
    //     }
    // }
}

void newGeneration( population* population);
void newGeneration( population* population){
    
//sets fitness and probability     
    evaluateFitnessAndProbability( *population->chromossomes, 0 );
    // setProbabilities( population);

    deathOfTheUnfitting( population );
    // fitnessSelection ()
}



void main ()
{
    population population;


    population.populationSize = 3;
    // population.populationSize = 79999;
// for (int i = 0; i < 10; i++)
// {                            //FOR BRUTE RANDOM ASSESSING
//         initiatePopulation( &population);
// }

    initiatePopulation( &population);



    newGeneration( &population);
    

    // printf("            @@ ANSWER %f \n", rand()/(double)RAND_MAX);
    printf("         SHORTEST PATH: ");
    printChromossome(ANSWER);

    freeMemory(&population);


    return;
}
