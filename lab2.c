#include <stdio.h>
#include <stdlib.h>

int main()
{
    int studentnumber, percentage;
    FILE* inputptr;
    FILE* outputptr;

    inputptr = fopen("input.txt", "r");
    outputptr = fopen("output.txt", "w");
    if (inputptr == NULL){
        printf("error! could not open input");
        return 1;
    }
    if (outputptr == NULL){
        printf("error! could not open output");
        fclose(inputptr);
        return 1;
    }
    char line[256];
    while (fgets (line, sizeof(line), inputptr) != NULL) {
        if (sscanf(line, "%d %d", &studentnumber, &percentage) !=2){
            fprintf(outputptr, "output is not valid : %s", line);
            continue;
        }
        char grade;
        if (percentage >= 90) grade = 'A';
        else if (percentage >= 80 ) grade = 'B';
        else if (percentage >= 70) grade = 'C';
        else if (percentage >=60) grade = 'D';
        else grade = 'F';

        fprintf(outputptr, "Student %d: Percentage = %d, Grade = %c\n", studentnumber, percentage, grade);
    }
    fclose(inputptr);
    fclose(outputptr);
    

}