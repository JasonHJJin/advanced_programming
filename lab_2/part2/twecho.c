/*
 * twecho
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static char **duplicateArgs(int argc, char **argv)
{   
    char **cp1 = argv;
    
    //malloc: vertical array
    cp1 = (char**) malloc((argc+1) * sizeof(char*)); 

    if(cp1 == NULL){
        perror("malloc returned NULL");
        exit(1);
    }

    for(int i = 0; i < argc; i++){
        //malloc each string
        cp1[i] = (char*) malloc((strlen(argv[i]) * sizeof(char)) + 1);
        
        if(cp1[i] == NULL){
            perror("malloc returned NULL");
            exit(1);
        }

        char **temp = argv;
        strcpy(cp1[i], temp[i]);

        char *index = cp1[i];
        for(int j = 0; j < strlen(cp1[i])+1; j++){
            *index = toupper(*index);
            index++;
        }
    }    
    
    cp1[argc] = NULL;

    return cp1;
}

static void freeDuplicatedArgs(char **copy)
{ 
    char **p = copy;
    
    while(*p){
        free(*p++);
    }
    
    free(copy);
}

/*
 * DO NOT MODIFY main().
 */
int main(int argc, char **argv)
{
    if (argc <= 1)
        return 1;

    char **copy = duplicateArgs(argc, argv);
    char **p = copy;

    argv++;
    p++;
    while (*argv) {
        printf("%s %s\n", *argv++, *p++);
    }

    freeDuplicatedArgs(copy);

    return 0;
}
