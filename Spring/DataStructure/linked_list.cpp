#include <iostream>
using namespace std;

// 연결 리스트 node 클래스 정의
class node {
    public: 
        typedef int value_type;

        // 생성자
        node(const value_type& init_data = value_type(), node* init_link = NULL) {
            this->data = init_data;
            this->link = init_link;
        }
        
        // 출력 함수 
        void print() {
            cout << this->data << " / next : " << this->link << endl;
        }

        friend int list_length(const node* head_ptr);

    private:
        value_type data;
        node *link;
};


// program 1. computes the length of a linked list 
int node::list_length(const node* head_ptr) {
    const node *cursor; // 현재 가리키고 있는 위치 
    int answer = 0; // 길이를 담는 변수
    for ( cursor=head_ptr ; cursor ; cursor = cursor->link()) {
        ++answer;
    }
    return answer;
}


int main(void) {

    node *p, *q, *r;

    // 일반적 node 사용 예제 
    p = new node;
    q = new node(1);
    r = new node(2, p);

    p->print();
    cout << p << endl;
    q->print();
    r->print();


    // 연결 리스트 사용 예제 
    node * head_ptr = new node(1, NULL);
    head_ptr = new node(2, head_ptr);
    head_ptr = new node(3, head_ptr);
    head_ptr = new node(4, head_ptr);

    cout << "len: " << list_length(head_ptr);

    return 0;
}