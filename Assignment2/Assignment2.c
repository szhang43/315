#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Name: Sophia Zhang
Date: 04/23/2023
Description: Assignment 2 - Find the longest path 
*/
typedef struct edge{
    int from, to, weight;
    struct edge *next;
}Edge;

int main(){
    int N, E;
    scanf("%d %d", &N, &E); // get the number of nodes and edges
    // printf("N: %d, E: %d\n", N, E);

    int inDegree[N]; //create an array of inDegree count for the nodes
    Edge *adjacencyList[1000000];
    for(int i = 0; i < N; i++){ // initialize the arrays
        inDegree[i] = 0;
        adjacencyList[i] = 0;
    }
    int j = 0; // read the file
    while(j < E){ // add information to the struct node
        int from, to, weight;
        scanf("%d %d %d", &from, &to, &weight);
        Edge *newEdge = malloc(sizeof(Edge)); 
        newEdge->from = from; 
        newEdge->to = to;
        newEdge->weight = weight;
        newEdge->next = adjacencyList[from]; // come back to it later
        adjacencyList[from] = newEdge;
        inDegree[to]++; // include the inDegree count into the array 
        j++;
    }

    int front = 0; 
    int back = 0;
    int queue[N];
    int result[N];
    int dist[N];
    int count[N];

    for(int i = 1; i <= N; i++){ // start the queue by enqueueing nodes with 0 indegree
        if(inDegree[i] == 0){
            queue[back++] = i;
        }
        dist[i] = -1;
        count[i] = 1;
    }
    dist[1] = 0; // the source node should be 0
    count[1] = 1; 
    // queue[back++] = 0;
    int i = 0;
    while(front < back){
        int element = queue[front++];
        result[i] = element; // topological sort array
        i++;
        Edge *curr = adjacencyList[element];

        while(curr != NULL){
            int to = curr->to;
            int weight = curr->weight; 
            inDegree[to]--; // decrement the indegree of that node
            if(inDegree[to] == 0){ // if it comes to 0, add it to the queue
                queue[back++] = to; 
            }

            if(dist[element] + weight > dist[to]){ // using Dijstra's Algorithm compare the weights
                dist[to] = dist[element] + weight; // if it is a shorter path, then we update it
                count[to] = count[element]; // add it to the count array to keep track of path #
            }
            else if(dist[element] + weight == dist[to]){
                count[to] += count[element];
            }

            curr = curr->next;
        }

    }
    // printf("sort = [");
    // for(int i = 0; i < N; i++){
    //     printf(" %d", count[i]);
    // }
    // printf("]\n");

    printf("Longest  path = %d\n", dist[N]);
    printf("Number of longest paths = %d\n", count[N]);
}