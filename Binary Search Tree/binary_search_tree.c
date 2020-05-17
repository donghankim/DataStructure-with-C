#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node* left;
    struct node* right;
} NODE;

typedef struct tree{
    NODE* root_node;
} TREE;

TREE* create_tree(void);
NODE* create_node(int val);
NODE* insert_node(NODE* node, NODE* new_node);
void inorder_print(NODE* root_node);
void search_tree(NODE* node, int val);
void delete_node(NODE* node, int val);

int main(void){

    TREE* tree = create_tree();
    if(!tree){
        printf("memory full.\n");
    }

    int values[10] = {1,9,2,1,0,10,5,3,18,3};

    // inserting values into binary tree.
    for(int i = 0; i < sizeof(values)/sizeof(values[0]); i++){
        NODE* new_node = create_node(values[i]);
        if(!new_node){
            printf("memory is full, could not insert %d.\n", values[i]);
        } else{
            tree->root_node = insert_node(tree->root_node, new_node);
        }
    }

    inorder_print(tree->root_node);
    printf("\n");
    search_tree(tree->root_node, 100);
    delete_node(tree->root_node, 10);
    inorder_print(tree->root_node);

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

// not complete
void delete_node(NODE* node, int val){
    if(!node){
        printf("%d not found.\n", val);
        return;
    } else if(node->data == val){
        printf("%d deleted.\n", val);
        free(node);
        return;
    }

    if(node->data > val){
        return delete_node(node->left, val);
    } else{
        return delete_node(node->right, val);
    }
}
