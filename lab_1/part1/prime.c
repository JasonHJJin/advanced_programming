#include <stdio.h>
#include "prime.h"

int prime(int a)
{
        
    int i, bool = 0;

    int loopNumb = a/2;


    for(i= 2; i<= loopNumb; i++)
    {
        
        if((a%i) == 0)
        {
                bool = 1;
                break;        
        }
    
    }

    if(bool==0){
        return 0;
    }else{
        return 1;
    }
   
}
