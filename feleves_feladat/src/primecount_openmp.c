#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <time.h>

int main(int argc, char *argv[]);
void call_prime_number(int low, int high, int step_count);
int prime_number(int n);

int main(int argc, char *argv[])
{
  int step_size;
  int high;
  int low;

  double wtime = omp_get_wtime();

  printf("\n");
  printf("PRIME_OPENMP\n");

  low = 10;
  high = 1310720;
  step_size = 2;

  call_prime_number(low, high, step_size);

  wtime = omp_get_wtime() - wtime;
  printf("\nEltelt ido: %fl masodperc\n", wtime);

  return 0;
}

void call_prime_number(int low, int high, int step_size)
{
  int n;
  int primes;
  printf("\n");
  printf("         N        Pi              \n");
  printf("\n");

  n = low;

  while (n <= high)
  {
    primes = prime_number(n);
    printf("  %8d  %8d\n", n, primes);

    n = n * step_size;
  }

  return;
}

int prime_number(int n)
{
  int i;
  int j;
  int prime;
  int total = 0;

#pragma omp parallel \
shared(n) private(i, j, prime)

#pragma omp for reduction(+ \
                          : total)
  for (i = 2; i <= n; i++)
  {
    prime = 1;

    for (j = 2; j < i; j++)
    {
      if (i % j == 0)
      {
        prime = 0;
        break;
      }
    }
    total = total + prime;
  }

  return total;
}
