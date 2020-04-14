#include <stdio.h>
#include <stdlib.h>

/*
create_list
retrive_node
destroy_list
add_node
search_list
remove_node
*/

typedef struct node{
    void* data;
    struct node* link;
} Node;

typedef struct{
    int count;
    Node* head_node;
} LinkedList;

// Creates an empty linked list
LinkedList* create_list(void){

    LinkedList* ll_ptr = (LinkedList*) malloc(sizeof(LinkedList));

    ll_ptr->count = 0;
    ll_ptr->head_node = NULL;

    return ll_ptr;
}

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

}



int main(void){

    LinkedList* ll_ptr = create_list();

    int data1 = 20;
    add_node(ll_ptr, &data1);

    int data2 = 306;
    add_node(ll_ptr, &data2);

    char data3 = 'F';
    add_node(ll_ptr, &data3);


    printf("%d\n", *(int*)(ll_ptr->head_node->data));
    printf("%d\n", *(int*)(ll_ptr->head_node->link->data));
    printf("%c\n", *(char*)(ll_ptr->head_node->link->link->data));

    return 0;
}
