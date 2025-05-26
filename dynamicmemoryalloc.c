#include <stdio.h>
#include <stdlib.h>

int main(){



int *arr = (int*) malloc(5 * sizeof(int)); // Allocates memory for 5 integers
free(arr);  // Always free memory!
}
