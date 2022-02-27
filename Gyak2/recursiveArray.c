#include <stdio.h>
#include <time.h>

int calculateMin(int ara[], int length);
int calculateMax(int ara[], int length);
int calculateSum(int ara[], int length);

int main(){
    int i,size;
   
    printf("Enter array length : \n");
    scanf("%d",&size);
    
    int ara[size];
    
     printf("Enter array elements:\n");
     for(i = 0; i < size;  i++){
        scanf("%d", &ara[i]);
     }
    start_t = clock();
    printf("Min number is %d\n",calculateMin(ara,size));
    end_t = clock();
         total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
   printf("Min futasi ideje: %fl\n", total_t  );
    start_t = clock();
    printf("Max number is %d\n",calculateMax(ara,size));
    end_t=clock();
         total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
   printf("Max futasi ideje: %fl\n", total_t  );
    start_t = clock();
    printf("Sum: %d\n",calculateSum(ara,size));
    end_t=clock();
         total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
   printf("Sum futasi ideje: %fl\n", total_t  );

    return 0;

}

int calculateMin(int ara[], int length) {

  int min=ara[0];
  int i;
  printf("calculating min.\n");
  for(i = 0; i < length; i++){
        
        if(ara[i] < min){
            min = ara[i];
        }
    }


  return min;
}

int calculateMax(int ara[], int length) {

    int i;
  int max=ara[0];
  printf("calculating max.\n");
  for(i = 0; i < length; i++){
        
        if(ara[i] > max){
            max = ara[i];
        }
    }

  return max;
}

int calculateSum(int ara[], int length) {

    int i;
  int sum=0;
  printf("calculating sum.\n");
  for(i = 0; i < length; i++){
        
        sum=sum+ara[i];
    }

   printf("Sum futasi ideje: %fl\n", total_t  );
  return sum;
}