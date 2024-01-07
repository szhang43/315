#include <stdio.h>
#include <stdlib.h>

int graphSize(char* argv){
    FILE *ptr;
    ptr = fopen(argv);
    if(ptr == NULL){
        exit(EXIT_FAILURE);
    }
    printf("Test");

}
struct graph{
    struct Node* head[N]
};
typedef struct graph Graph;

int main(int argc, char** argv){
    graphSize(argv[1]);
}


