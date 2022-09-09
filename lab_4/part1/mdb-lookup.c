#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylist.h"
#include "mdb.h"

static void die(const char *message)
{
    perror(message);
    exit(1); 
}

int main(int argc, char **argv){
    
    if(argc!=2){
        fprintf(stderr, "%s\n", "usage: mdb-lookup <database_file>");
    }
    
    //Read argv[1] database file
    char *filename = argv[1];
    FILE *fp = fopen(filename, "rb");
    if(fp == NULL){die("fopen fail");}    
        
    struct List list;
    initList(&list);
    
    struct MdbRec mdbrec;
    struct Node *node = NULL;
    

    //Reading entire memory
    while(fread(&mdbrec, sizeof(mdbrec), 1, fp) == 1){
        
        struct MdbRec *mem = (struct MdbRec *)malloc(sizeof(mdbrec));
        if(!mem){die("malloc failed");}
        memcpy(mem, &mdbrec, sizeof(mdbrec));
        //each node pointer pointing to mdb rack        
        node = addAfter(&list, node, mem);
        if(node==NULL){die("addFront failed");}

    }

    if(ferror(fp)){die("fread fail");}    

    char buf[1000]; //linebyline
    char five[6]; //
    printf("lookup: ");
    fflush(stdout);
    while(fgets(buf, sizeof(buf), stdin) != NULL){
        
        strncpy(five, buf, sizeof(five)-1);//or line
        five[sizeof(five)-1] = '\0';//input could be less than 5

        if(five[strlen(five)-1]=='\n'){
            five[strlen(five)-1] = '\0'; //to terminate 
        }

        struct Node *node2 = list.head;
        int lineno = 1;
        while(node2){
            struct MdbRec *m = (struct MdbRec *)node2->data;
            if((strstr(m->name, five)) || (strstr(m->msg, five))){
                printf("%4d: {%s} said {%s}\n", lineno, m->name, m->msg);
            }
            node2 = node2->next;
            m++;
            lineno++;
        }   

        printf("\nlookup: ");
        fflush(stdout);
    }

    if(ferror(fp)){die("reading failed");}
    traverseList(&list, &free);
    removeAllNodes(&list); 
    fclose(fp);
    return 0;

}
