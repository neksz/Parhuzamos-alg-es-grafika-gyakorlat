#include <time.h>
#include <stdlib.h>
#include <stdio.h>
int linearSearchFunc(int length, int lowerRange, int upperRange);

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    printf("Enter how many numbers i should generate:\n");
    int length;
    double totalTime;
    scanf("%d", &length);

    FILE *fpt;
    fpt = fopen("linearSearch.csv", "w+");
    fprintf(fpt, "Searched number index, Time Required, Number of elements\n");
    int searchedIndex;
    int lowerRange = 0;
    int upperRange = 1000;
    clock_t start_t, end_t, total_t;

    for (int i = 0; i < 100; i++)
    {
        start_t = clock();
        searchedIndex = linearSearchFunc(length, lowerRange, upperRange);
        end_t = clock();
        totalTime = ((double)(end_t - start_t)) / CLOCKS_PER_SEC;
        // printf("Total time taken by CPU: %fl\n", total_t  );
        fprintf(fpt, "%d, %f, %d\n", searchedIndex, totalTime, length);
        printf("%d. Time required: %f\n", i + 1, totalTime);
        // printf("\nSearched number index: %d",linearSearchFunc(length,0,10)+1);
    }
    fclose(fpt);
}

int linearSearchFunc(int length, int lowerRange, int upperRange)
{
    int *numbers;
    int i, searchNumber;

    // printf("%d", time(NULL));
    searchNumber = (rand() % (upperRange - lowerRange + 1)) + lowerRange;
    // printf("Searched number: %d\n",searchNumber);

    numbers = calloc(length, sizeof(int));

    for (i = 0; i < length; i++)
        *(numbers + i) = (rand() % (upperRange - lowerRange + 1)) + lowerRange;

    for (i = 0; i < length; i++)
    {
        // printf("%d\t", *(numbers+i));
        if (*(numbers + i) == searchNumber)
        {
            free(numbers);
            return i;
        }
    }
}
