#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    void* data;
    struct node* next;
} Node;

typedef struct head{
    int count;
    Node* head_node;
    Node* tail_node;
} Queue;

Queue* create_queue(void);
void enqueue(Queue* Queue_ptr, void* new_data);
void dequeue(Queue* Queue_ptr);
void* head_peak(Queue* Queue_ptr);
void* tail_peak(Queue* Queue_ptr);
void int_print_queue(Queue* Queue_ptr);
void destroy_queue(Queue* Queue_ptr);

int main(void){

    Queue* Queue_ptr = create_queue();

    int data1 = 10;
    enqueue(Queue_ptr, &data1);

    int data2 = 20;
    enqueue(Queue_ptr, &data2);

    int data3 = 30;
    enqueue(Queue_ptr, &data3);

    int data4 = 40;
    enqueue(Queue_ptr, &data4);
    int_print_queue(Queue_ptr);

    void* head_data = head_peak(Queue_ptr);
    void* tail_data = tail_peak(Queue_ptr);

    printf("head node data: %d\n", *(int*)head_data);
    printf("tail node data: %d\n", *(int*)tail_data);

    destroy_queue(Queue_ptr);
    return 0;
}

Queue* create_queue(void){

    Queue* Queue_ptr = (Queue*) malloc(sizeof(Queue));
    Queue_ptr->count = 0;
    Queue_ptr->head_node = NULL;
    Queue_ptr->tail_node = NULL;

    return Queue_ptr;
}

void enqueue(Queue* Queue_ptr, void* new_data){

    Node* new_node = (Node*) malloc(sizeof(Node));
    new_node->data = new_data;
    new_node->next = NULL;

    if(Queue_ptr->count == 0){
        Queue_ptr->head_node = new_node;
        Queue_ptr->tail_node = new_node;
        Queue_ptr->head_node->next = Queue_ptr->tail_node;
        (Queue_ptr->count)++;
    } else{
        Node* old_tail = Queue_ptr->tail_node;
        old_tail->next = new_node;
        Queue_ptr->tail_node = new_node;
        (Queue_ptr->count)++;
    }
}

void dequeue(Queue* Queue_ptr){

    if(Queue_ptr->count == 0){
        printf("Queue is empty...\n");
    } else{
        Node* new_head = Queue_ptr->head_node->next;
        Node* del_node = Queue_ptr->head_node;
        free(del_node);

        Queue_ptr->head_node = new_head;
        (Queue_ptr->count)--;
    }
}

void* head_peak(Queue* Queue_ptr){
    if(Queue_ptr->count == 0){
        printf("Queue is empty...\n");
        return NULL;
    } else{
        return Queue_ptr->head_node->data;
    }
}

void* tail_peak(Queue* Queue_ptr){
    if(Queue_ptr->count == 0){
        printf("Queue is empty...\n");
        return NULL;
    } else{
        return Queue_ptr->tail_node->data;
    }
}

void int_print_queue(Queue* Queue_ptr){

    if(Queue_ptr->count == 0){
        printf("Queue is empty...\n");
    } else{
        Node* traverse = Queue_ptr->head_node;
        while(traverse->next != NULL){
            printf("%d ", *(int*)traverse->data);
            traverse = traverse->next;
        } printf("%d\n", *(int*)traverse->data);
    }
}

void destroy_queue(Queue* Queue_ptr){

    Node* head = Queue_ptr->head_node;
    Node* traverse;

    while(head){
        traverse = head;
        head = traverse->next;
        free(traverse);
    }

    Queue_ptr->count = 0;
    Queue_ptr->head_node = NULL;
    Queue_ptr->tail_node = NULL;
    free(Queue_ptr);
}
