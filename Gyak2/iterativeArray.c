#include <stdio.h>
#include <time.h>


int main(){
    clock_t start_t, end_t, total_t;

   start_t = clock();

    int i,size;
   
    printf("Enter array length : \n");
    scanf("%d",&size);
    
    int ara[size];
    
     printf("Enter array elements:\n");
     for(i = 0; i < size;  i++){
        scanf("%d", &ara[i]);
     }

     int min=ara[0];
     int max=ara[0];
     int sum=0;
     int i;

    for(i = 0; i < size; i++){
        
        if(ara[i] < min){
            min = ara[i];
        }
        if(ara[i] > max){
            max = ara[i];
        }
        sum=sum+ara[i];
    }

    printf("Sum: %d, | Min: %d, | Max: %d",sum,min,max);
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
   printf("Total time taken by CPU: %fl\n", total_t  );

   printf("Exiting of the program...\n");

    return 0;

}