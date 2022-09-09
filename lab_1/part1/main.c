#include <stdio.h>
#include "prime.h"
#include "gcd.h"

int main()
{
    int a, b;
    float c;
   
    printf("Enter your first integer: ");
   
    scanf("%d", &a);

    printf("Enter your second integer: ");
   
    scanf("%d", &b);
    
    c = (float)(a + b)/2;

    printf("\nThe average of these two numbers is: %f \n", c);
    if(prime(a)==0){
        printf("%d is a prime number.\n", a);
    }else if(prime(a)!=0){
        printf("%d is not a prime number.\n", a);
    }

    if(prime(b)==0){
        printf("%d is a prime number.\n", b);
    }else if(prime(b)!=0){
        printf("%d is not a prime number.\n", b);
    }

    gcd(a , b);    
    
    return 0;
}
