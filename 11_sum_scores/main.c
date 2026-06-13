#include <stdio.h>

int main(){

    int sum = 0;
    int numbers[5] = {1,2,3,4,5};

    int size = sizeof(numbers) / sizeof(int);
    for(int i = 0; i < size; i++){
        sum = sum + numbers[i];
    }

    printf("the sum of the array is %d\n", sum);


    return 0;
}


