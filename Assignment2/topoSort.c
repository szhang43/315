#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t size = 1024;
typedef struct edge{
    int from, to, weight;
    struct edge *next;
}Edge;

void addNode(Edge **head, int from, int to, int weight){
    Edge *newEdge = malloc(sizeof(Edge));
    newEdge->from = from; 
    newEdge->to = to;
    newEdge->weight = weight;
    newEdge->next = NULL;

    if (*head == NULL) {
        *head = newEdge;
        return;
    }
    Edge *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    // add the new node after the last node
    current->next = newEdge;
}

int *topologicalSort(Edge *head, int N, int E){
    int *queue = malloc(sizeof(int) * N);
    int front = 0; 
    int back = 0;
    int *inDegree = malloc(sizeof(int) * N);
    int *result = malloc(sizeof(int) * N);
    int *dist = malloc(sizeof(int) * N + 1);
    int *count = malloc(sizeof(int) * N + 1);

    Edge *current = head;
    while(current != NULL){
        int to = current->to;
        inDegree[to]++;
        current = current->next;
    }

    for(int i = 0; i <= N; i++){
        // int to = head->to;
        if(inDegree[i] == 0){
            queue[back] = i;
            back++;
        }
        dist[i] = -1;
        count[i] = 0;
    }
    dist[0] = 0;
    count[0] = 1;

    int i = 0;
    while(front < back){
        int element = queue[front];
        front++;
        result[i] = element;
        // printf("%d is the element\n", element);
        i++;
        Edge *curr = head;
        while(curr != NULL){
            int to = curr->to;
  
            printf("to : %d\n", to);
            inDegree[to]--;
            if(inDegree[to] == 0){
                queue[back] = to; 
                back++;
            }
        
            if(dist[element] + curr->weight > dist[to]){
                printf("curr->from: %d + curr->weight: %d dist[element]: %d\n", curr->to, curr->weight, dist[element]);
                dist[to] = dist[element] + curr->weight;
                count[to] = count[element];
            }
            else if(dist[element] + curr->weight == dist[to]){
                count[to] = count[to] +  count[element];
            }
            
            curr = curr->next;
        }
    }
    printf("Distance = [");
    for(int i = 1; i < N; i++){
        printf(" %d", result[i]);
    }
    printf("]\n");

    // printf("Longest  path = %d\n", dist[N - 1]);
    // printf("Number of longest paths = %d\n", count[N - 1]);
    return result;
}


int main(char argc, char **argv){
    Edge *head = NULL;
    FILE *ptr = fopen(argv[1], "r"); 
    int N, E;
    if(ptr == NULL){
        exit(EXIT_FAILURE);
    }
    char *buffer = malloc(size * sizeof(char)); 
    fgets(buffer, size, ptr); // read a line from the file into buffer
    sscanf(buffer, "%d %d ", &N, &E); // get the number of nodes and edges
    printf("N: %d, E: %d\n", N, E);
    while(getline(&buffer, &size, ptr) > 0){
        int from, to, weight;
        sscanf(buffer, "%d %d %d", &from, &to, &weight);
        addNode(&head, from, to, weight);
    }
    topologicalSort(head, N, E);
    

}