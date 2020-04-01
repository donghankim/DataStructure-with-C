#include <stdio.h>
#include <stdlib.h>

void print_arr(int arr[], int len){
    for(int i = 0; i < len; i++){
        printf("%d ", arr[i]);
    }printf("\n");
}

void set_arr(int arr[], int len){
    for(int i = 0; i < len; i++){
        arr[i] = 1 + rand()%10;
    }
}


int main(void){

    int* arr_ptr = (int*) malloc(10*sizeof(int));
    set_arr(arr_ptr, 10);
    print_arr(arr_ptr, 10);

    arr_ptr = realloc(arr_ptr, 20*sizeof(int));
    print_arr(arr_ptr, 20);

    return 0;
}
