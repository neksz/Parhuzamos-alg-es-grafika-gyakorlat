#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "primecount_serial.h"

int main(int argc, char *argv[])
{
  int n = 81920;

  srand(time(NULL));
  clock_t start, end;
  double cpu_time_used;
  start = clock();

  printf("%d", prime_number(n));

  end = clock();
  cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
  printf("\nEltelt ido: %fl masodperc\n", cpu_time_used);

  return 0;
}

int prime_number(int n)
{
  int i;
  int j;
  int prime;
  int total;

  total = 0;

  for (i = 2; i <= n; i++)
  {
    prime = 1;
    for (j = 2; j < i; j++)
    {
      if ((i % j) == 0)
      {
        prime = 0;
        break;
      }
    }
    total = total + prime;
  }
  return total;
}
