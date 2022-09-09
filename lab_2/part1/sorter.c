#include <stdio.h>
#include <stdlib.h>


void sort_integer_array(int *begin, int *end, int ascending) 
{
        /* In here, you will call your real sorting function (your own
         * or the qsort()).  Basically, I want to make sure that you
         * know how to translate the begin/end parameter to whatever
         * is required for your sorting function.
         */
    
    int temp;
    if(ascending == 1){
        for(int i = 0; i < *end; i++)
        {  
            for(int j = i+1; j < *end; j++){
                if(begin[i] > begin[j]){
                    temp = begin[i];
                    begin[i] = begin[j];
                    begin[j] = temp;               
                }
            }
        }
    }

    if(ascending == 0){
        for(int i = 0; i < *end; i++)
        {  
            for(int j = i+1; j < *end; j++){
                if(begin[i] < begin[j]){
                    temp = begin[i];
                    begin[i] = begin[j];
                    begin[j] = temp;               
                }
            }
        }
    }
}

