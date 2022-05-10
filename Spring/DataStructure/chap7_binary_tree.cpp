#include <iostream>
using namespace std;


class Binary {

private:
    string data;
    Binary* left_child;
    Binary* right_child;

public: 
    Binary(string data, Binary* left, Binary* right ) {
        this->data = data;
        this->left_child = left;
        this->right_child = right;
    }

    string getData() {
        return this->data;
    }

    Binary* getLeftChild() {
        return this->left_child;
    }

    Binary* getRightChild() {
        return this->right_child;
    }
};


// Preorder : V -> L -> R
void preorder( Binary* node_ptr ) {
    // root 탐색 
    if ( node_ptr ) {
        cout << node_ptr->getData() << endl;
        // 재귀 호출로 subtree 탐색 
        preorder (node_ptr->getLeftChild());
        preorder (node_ptr->getRightChild());
    }
}

// inorder :  L -> V -> R
void inorder( Binary* node_ptr ) {
    // root 탐색 
    if ( node_ptr ) {
        // 재귀 호출로 subtree 탐색 
        inorder (node_ptr->getLeftChild());
        cout << node_ptr->getData() << endl;
        inorder (node_ptr->getRightChild());
    }
}

// postorder :  L -> R -> V
void postorder( Binary* node_ptr ) {
    // root 탐색 
    if ( node_ptr ) {
        // 재귀 호출로 subtree 탐색 
        postorder (node_ptr->getLeftChild());
        postorder (node_ptr->getRightChild());
        cout << node_ptr->getData() << endl;
    }
}


int main( void ) {
    Binary leaf1 = Binary("4", NULL, NULL);
    Binary leaf2 = Binary("5", NULL, NULL);
    Binary leaf3 = Binary("6", NULL, NULL);
    Binary leaf4 = Binary("7", NULL, NULL);
    Binary internal1 = Binary("2", &leaf1, &leaf2);
    Binary internal2 = Binary("3", &leaf3, &leaf4);
    Binary root = Binary("1", &internal1, &internal2);

    cout << "Preorder Traversal" << endl;
    preorder(&root);
    cout << "Inorder Traversal" << endl;
    inorder(&root);
    cout << "Postorder Traversal" << endl;
    postorder(&root);

    return 0;
}