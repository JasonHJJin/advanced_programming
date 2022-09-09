#include <stdio.h>

int main()
{ 
    int num;
    scanf("%d", &num); 
    printf("signed dec:   %d\n", num);
    printf("unsigned dec: %u \n", num);
    printf("hex:          %x\n", num);
    
    int i, bit;
    int count = 1;
    printf("binary:       ");
    for(i = 31; i >= 0 ; i--)
    {
       bit =  num >> i;
       
      if(bit & 1){
        printf("1");
      }else{
        printf("0");
      }
      
      if((count%4) == 0)
      {
        printf(" ");
      } 
      
      count++;  

    }
    printf("\n");
}
