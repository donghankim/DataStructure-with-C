#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    void* data;
    struct node* link;

}Node;

Node* createNode(void* value){
    Node* nodePtr = (Node*) malloc(sizeof(Node));
    nodePtr->data = value;
    nodePtr->link = NULL;
    return nodePtr;
}

int main(void){

    int* new_node = (int*) malloc(sizeof(int));
    *new_node = 10;
    Node* n1 = createNode(new_node);

    new_node = (int*) malloc(sizeof(int));
    *new_node = 100;
    n1->link = createNode(new_node);

    char* new_char_node = (char*) malloc(sizeof(char));
    *new_char_node = 'A';
    n1->link->link = createNode(new_char_node);

    printf("first node value: %d\nsecond node value: %d\nthird node value: %c\n", *(int*)n1->data, *(int*)n1->link->data, *(char*)n1->link->link->data);

    return 0;
}
