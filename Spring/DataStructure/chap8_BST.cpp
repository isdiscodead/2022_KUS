#include <iostream>
using namespace std;


template <class Item> // 템플릿으로 자료형 사용 
class BST_node { 
public : 
    // typedef
    typedef Item value_type;

    // constructor 
    BST_node(Item item, BST_node<Item>* left, BST_node<Item>* right) {    
        this->key_field = item;
        this->left_son = left;
        this->right_son = right;
    }


    // getter 
    Item getKey() {
        return this->key_field;
    }
    BST_node<Item>* getLeftSon() {
        return this->left_son;
    }
    BST_node<Item>* getRightSon() {
        return this->right_son;
    }

    // setter 
    void setKey(Item key) {
        this->key_field = key;
    }
    void setLeftSon(BST_node<Item>* left) {
        this->left_son = left;
    }
    void setRightSon(BST_node<Item>* right) {
        this->right_son = right;
    }





    // delete
    void nodeDelete(BST_node<Item>* root, BST_node<Item>* parent, Item target) {
        BST_node<Item>* ptr;

        if ( !root ) {
            cout << "tree is empty";
            return;
        }

        // 하위로 더 내려가야 할 경우 
        if ( root->getLeftSon() && target < root->getKey() ) {
            nodeDelete(root->getLeftSon(), root, target);
        } else if ( root->getRightSon() && target >= root->getKey()) {
            nodeDelete(root->getRightSon(), root, target);
        } 

        // 삭제할 노드 찾았을 경우 
        if ( target == root->getKey() ) {
            // case 1. no left child & no right child 
            if ( (! root->getLeftSon()) && (! root->getRightSon())) { 
                if ( parent->getLeftSon() ) {
                    parent->setLeftSon(NULL);
                    delete root;
                } else {
                    parent->setRightSon(NULL);
                    delete root;
                }

            // case 2. only one sub tree exists
            } else if ( (! root->getRightSon()) || (! root->getLeftSon()) ) {
                BST_node<Item>* childNode = (!root->getLeftSon()) ? root->getLeftSon() : root->getRightSon();
                if( root == parent ){    // 삭제하려는 node가 root인 경우 왼쪽 서브트리의 root를 위로 끌어올림 
                    parent->setLeftSon(childNode);
                    delete root;
                }else{
                    if(parent->getLeftSon() == root){        // parent의 왼쪽 자식노드에 childNode link
                        parent->setLeftSon(childNode);
                    }else if(parent->getRightSon() == root){ // parent의 오른쪽 자식노드 childNode link
                        parent->setRightSon(childNode);
                    }
                    delete root;
                }

            // case 3. two sub tree exists
            } else {
                // 삭제하려는 노드의 오른쪽 서브트리에서 가장 작은 노드를 탐색하는 과정
                BST_node<Item>* succp = root;
                BST_node<Item>* succ = root->getRightSon();

                while(succ->getLeftSon() != NULL){
                    succp = succ;
                    succ = succ->getLeftSon();
                }

                // 3-1. 후계자 노드의 부모와 후계자 노드의 자식 연결
                if(succp->getLeftSon() == succ){
                    succp->setLeftSon(succ->getRightSon());
                }else{  // 후계자 노드가 삭제할 노드의 바로 오른쪽 자식인 경우
                    succp->setRightSon(succ->getRightSon());
                }

                // 3-2. 삭제할 노드의 data를 후계자노드의 data로 대체
                root->setKey(succ->getKey());

                // 3-3. 삭제할 노드를 후계자노드로 변경 (후계자노드를 delete 하기 위해)
                root = succ;

                delete root;
            }
        }
        
    }


private : 
    Item key_field;
    BST_node *left_son;
    BST_node *right_son; 
};


// search -> O(h)
template <class Item>
BST_node<Item>* search( BST_node<Item>* root, Item key ) {
    if ( !root ) {
        return NULL;
    }

    if ( key == root->getKey() ) {
        return root;
    }

    if ( key < root->getKey() ) {
        return search(root->getLeftSon(), key);
    } else {
        return search(root->getRightSon(), key);
    }
}


// inorder :  L -> V -> R : Ascending 
template <class Item>
void inorder( BST_node<Item>* node_ptr ) {
    // root 탐색 
    if ( node_ptr ) {
        // 재귀 호출로 subtree 탐색 
        inorder (node_ptr->getLeftSon());
        cout << node_ptr->getKey() << " ";
        inorder (node_ptr->getRightSon());
    }
}



int main(void) {
    BST_node<string>* root = new BST_node<string>("data", NULL, NULL);
    root->nodeInsert(root, "structure");
    root->nodeInsert(root, "is");
    root->nodeInsert(root, "one");
    root->nodeInsert(root, "of");
    root->nodeInsert(root, "the");
    root->nodeInsert(root, "most");
    root->nodeInsert(root, "important");
    root->nodeInsert(root, "courses");
    root->nodeInsert(root, "in");
    root->nodeInsert(root, "computer");
    root->nodeInsert(root, "science");

    inorder(root);

    BST_node<string>* searched =  search(root, string("the"));
    cout << endl << searched->getKey() << endl;

    root->nodeDelete(root, root, "in");
    inorder(root);

    return 0;
}