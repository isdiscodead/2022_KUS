#include <iostream>
using namespace std;


template <class Item>
class BST_node { 
public : 
    // typedef
    typdef Item value_type;

    // constructor 

    // getter 


private : 
    Item key_field;
    BST_node *left_son;
    BST_node *right_son; 
};


// search -> O(h)
BST_node* search( BST_node* root, int key ) {
    if ( !root ) {
        return NULL;
    }

    if ( key == root->key_field ) {
        return root;
    }

    if ( key < root->key_field ) {
        return search(root->left, key);
    } else {
        return search(root->right, key);
    }
}

// clear the tree
void tree_clear() {

}


int main(void) {


    return 0;
}