#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main(int argc, char const *argv[])
{
    int count;
    printf("How many numbers should i work with?\n");  
    scanf("%d",&count);
    srand(time(NULL));

    int numbers[count];
    int outputArray[count];

    printf("Generating random numbers from 1-10...\n");

    for (int i = 0; i < count; i++) {
        numbers[i] = (rand() %
           (3 - 1 + 1)) + 1;
        printf("%d\t",numbers[i]);
    }

    int temp1 = 0;
    int temp2 = 0;

    int outputArray1[(int)floor(count/2)];
    int outputArray2[(int)(count-(floor(count/2)))];
    //1 process
    for (int i = 0; i < floor(count/2); i++)
    {
        temp1=temp1+numbers[i];
        outputArray1[i]=temp1;
        printf("temp1:%d\n",temp1);
    }

    //2 process
    for (int i = 0; i < count-(floor(count/2)); i++)
    {
        temp2=temp2+numbers[i]; //Itt a gond
        outputArray2[i]=temp2;
        printf("temp2:%d\n",temp2);
    }

    //Final addition
    int j = 0;
    for (int i = 0; i < count; i++)
    {
        if (i < floor(count/2))
        {
            outputArray[i] = outputArray1[i];
        }
        else
        {
            outputArray[i] = temp1 + outputArray2[j];
            j++;
        }
    }
    printf("\nOutput array:\n");
    for (int i = 0; i < count; i++)
    {
        printf("%d\t",outputArray[i]);
    }

    return 0;
}