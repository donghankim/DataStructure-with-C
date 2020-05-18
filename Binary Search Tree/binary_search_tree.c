#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node* left;
    struct node* right;
} NODE;

typedef struct tree{
    NODE* root_node;
    int count;
} TREE;

TREE* create_tree(void);
NODE* create_node(int val);
NODE* insert_node(NODE* node, NODE* new_node);
NODE* minNode(NODE* node);
NODE* delete_node(NODE* node, int val);
void inorder_print(NODE* root_node);
void search_tree(NODE* node, int val);

int main(void){

    TREE* tree = create_tree();
    if(!tree){
        printf("memory full.\n");
    }

    int values[7] = {9,2,10,5,3,18,3};

    // inserting values into binary tree.
    for(int i = 0; i < sizeof(values)/sizeof(values[0]); i++){
        NODE* new_node = create_node(values[i]);
        if(!new_node){
            printf("memory is full, could not insert %d.\n", values[i]);
        } else{
            tree->root_node = insert_node(tree->root_node, new_node);
        }
    }

    // print binary search tree
    inorder_print(tree->root_node);
    printf("\n");

    // delete root node (which is 9)
    tree->root_node = delete_node(tree->root_node, 9);

    // print new binary search tree
    inorder_print(tree->root_node);
    printf("\n");

    return 0;
}


TREE* create_tree(void){
    TREE* new_tree = (TREE*) malloc(sizeof(TREE));

    if(!new_tree){
        return NULL;
    } else{
        new_tree->root_node = NULL;
    }
    return new_tree;
}

NODE* create_node(int val){
    NODE* new_node = (NODE*) malloc(sizeof(NODE));

    if(!new_node){
        return NULL;
    } else{
        new_node->data = val;
        new_node->left = NULL;
        new_node->right = NULL;
    }
    return new_node;
}

NODE* insert_node(NODE* node, NODE* new_node){
    // node represents the root node when function called first.
    if(!node){
        node = new_node;
        return node;
    }

    if(node->data > new_node->data){
        node->left = insert_node(node->left, new_node);
        return node;
    } else{
        node->right =  insert_node(node->right, new_node);
        return node;
    }
}

void inorder_print(NODE* root_node){
    if(!root_node){
        return;
    } else{
        inorder_print(root_node->left);
        printf("%d ", root_node->data);
        inorder_print(root_node->right);
    }
}

void search_tree(NODE* node, int val){
    if(!node){
        printf("%d not found.\n", val);
        return;
    } else if(node->data == val){
        printf("%d found in tree.\n", val);
        return;
    }

    if(node->data > val){
        return search_tree(node->left, val);
    } else{
        return search_tree(node->right, val);
    }
}

NODE* minNode(NODE* node){
    if(!node->left){
        return node;
    } else{
        return minNode(node->left);
    }
}

NODE* delete_node(NODE* node, int val){
    if(!node){
        printf("%d not found.\n", val);
        return NULL;
    }

    if(node->data > val){
        node->left = delete_node(node->left, val);
    }
    else if(node->data < val){
        node->right = delete_node(node->right, val);
    }
    else{
        if(node->right == NULL && node->left == NULL){
            NODE* temp = node->left;
            free(node);
            return temp;
        }
        else if(node->right == NULL){
            NODE* temp = node->left;
            free(node);
            return temp;
        }
        else if(node->left == NULL){
            NODE* temp = node->right;
            free(node);
            return temp;
        }
        else{
            NODE* temp = minNode(node->right);
            node->data = temp->data;
            node->right = delete_node(node->right, temp->data);
            return node;
        }
    }
}


