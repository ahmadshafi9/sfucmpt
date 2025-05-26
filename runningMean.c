/* Assignment 4 */
/* Miguel and Ahmad */

#include <stdio.h>
#include <stdlib.h>

void WeightedRunningMean(double* measurements, double* weightedRunningMean, int numInRunningMean) {
    for (int k = 0; k < numInRunningMean; k++) {
        if (k == 0) {
            weightedRunningMean[k] = measurements[k];
        } else {
            weightedRunningMean[k] = (weightedRunningMean[k-1] / 2.0 + measurements[k]) / 1.5;
        }
    }
}

int main() {
    char filename[256];
    FILE *file = NULL;
    int attempts = 0;

    for (attempts = 0; attempts < 3; attempts++) {
        printf("Enter the name of the input file: ");
        scanf("%255s", filename);
        getchar(); 

        file = fopen(filename, "r");
        if (file != NULL) {
            break; 
        }
        printf("ERROR: Input file %s not opened\n", filename); 
    }

    if (file == NULL) {
        printf("ERROR: too many failures opening input file\n"); 
        return 1;
    }

    int numMeas = 0;
    printf("Enter the number of measurements: ");
    scanf("%d", &numMeas);
    getchar(); 

    if (numMeas <= 0 || numMeas > 40) {
        printf("ERROR: numMeas is out of range\n");
        fclose(file);
        return 1;
    }

    double *myMeasurements = (double *)malloc(numMeas * sizeof(double));
    double *myRunningMean = (double *)malloc(numMeas * sizeof(double));

    if (myMeasurements == NULL || myRunningMean == NULL) {
        printf("ERROR: Memory allocation failed\n");
        fclose(file);
        if (myMeasurements) free(myMeasurements);
        if (myRunningMean) free(myRunningMean);
        return 1;
    }

    int actualValuesRead = 0;
    for (int i = 0; i < numMeas; i++) {
        if (fscanf(file, "%lf", &myMeasurements[i]) != 1) {
            break; 
        }
        actualValuesRead++;
    }

    fclose(file); 

    if (actualValuesRead == 0) {
         printf("ERROR: input file is empty\n"); 
         free(myMeasurements);
         free(myRunningMean);
         return 1; 
    }

    if (actualValuesRead < numMeas) {
        printf("ERROR: fewer than numMeas measurements in the file\n"); 
    }

    WeightedRunningMean(myMeasurements, myRunningMean, actualValuesRead);

    printf("The running sums are\n"); 
    for (int i = 0; i < actualValuesRead; i++) {
        printf("%10.2f", myRunningMean[i]); 
        if ((i + 1) % 5 != 0 && i != actualValuesRead - 1) {
             printf(" "); 
        }
        if ((i + 1) % 5 == 0 || i == actualValuesRead - 1) {
            printf("\n");
        }
    }

    free(myMeasurements);
    free(myRunningMean);

    return 0;
}