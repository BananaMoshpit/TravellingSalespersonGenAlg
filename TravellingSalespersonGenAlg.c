/*where ANSWER IS, ONLY PATH & KEY, NO PROB/FIT
    CHECK ETHER ACCES TO TRUE ANSWER I MANTAINED THROUGH
    GENERATIONS AS ORIGINAL CHROMOSSOME DIES AND A COPY REMAINS ON ANSWER
    check values OF 2NDGEN ON RECURSIVE FNCTN

*/

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
    struct chromossome** currentGeneration;
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
        //An utility function to get a random number withn given range
        int randomInt( int minimum_number, int max_number){
           return ( rand() % (max_number + 1 - minimum_number) + minimum_number) ;
        }

        // An utility function to print an array
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


        chromossome* allocateCromossome( );
        void destroyCromossome();

        // An utility function to swap to integers
        void swapPlaces (int *indexA, int *indexB) ;
        void swapPlaces (int *indexA, int *indexB)
        {
            int aux = *indexA;
            *indexA = *indexB;
            *indexB = aux;
        }



        // A function to generate a random permutation of chromossome*


void setStandardChromossome(chromossome* chromossome, int key);

// Utility function to alocate chromossomes
        chromossome* allocateCromossome(chromossome** new){

            (*new) = (chromossome*)malloc(sizeof(chromossome)) ;

            if( (*new) == NULL )
                printf("Warning: Can't alocate struct. Is the memory sufficient?");

        }


//main functions

void setStandardChromossome(chromossome* chromossome, int key){

                chromossome->fitness = 0;
                chromossome->probability = 0;
                chromossome->length = 0;
                chromossome->chromossomeKey = key;

                chromossome->next = NULL;

                for (int i = 0; i < 10; i++)
                {
                    chromossome->path[i] = i;
                }

}

void copyPath(chromossome* copy, chromossome* copied, int fromIndex, int toIndex);
void copyPath(chromossome* copy, chromossome* copied, int fromIndex, int toIndex){
    for (int i = fromIndex; i <= toIndex; i++)
    {
        copy->path[i] = copied->path[i] ;
    }
    
}

chromossome* initiatePopulation (population *start);
chromossome* initiatePopulation (population *start){

    chromossome** chromossome ;
    int i, j, chromossomeKey, size = 10;

    printf(">>Initiating population... \n");

    // Use a different seed value so that we don't get same
    // result each time we run this program
    srand ( time(NULL) );

    start->currentGeneration = malloc(sizeof(int) * start->populationSize);

     chromossome = (start->currentGeneration);
    //Alocates given number of chromossomes
    for ( chromossomeKey = 0; chromossomeKey < start->populationSize; chromossomeKey++)
    {
        allocateCromossome( chromossome );
        setStandardChromossome( *chromossome, chromossomeKey );

        // Start from the last element and swap one by one. We don't
        // need to run for the first element that's why i > 0
        for ( i = size-1; i > 0; i--)
        {
            // Pick a random index from 0 to i
             j = rand() % (i+1);

            // Swap chromossome[i] with the element at random index
            swapPlaces(&(*chromossome)->path[i], &(*chromossome)->path[j]);
        }

        printArray((*chromossome)->path);
        chromossome = &(*chromossome)->next;    /*CAN USE INDEX*/
    }

    printf(">>Population initiated \n");

}

//Reads chromossome->path, seeks data on distances matrix and sums path distance
// sets individuals fitness ( 1/length ) on the way to the last chromossome
// sets idividual probability on the way back
long double evaluateFitnessAndProbability(chromossome* chromossome, long double fitnessSum);
long double evaluateFitnessAndProbability(chromossome* chromossome, long double fitnessSum){
    double length = 0;
    int fromCity;
    int toCity;

printf(">>Evaluating fitness/probability of:\n");
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

        chromossome->fitness = 1000 / length;
        fitnessSum += chromossome->fitness;

        fitnessSum = evaluateFitnessAndProbability( chromossome->next, fitnessSum );

       if (fitnessSum != 0)
            chromossome->probability = chromossome->fitness / fitnessSum;

//chromossome is marked as answer if it's the smallest one
        if ( length < SHORTESTPATH ) {
            SHORTESTPATH = length;
            *ANSWER = *chromossome;

        }

        printChromossome(chromossome);
    }

 return fitnessSum;
}


void freeMemory( population* population);
void freeMemory( population* population) {
    chromossome** auxi = population->currentGeneration;
    chromossome** auxii;

    if ( population->currentGeneration && (*population->currentGeneration)->next != NULL)
        auxii = population->currentGeneration;

    while ( *auxi != NULL){
        free(*auxi);
        auxi = auxii;

        if(*auxii != NULL)
            auxii = &(*auxii)->next;
    }

    free ( population->currentGeneration );
}
// void setProbabilities(population* population);
// void setProbabilities(population* population){

//     int fitnessSum = 0;
//     chromossome* aux = population->currentGeneration;

//     for (int i = 0; i < population->populationSize; i++)
//     {
//         fitnessSum += population->currentGeneration[i]->fitness;
//     }

//     for (int i = 0; i < population->populationSize; i++)
//         population->currentGeneration[i]->probability = population->currentGeneration[i]->fitness / fitnessSum;
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



    indexA = indexB;


    switch (opt)
    {
    case 0:

        reverseArray( (*chromossome)->path, 0, 9);
        break;
    case 1:

        indexA = randomInt( 0, 9);
        indexB = randomInt( 0, 9);

        swapPlaces( &(*chromossome)->path[indexA], &(*chromossome)->path[indexB] );

        break;
    case 3:

       while ( indexA >= indexB){
        indexA = randomInt( 0, 9);
        indexB = randomInt( 0, 9);}

        reverseArray( (*chromossome)->path, indexA, indexB);
        break;
    case 4:

        for (int i = 0; i < randomInt( 1, 4); i++)
            mutation( chromossome, randomInt( 0, 3) );

        break;
    }

}

//stimulates population quality by replacing
// remarkably unfitting idividuals
//with permutations of desirable ones

//check if new values are according, fitness, NEXT CHROMOSSOME
void  reformTheUnfitting( population* population );
void  reformTheUnfitting( population* population ){
    chromossome** aux = population->currentGeneration;
    chromossome newChromossome;
    chromossome* keepInLine;



    while( *aux != NULL){
        
        if ( (*aux)->fitness <= (ANSWER->fitness /2) )
        {
            printf("\n                In Need Of Correction\n");
            
            setStandardChromossome( &newChromossome, (*aux)->chromossomeKey );
            copyPath( &newChromossome, ANSWER, 0, 9);
            newChromossome.next = (*aux)->next;
            
            *aux = &newChromossome; //ALL previous rehabs are LOST.Many equal chromossomes.
            mutation( aux, randomInt( 0, 4));

            printChromossome( *aux );
        }

        aux = &(*aux)->next;
        // printf("                NO Need Of Correction");
    }

                                    //  ERROR IF ANSWER == NUL !!
    // printf("                    DIE: ");
    // printArray( (*population->currentGeneration)->path);
    // printf("                    FOR: ");
    // printArray( ANSWER->path);

    // evaluateFitnessAndProbability( *population->currentGeneration, 0);
    // printChromossome( *aux );
    printf("reformed");

}

void newGeneration( population* population);
void newGeneration( population* population){

//sets fitness and probability
    evaluateFitnessAndProbability( *population->currentGeneration, 0 );
    // setProbabilities( population);

    reformTheUnfitting( population );
    // fitnessSelection ()
}



void main ()
{
    population population;
    ANSWER = malloc(sizeof(chromossome));

    population.populationSize = 3000;
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
