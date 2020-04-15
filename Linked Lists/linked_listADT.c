#include <stdio.h>
#include <stdlib.h>

// node structure
typedef struct node{
    void* data;
    struct node* link;
} Node;

// linked list structure
typedef struct{
    int count;
    Node* head_node;
} LinkedList;

LinkedList* create_list(void);
void add_node(LinkedList* ll_ptr, void* new_data);
void insert_(LinkedList* ll_ptr, int index, void* val);
void remove_node(LinkedList* ll_ptr);
void remove_(LinkedList* ll_ptr, int index);
void* retrieve_node(LinkedList* ll_ptr, int index);
void print_list(LinkedList* ll_ptr);
void destroy_list(LinkedList* ll_ptr);

int main(void){

    LinkedList* ll_ptr = create_list();

    int data1 = 1;
    add_node(ll_ptr, &data1);

    char data2 = 'A';
    add_node(ll_ptr, &data2);

    int data3 = 3;
    add_node(ll_ptr, &data3);

    double data4 = 4.1;
    add_node(ll_ptr, &data4);

    float data5 = 5.2;
    insert_(ll_ptr, 2, &data5);

    print_list(ll_ptr);

    destroy_list(ll_ptr);

    return 0;
}


// Creates an empty linked list
LinkedList* create_list(void){

    LinkedList* ll_ptr = (LinkedList*) malloc(sizeof(LinkedList));

    ll_ptr->count = 0;
    ll_ptr->head_node = NULL;

    return ll_ptr;
}

// adds node to the end of the list
void add_node(LinkedList* ll_ptr, void* new_data){

    Node* new_node = (Node*) malloc(sizeof(Node));
    new_node->data = new_data;
    new_node->link = NULL;

    if (ll_ptr->count == 0){
        ll_ptr->head_node = new_node;
    }else{
        Node* tempNode = ll_ptr->head_node;

        while(tempNode->link != NULL){
            tempNode = tempNode->link;
        }
        tempNode->link = new_node;
    }
    (ll_ptr->count)++;

    return;
}

// removes node at the end of a list
void remove_node(LinkedList* ll_ptr){

    Node* traverse = (Node*) malloc(sizeof(Node));
    Node* del_node = (Node*) malloc(sizeof(Node));

    traverse = ll_ptr->head_node;

    while(traverse->link->link != NULL){
        traverse = traverse->link;
    }

    del_node = traverse->link;
    traverse->link = NULL;
    free(del_node);
    (ll_ptr->count)--;

    return;
}

// adds node to specified location (index)
void insert_(LinkedList* ll_ptr, int index, void* val){

    if(index > ll_ptr->count){
        printf("Index out of range\n");
        return;
    }

    Node* new_node = (Node*) malloc(sizeof(Node));
    new_node->data = val;

    Node* prev_node = (Node*) malloc(sizeof(Node));
    prev_node = ll_ptr->head_node;

    Node* next_node = (Node*) malloc(sizeof(Node));

    for(int i = 1; i < index - 1; i++){
        prev_node = prev_node->link;
    }

    next_node = prev_node->link;
    prev_node->link = new_node;
    new_node->link = next_node;

    (ll_ptr->count)++;

    return;
}

// removes node at specificed location (index)
void remove_(LinkedList* ll_ptr, int index){

    if(index > ll_ptr->count){
        printf("Index out of range\n");
        return;
    }

    Node* prev_node = (Node*) malloc(sizeof(Node));
    Node* next_node = (Node*) malloc(sizeof(Node));
    Node* del_node = (Node*) malloc(sizeof(Node));

    prev_node = ll_ptr->head_node;

    for(int i = 1; i < index -1; i++){
        prev_node = prev_node->link;
    }
    del_node = prev_node->link;
    next_node = del_node->link;
    prev_node->link = next_node;
    free(del_node);

    (ll_ptr->count)--;

    return;
}

// returns node data at given location (index), but doesnt alter the node
void* retrieve_node(LinkedList* ll_ptr, int index){

    if(index > ll_ptr->count){
        printf("Index out of range\n");
        return NULL;
    }

    Node* ret_node = ll_ptr->head_node;

    for(int i = 1; i < index; i++){
        ret_node = ret_node->link;
    }

    return ret_node->data;
}

// prints the entire linked list
void print_list(LinkedList* ll_ptr){

    Node* traverse = (Node*) malloc(sizeof(Node));
    traverse = ll_ptr->head_node;
    int i = 1;

    while(traverse->link != NULL){
        printf("Data at Node %d is at location %p\n", i, traverse->data);
        traverse = traverse->link;
        i++ ;
    }
    printf("Data at Node %d is at location %p\n", i, traverse->data);
}

// frees dyanmic memory used in creating linked list -> error
void destroy_list(LinkedList* ll_ptr){

    Node* head = (Node*) malloc(sizeof(Node));
    Node* traverse = (Node*) malloc(sizeof(Node));

    head = ll_ptr->head_node;

    while(head){
        traverse = head;
        head = traverse->link;
        free(traverse);
    }

    ll_ptr->count = 0;
    free(ll_ptr);

    return;
}
