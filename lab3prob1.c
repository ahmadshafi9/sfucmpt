#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
int smallestnum;
int largestnum;
printf("Enter the smallest integer to consider as part of the sum: ");
scanf("%d", &smallestnum);
printf("Enter the largest integer to consider as part of the sum: ");
scanf("%d", &largestnum);
int divisorofinterest;
printf("Enter the divisor of interest: ");
scanf("%d", &divisorofinterest);
int i;

int totalsumdivisible;
int totalsumnotdivisible;
totalsumdivisible = 0;
for (i = smallestnum; i <= largestnum; i++){
    if (i % divisorofinterest == 0){
        totalsumdivisible += i;
    }
    else {
        totalsumnotdivisible += i;
    }
}
printf("sum of integers that are divisible: %d\n", totalsumdivisible);
printf("sum of integers that are not divisible: %d\n", totalsumnotdivisible);
}