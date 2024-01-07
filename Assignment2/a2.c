#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t size = 1024;
typedef struct edge{
    int from, to, weight;
    struct edge *next;
}Edge;

int main(char argc, char **argv){
    FILE *ptr = fopen(argv[1], "r"); 
    int N, E;
    if(ptr == NULL){
        exit(EXIT_FAILURE);
    }
    char *buffer = malloc(size * sizeof(char)); 
    fgets(buffer, size, ptr); // read a line from the file into buffer
    sscanf(buffer, "%d %d ", &N, &E); // get the number of nodes and edges
    printf("N: %d, E: %d\n", N, E);

    int *inDegree = malloc(sizeof(int) * N);
    Edge *adjacencyList[1000];

    for(int i = 0; i < N; i++){
        inDegree[i] = 0;
        adjacencyList[i] = 0;
    }

    while(getline(&buffer, &size, ptr) > 0){
        int from, to, weight;
        sscanf(buffer, "%d %d %d", &from, &to, &weight);
        Edge *newEdge = malloc(sizeof(Edge)); 
        newEdge->from = from; 
        newEdge->to = to;
        newEdge->weight = weight;
        newEdge->next = adjacencyList[from]; // come back to it later
        adjacencyList[from] = newEdge;
        inDegree[to]++;
    }
    
    for(int i = 0; i < N; i++){
        printf("%d\n", inDegree[i]);
    }

    int front = 0; 
    int back = 0;
    int *queue = malloc(sizeof(int) * N);
    int *result = malloc(sizeof(int) * N);
    int *dist = malloc(sizeof(int) * N);
    int *count = malloc(sizeof(int) * N);

    for(int i = 1; i < N; i++){
        if(inDegree[i] == 0){
            queue[back++] = i;
        }
        dist[i] = -1;
        count[i] = 1;
    }
    dist[1] = 0;
    count[1] = 1;
    // queue[back++] = 0;
    int i = 0;
    while(front < back){
        int element = queue[front++];
        result[i] = element;
        i++;
        Edge *curr = adjacencyList[element];

        while(curr != NULL){
            int to = curr->to;
            int weight = curr->weight; 
            inDegree[to]--;
            if(inDegree[to] == 0){
                queue[back++] = to; 
            }

            if(dist[element] + weight > dist[to]){
                dist[to] = dist[element] + weight;
                count[to] = count[element];
            }
            else if(dist[element] + weight == dist[to]){
                count[to] += count[element];
            }

            curr = curr->next;
        }

    }
    printf("sort = [");
    for(int i = 0; i < N; i++){
        printf(" %d", count[i]);
    }
    printf("]\n");

    printf("Longest  path = %d\n", dist[N]);
    printf("Number of longest paths = %d\n", count[N]);
}