#include <stdio.h>

int isPalindrome(int arr[], int size) {
    int start = 0, end = size - 1;
    while (start < end) {
        if (arr[start] != arr[end]) {
            return 0; // Not a palindrome
        }
        start++;
        end--;
    }
    return 1; // It's a palindrome
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {1, 2, 3, 2, 1}; // Palindrome example
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Array: ");
    printArray(arr, size);

    if (isPalindrome(arr, size)) {
        printf("The array is a palindrome.\n");
    } else {
        printf("The array is NOT a palindrome.\n");
    }

    return 0;
}
