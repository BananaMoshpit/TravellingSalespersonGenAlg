#include<stdlib.h>
#include<stdio.h>


//chromossome has only 10 but fitness adds return
typedef struct  chromossome  {

int path[10];
double fitenss;

struct chromossome* next;
int index;
}chromossome;

typedef struct population{
    chromossome* startingPath;
    int size;
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

                            } ;

//creates given number of random chromossomes
chromossome* initiatePopulation(population *start);

//calculates specific fitness relative to the sum of all path lengths 
//recursive, sum on the way, fitness on the back (specific/total length)
int evaluateFitness(chromossome* path, int lengthSum);

// prints chromossome as a path between cities
void printPath(chromossome* path);


chromossome* SHORTESTPATH;


// helper functions

chromossome* createCromossome( );

void destroyCromossome();

chromossome* createCromossome(){
    chromossome* new;
    new = (chromossome*)malloc(sizeof(chromossome)) ;

    if( new == NULL )
        printf("Warning: Can't alocate struct. Is the memory sufficient?");

    else
    {
        new->fitenss = 0;
        new->next = NULL;
    }
    
    return new;
}

//main functions


chromossome* initiatePopulation(population *start){

    chromossome** aux = &start->startingPath;
    int i;

    for ( i = 1; i <= start->size; i++)
    {
        *aux = createCromossome();
        (*aux)->index = i;

        aux = &(*aux)->next;
    }
    
    
}



void main ()
{
    int populationSize;
    population population;
    int num;

    num = (rand() % (10 - 1)) ;
    printf("%d", num);

    population.size = 20;

    initiatePopulation( &population);

    createCromossome();

    // for (row=0; row<10; row++)
    //  {
    //     for(column=0; column<10; column++)
    //         {printf("%d     ", distances[row][column]);}
    //         printf("\n");
    //  }
    
    // while(0){printf("'");}
  

    return;
}
