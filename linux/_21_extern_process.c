#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    printf("дочерний процесс с id=%d и аргументами:", getpid());
    for(int i=0; i<argc; ++i){
        printf(" %s", argv[i]);
    }
    printf("\n");
    exit(100500);
}