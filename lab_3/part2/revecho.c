#include <stdio.h>
#include <stdlib.h>
#include "mylist.h"
#include <string.h>
#include <assert.h>


int main(int argc, char** argv){        
    
    assert(argc>=2);

    struct List list;
    initList(&list);

    for(int i = 1; i < argc; i++){
        addFront(&list, argv[i]);}

    struct Node *list1 = list.head;
    while(list1){

        printf("%s\n", (char *)(list1->data));
        list1 = list1->next;
        
    }
    
    if(findNode(&list, "dude", (int (*)(const void *, const void *))&strcmp)){
        printf("\ndude found\n");
    }else{
        printf("\ndude not found\n");
    }

    removeAllNodes(&list);

    return 0;

}

