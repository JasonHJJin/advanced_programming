#include <stdio.h>
#include <stdlib.h>
#include "sorter.h"
#include <time.h>

void srand(unsigned int seed);

int main(){
    
    int user_Input = 0;
    scanf("%d", &user_Input);
    
    int arr1[user_Input];
    int arr2[user_Input];
    int arr3[user_Input];
       
    for(int i = 0; i < user_Input; i++){
       
       int random = rand() % 100;
       arr1[i] = random;
       arr2[i] = random;
       arr3[i] = random;
    }   
    
    //ORIGINAL
    int *p;
    p = (int*) malloc(user_Input * sizeof(int));

    if (p == NULL) {
        perror("malloc returned NULL");
        exit(1);
    }
    
    for(int num = 0; num < user_Input; num++){
        p[num] = arr1[num]; 
    }
        
    printf("original: ");
    for(int j = 0; j < user_Input; j++){
       printf("%d ", p[j]);
    }
    
    printf("\n");
    free(p);

    
    //ASCENDING
    int *up;
    up = (int*) malloc(user_Input * sizeof(int));
    
    if (up == NULL) {
        perror("malloc returned NULL");
        exit(1);
    }
 
    for(int num = 0; num < user_Input; num++){
        up[num] = arr2[num]; 
            
    }
     
    sort_integer_array(&up[0], &user_Input, 1);
    
    printf("ascending: ");    
    for(int j = 0; j < user_Input; j++){
       printf("%d ", up[j]);
    }

    printf("\n");
    free(up);



    //DESCENDING
    
    int *down;
    down = (int*) malloc(user_Input * sizeof(int));
    
    if (down == NULL) {
        perror("malloc returned NULL");
        exit(1);
    }
 
    for(int num = 0; num < user_Input; num++){
        down[num] = arr3[num]; 
            
    }
     
    sort_integer_array(&down[0], &user_Input, 0);
    
    printf("descending: ");    
    for(int j = 0; j < user_Input; j++){
       printf("%d ", down[j]);
    }

    printf("\n");
    free(down);

    return 0;   


}



