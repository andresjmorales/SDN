#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>


/*
 Comparison function necessary for quicksort.
 */
static int intcmp(const void *p1, const void *p2){
    return *(int*)p1 > *(int*)p2;
}

int dijkstra(int *table, int dimension){
    
    /* ********************************************INITIALIZING VALUES*********************************************/

 
    bool Np[dimension]; //N' Array to keep track of nodes that have the shortest path, basically use 0 or 1, true or false, if node is already in shortest path tree
    int D[dimension], P[dimension]; //array to store the costs or distances between nodes, array to store predecessor nodes, source is 0 or u
    
    for (int i = 0; i < dimension; i++){
        P[i] = -1; //predecessor nodes set to -1
        if(i == 0){
            D[i] = 0;//cost to source node should be 0
        }
        else{
            D[i] = 10000; //Dijkstra's algorithm states that all costs should be initialized to infinity
        }
        Np[i] = false; //no nodes in N' tree
    }
    
    /* ***************************************** END INITIALIZING VALUES******************************************/

    
    /******************************************* Following the pseudocode****************************************/
    for (int i = 0; i < dimension - 1; ++i){
        
        int initial_value = 10000, index = 0; //infinity is the initial value, the index should be set to 0 initially for the index of the minimum cost node
        for (int i = 0; i < dimension; ++i){
            if (Np[i] == false && D[i] <= initial_value){//if the node is not in the shortest path tree and the cost is less than whatever the value currently in D is
                initial_value = D[i]; //set the cost to the new or same lowest cost
                index = i; //the index of the node is stored
            }
        }
        
        
        Np[index] = true; //the node is now in the shortest path tree
        for (int j = 0; j < dimension; ++j){
            if (Np[j] == false && table[index][j] && D[index] + table[index][j] < D[j]){ //if it's not in the shortest path tree and the initial cost in table and the new cost d + table are less than what is in the cost array D
                P[j] = index; //set predecessor node
                D[j] = D[index] + table[index][j]; //set new cost to get to node since multiple nodes were reached
            }
        }
    }
    
    /******************************************* End Following the pseudocode****************************************/

    /******************************************* Printing the values ************************************************/
    
   

    
    int d2[6];//temporary array used for comparison to store unsorted costs
    for(int i = 0; i < dimension; ++i){
        
        d2[i] = D[i]; //store costs before sorting
        
    }
    
    qsort(D, (sizeof(D)/sizeof(int)), sizeof(int), intcmp); //use quicksort implementation to check costs and sort least to greatest
    
    printf("Shortest Path Tree Based On Distance: ");
    
    for(int i=0; i< dimension; ++i){
        for(int j =0; j< dimension; ++j){
            /*
             Logic: compare unsorted and sorted arrays... the D cost array is ordered by index, where the index represents a node. example: 0 is origin , 1 is device, etc. check the unsorted list for a matching cost. when a match is found, we know what letter to print based off of the index of the unsorted list.
             
             */
            if(d2[j] == D[i]){
               
              if(j == (dimension - 1)){
               
                printf("Device %d\n", j); //last device
               
              }
              else{
                printf("Device %d --> ", j);
              }
	    }
        }
    }
    
    
     /******************************************* End printing the values ************************************************/
    
}

