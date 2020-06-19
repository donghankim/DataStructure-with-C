#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NUM 10

typedef struct heap{
    int* arr;
    int count;
} HEAP;

HEAP* create_heap(void){
    HEAP* heap_ptr = (HEAP*) malloc(sizeof(HEAP));
    heap_ptr->count = 0;
    heap_ptr->arr = (int*) malloc(sizeof(int)*NUM);
    return heap_ptr;
}

void heapify_up(HEAP* heap_ptr, int index){
    if (index == 0) return;
    else{
        int p_index = floor((index - 1) / 2);
        int parent = heap_ptr->arr[p_index];
        if (parent < heap_ptr->arr[index]){
            int temp = heap_ptr->arr[p_index];
            heap_ptr->arr[p_index] = heap_ptr->arr[index];
            heap_ptr->arr[index] = temp;
            heapify_up(heap_ptr, p_index);
        }
    }
}

void heapify_down(HEAP* heap_ptr, int index){
    int left = 2*index + 1;
    int right = 2*index + 2;

    if(left > heap_ptr->count){
        return;
    } else{
        if(heap_ptr->arr[left] > heap_ptr->arr[right]){
            if(heap_ptr->arr[index] < heap_ptr->arr[left]){
                int temp = heap_ptr->arr[index];
                heap_ptr->arr[index] = heap_ptr->arr[left];
                heap_ptr->arr[left] = temp;
                heapify_down(heap_ptr, left);
            }
        } else{
            if(heap_ptr->arr[index] < heap_ptr->arr[right]){
                int temp = heap_ptr->arr[index];
                heap_ptr->arr[index] = heap_ptr->arr[right];
                heap_ptr->arr[right] = temp;
                heapify_down(heap_ptr, right);
            }
        }
    }

}

void heap_insert(HEAP* heap_ptr, int data){
    if(heap_ptr->count == NUM){
        printf("Heap is full. \n");
    }
    heap_ptr->arr[heap_ptr->count] = data;
    heapify_up(heap_ptr, heap_ptr->count);
    heap_ptr->count++;
}

void heap_remove(HEAP* heap_ptr, int data){
    // find index
    int del_index = -1;
    for(int i = 0; i < heap_ptr->count; i++){
        if(heap_ptr->arr[i] == data){
            del_index = i;
        }
    }

    if(del_index == -1){
        printf("The data %d was not found.\n", data);
    } else{
        int temp = heap_ptr->arr[heap_ptr->count];
        heap_ptr->arr[del_index] = temp;
        heap_ptr->count--;
        heapify_down(heap_ptr, 0);
    }

}

void print_heap(HEAP* heap_ptr){
    for(int i = 0; i < heap_ptr->count; i++){
        printf("%d ", heap_ptr->arr[i]);
    }printf("\n");
}

int main(void){

    // max-heap imeplementation
    HEAP* heap_ptr = create_heap();
    int data[NUM] = {39,1,10,54,32,9,8,74,11,7};

    for(int i = 0; i < NUM; i++){
        heap_insert(heap_ptr, data[i]);
        print_heap(heap_ptr);
    }

    heap_remove(heap_ptr, 74);
    print_heap(heap_ptr);

    return 0;
}


