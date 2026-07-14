#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINES 100
#define BSIZE 100

char* chomp(char *s){
    size_t len;

    len = strlen(s);
    if(len > 0 && s[len - 1] == '\n'){
        s[len - 1] = '\0';
    }

    return s;
}

void print_lines(char *lines[], int n){
    int i;
    size_t len;

    for(i = 0; i < n; i++){
        printf("%03d %s", i + 1, lines[i]);
        len = strlen(lines[i]);
        if(len == 0 || lines[i][len - 1] != '\n'){
            printf("\n");
        }
    }
}

void free_lines(char *lines[], int n){
    int i;

    for(i = 0; i < n; i++){
        free(lines[i]);
    }
}

char* substitution(const char *old, const char *position,
                   const char *s, const char *t){
    size_t oldlen;
    size_t slen;
    size_t tlen;
    size_t prefix;
    size_t i;
    size_t j;
    size_t k;
    char *x;

    oldlen = strlen(old);
    slen = strlen(s);
    tlen = strlen(t);
    prefix = (size_t)(position - old);

    x = (char*)malloc(oldlen - slen + tlen + 1);
    if(x == NULL){
        return NULL;
    }

    k = 0;
    for(i = 0; i < prefix; i++){
        x[k] = old[i];
        k++;
    }

    for(i = 0; i < tlen; i++){
        x[k] = t[i];
        k++;
    }

    j = prefix + slen;
    while(j < oldlen){
        x[k] = old[j];
        j++;
        k++;
    }
    x[k] = '\0';

    return x;
}

int main(void){
    char *lines[LINES];
    char buf[BSIZE];
    char s[BSIZE];
    char t[BSIZE];
    char *p;
    char *x;
    int n = 0;
    int i;

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
            free_lines(lines, n);
            exit(EXIT_FAILURE);
        }

        strcpy(p, buf);
        lines[n] = p;
        n++;
    }

    print_lines(lines, n);

    while(1){
        printf("source: ");
        fgets(s, BSIZE, stdin);
        chomp(s);
        if(s[0] == '.' && s[1] == '.' && s[2] == '.'){
            break;
        }

        printf("target: ");
        fgets(t, BSIZE, stdin);
        chomp(t);
        if(t[0] == '.' && t[1] == '.' && t[2] == '.'){
            break;
        }

        for(i = 0; i < n; i++){
            p = strstr(lines[i], s);
            if(p != NULL){
                x = substitution(lines[i], p, s, t);
                if(x == NULL){
                    printf("memory allocation failure.\n");
                    free_lines(lines, n);
                    exit(EXIT_FAILURE);
                }
                free(lines[i]);
                lines[i] = x;
            }
        }

        printf("result:\n");
        print_lines(lines, n);
    }

    free_lines(lines, n);

    return 0;
}
