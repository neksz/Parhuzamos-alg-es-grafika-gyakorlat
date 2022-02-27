#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

void primeNumbers(int n);

int main(int argc, char const *argv[])
{
    clock_t start_t, end_t, total_t;
    int i;

    start_t = clock();
    printf("Starting program\n");

    primeNumbers(1000);

    end_t = clock();
    printf("Found primes\n");
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("Total time taken by CPU: %ld\n", total_t);

    printf("Exiting program...\n");

    return (0);
}

void primeNumbers(int n)
{
    int m = 0;
    int primes = 0;
    int flag = 0;
    int steps = 0;

    for (int j = 1; j < n + 1; j++)
    {
        steps++;
        m = j / 2;
        for (int i = 2; i <= m; i++)
        {
            steps++;
            if (j % i == 0)
            {
                steps++;
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            steps++;
            primes++;
        }
    }
    printf("Lepesszam: %d\n", steps);
}
