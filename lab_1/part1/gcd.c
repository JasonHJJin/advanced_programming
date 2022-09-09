#include <stdio.h>
#include "gcd.h"

int gcd(int a, int b)
{
    int i, gcd;
    for(i = 1; (i <= a) && (i <= b) ; i++){
        if( (a%i == 0) && (b%i == 0) ){
              gcd = i;  
        }
    }
    
    if (gcd == 1){
        printf("The two numbers are relatively prime.\n\n");
    }else{
        printf("The two numbers are NOT relatively prime.\n\n");
    }    

    return 0; 
}
