#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINES 100
#define BSIZE 100

int main(void){
    char *lines[LINES];
    char buf[BSIZE];
    char *p;
    int n = 0;
    int i;
    size_t len;

    while(n < LINES){
        if(fgets(buf, BSIZE, stdin) == NULL){
            break;
        }

        if(buf[0] == '.' && buf[1] == '.' && buf[2] == '.'){
            break;
        }

        p = (char*)malloc(strlen(buf) + 1);
        if(p == NULL){
            printf("memory allocation failure.\n");
            for(i = 0; i < n; i++){
                free(lines[i]);
            }
            exit(EXIT_FAILURE);
        }

        strcpy(p, buf);
        lines[n] = p;
        n++;
    }

    for(i = 0; i < n; i++){
        printf("%03d %s", i + 1, lines[i]);
        len = strlen(lines[i]);
        if(len == 0 || lines[i][len - 1] != '\n'){
            printf("\n");
        }
    }

    for(i = 0; i < n; i++){
        free(lines[i]);
    }

    return 0;
}
