#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    void* data;
    struct node* next;
} Node;

typedef struct head{
    int count;
    Node* head_node;
} Stack;

Stack* create_stack(void);
void push(Stack* Stack_ptr, void* new_data);
void pop(Stack* Stack_ptr);
void* peak(Stack* Stack_ptr);
void int_print_stack(Stack* Stack_ptr);
void destroy_stack(Stack* Stack_ptr);

int main(void){

    Stack* Stack_ptr = create_stack();

    int data1 = 10;
    push(Stack_ptr, &data1);

    char data2 = 'A';
    push(Stack_ptr, &data2);

    double data3 = 30.20;
    push(Stack_ptr, &data3);

    destroy_stack(Stack_ptr);
    return 0;
}

Stack* create_stack(void){

    Stack* Stack_ptr = (Stack*) malloc(sizeof(Stack));
    Stack_ptr->count = 0;
    Stack_ptr->head_node = NULL;

    return Stack_ptr;
}

void push(Stack* Stack_ptr, void* new_data){

    Node* new_node = (Node*) malloc(sizeof(Node));
    new_node->data = new_data;
    new_node->next = NULL;

    if(Stack_ptr->count == 0){
        Stack_ptr->head_node = new_node;
        (Stack_ptr->count)++;
    } else{
        Node* old_head = Stack_ptr->head_node;
        Stack_ptr->head_node = new_node;
        Stack_ptr->head_node->next = old_head;
        (Stack_ptr->count)++;
    }
}

void pop(Stack* Stack_ptr){

    if(Stack_ptr->count == 0){
        printf("Stack is empty...\n");
        return;
    } else{
        Node* del_node = Stack_ptr->head_node;
        Node* new_head = Stack_ptr->head_node->next;
        free(del_node);

        Stack_ptr->head_node = new_head;
        (Stack_ptr->count)--;
    }
}

void* peak(Stack* Stack_ptr){
    if(Stack_ptr->count == 0){
        printf("Stack is empty...\n");
    } else{
        return Stack_ptr->head_node->data;
    }
}

void int_print_stack(Stack* Stack_ptr){

    if(Stack_ptr->count <= 1){
        if(Stack_ptr->head_node == NULL){
            printf("Stack is empty...\n");
        }else{
            printf("%d\n", *(int*)Stack_ptr->head_node->data);
        }
    } else{
        Node* traverse = Stack_ptr->head_node;
        while(traverse->next != NULL){
            printf("%d ", *(int*)traverse->data);
            traverse = traverse->next;
        }printf("%d\n", *(int*)traverse->data);
    }
}

void destroy_stack(Stack* Stack_ptr){

    Node* head = Stack_ptr->head_node;
    Node* traverse;

    while(head){
        traverse = head;
        head = traverse->next;
        free(traverse);
    }
    Stack_ptr->count = 0;
    Stack_ptr->head_node = NULL;
    free(Stack_ptr);
}

