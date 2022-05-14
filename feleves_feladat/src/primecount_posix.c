#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "primecount_posix.h"

int main()
{
    srand(time(NULL));
    clock_t start, end;
    double cpu_time_used;
    int thread_count = 10;
    int low = 0;
    int high = 81920;
    int sum = 0;
    pthread_t thread[thread_count];

    start = clock();

    int steps = high / thread_count;
    int n_start = 0;
    int n_end = steps;

    Prime data_array[thread_count];

    for (int i = 0; i < thread_count; i++)
    {
        data_array[i].high = n_end;
        data_array[i].low = n_start;

        printf("nstart:%d, nend:%d\n", n_start, n_end);

        pthread_create(&thread[i], NULL, prime_number, &data_array[i]);

        n_start += steps;
        n_end += steps;
    }

    for (int i = 0; i < thread_count; i++)
    {
        pthread_join(thread[i], NULL);
    }

    for (int i = 0; i < thread_count; i++)
    {
        printf("\nSum: %d", data_array[i].sum);
        sum = sum + (int)data_array[i].sum;
    }
    sum += 1;

    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\n\nPrimes:%d", sum);
    printf("\nEltelt ido: %fl mp\n", cpu_time_used);
    return 0;
}

void prime_number(Prime *data)
{
    int high = data->high;
    int i;
    int j;
    int prime;
    int total;

    total = 0;

    for (i = data->low; i <= high; i++)
    {
        for (j = 2; j < i; j++)
        {
            prime = 1;
            if ((i % j) == 0)
            {
                prime = 0;
                break;
            }
        }
        total = total + prime;
    }
    printf("\nTotal: %d", total);
    data->sum = total;
    return;
}