/*
[ 연결 리스트 ( Linked List ) ]
    각 노드는 data와, 포인터인 link 필드를 가지고 있어
    물리적으로 이어져있지 않은 노드들 사이를 포인터 주소를 활용해 이어준 리스트 
*/

/*
[ parameters for linked list ]
    const node* = 리스트 변경 X 포인터 변경 X
    node* = 리스트 변경 O 포인터 변경 X
    node*& = 리스트 변경 O 포인터 변경 O 
*/

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

        // setter
        void set_data(const value_type &data) {
            this->data = data;
        }
        void set_link(node* link) { // const node*로 넣어주려면 link 자체가 const여야 함 ( 포인터는 메모리를 공유하므로 )
            this->link = link;
        }

        // getter 
        node* get_link() {
            return this->link;
        }
        value_type get_data() {
            return this->data;
        }
        
        // 출력 함수 
        void print() {
            cout << this->data << " / next : " << this->link << endl;
        }

        // 연결 리스트 관련 연산 함수들 
        friend int list_length(const node* head_ptr);
        friend void list_head_insert(node* &head_ptr, const node::value_type &entry);
        friend void list_insert(node* previous_ptr, const node::value_type& entry);
        friend void list_copy(const node* source_ptr, node* &head_ptr, node* &tail_ptr);
        friend void remove_head(node* &head_ptr);
        friend void remove_nonhead(node* prev_ptr);
        friend node* list_search(node* head_ptr, const node::value_type& target);

    // node 객체의 필드
    private:
        value_type data;
        node *link;
};


// double linked list -> 양방향 탐색 가능, 추가 메모리 사용 
// 삭제, 추가 등 변경 시 rlink, llink 모두 변경해야 함 
class double_ll {
public:
    typedef int value_type;
    void set_data(const value_type &new_data);
    void set_llink(node* new_llink);
    void set_rlink(node* new_rlink);

private:
    value_type data;
    node *llink;
    node *rlink;
};


// program 1. computes the length of a linked list 
int list_length( const node* head_ptr ) { // head_ptr은 변경되지 않으므로 const 매개변수 
    const node *cursor; // 현재 가리키고 있는 위치 
    int answer = 0; // 길이를 담는 변수
    for ( cursor=head_ptr ; cursor ; cursor=cursor->link ) { // 현재 위치가 유효할 때까지 link 필드를 통해 다음 node의 주소 접근
        ++answer;
    }
    return answer;
}


// program 2. insert a new node at the head position
void list_head_insert( node* &head_ptr, const node::value_type &entry ) {
    // 새 노드로 인해 head_ptr의 위치가 변경되므로 &head_ptr 참조변수
    // entry ( 새 노드의 값 )을 참조변수로 받는 이유는 모르겠... 지만... 흠... 왜지? 
    head_ptr = new node(entry, head_ptr); // 기존의 head를 다음 node로 가지는 새 node 
}


// program 3. insert a new node in the middle of a list
void list_insert( node* previous_ptr, const node::value_type& entry ) { // 앞의 노드는 link만 건들 것이기 때문에 그냥 변수 
    node *insert_ptr;
    insert_ptr = new node(entry, previous_ptr->link);
    previous_ptr -> set_link(insert_ptr); // 추가된 노드의 주소로 link
}


// program 4. copy a linked list 
void list_copy(const node* source_ptr, node* &head_ptr, node* &tail_ptr) { // head, tail은 임의의 새 node pointer ( 반환용 )
    head_ptr = NULL; tail_ptr = NULL; // 기존의 값이 있을 수도 있으니 NULL로 초기화 
    if ( source_ptr == NULL ) return; // 복사하려는 list가 비어있을 경우 종료 

    list_head_insert(head_ptr, source_ptr->data); // head 부분 복사
    source_ptr = source_ptr->link; // 나머지 노드로 이동 
    tail_ptr = head_ptr; // 방금 추가한 첫 노드의 주소를 tail_ptr에 담기 

    while ( source_ptr ) {
        list_insert(tail_ptr, source_ptr->data); // head 뒤에 새 노드 추가
        tail_ptr = head_ptr->link; // 방금 추가한 새 노드의 주소를 다시 tail_ptr에 담기
        source_ptr = source_ptr->link; // 다음 복사할 노드로 이동
    }

}


// program 5. delete head node
void remove_head(node* &head_ptr) {
    node *remove_ptr = head_ptr;   // 지워질 head의 주소를 담음
    head_ptr = head_ptr->link; // 다음 노드로 head 변경
    delete remove_ptr; // 지울 head 메모리 반환
}


// program 6. delete non-head node
void remove_nonhead(node* prev_ptr) { // 앞의 노드를 직접 변경하는 것이 아닌 link 변경하는 것
    node *remove_ptr = prev_ptr->link; // 지울 node의 주소 담기
    prev_ptr->set_link(remove_ptr->link); // 다음 node의 주소를 앞 node에 link로 담아서 이어줌
    delete remove_ptr;
}


// program 7. search key
node* list_search(node* head_ptr, const node::value_type& target) {
    for (node* cursor=head_ptr ; cursor ; cursor=cursor->link) {
        if ( cursor->data == target ) {
            return cursor;
        }
    }
    return NULL; // 찾지 못했을 경우 null pointer 반환
}


// main function 
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
    cout << "=======================" << endl;

    // 연결 리스트 사용 예제 
    node * head_ptr = new node(1, NULL); // 첫 노드이기 때문에 NULL Pointer 사용 
    head_ptr = new node(2, head_ptr); // 매번 바로 앞서 만든 node의 주소( head_ptr )을 link로 가져 연결 
    head_ptr = new node(3, head_ptr);
    head_ptr = new node(4, head_ptr);

    // Program 1. 리스트 길이 확인 
    cout << "len: " << list_length(head_ptr) << endl << endl;

    // Program 2. 새 head 노드 추가
    int value = -1;
    list_head_insert(head_ptr, 0);
    list_head_insert(head_ptr, value);
    // 정상 추가 확인 
    cout << "len: " << list_length(head_ptr) << endl << endl;

    // Program 3. 중간에 새 노드 추가  
    cout << "head: " << head_ptr->get_data() << endl;
    list_insert(head_ptr->get_link()->get_link(), (head_ptr->get_link()->get_link()->get_link()->get_data()+10)); // 2 + 10
    // 정상 추가 확인
    cout << "new: " << head_ptr->get_link()->get_link()->get_link()->get_data() << endl << endl;

    // Program 4. 리스트 복사 
    node * head2 = NULL;
    node * tail2 = NULL;

    list_copy(head_ptr, head2, tail2);
    cout << "copy list len: " << list_length(head2) << endl << endl;

    // Program 5. 헤드 삭제
    remove_head(head2);
    cout << "head deleted: " << head2->get_data() << endl << endl;

    // Program 6. 논헤드 삭제
    cout << "non-head: " << head2->get_link()->get_link()->get_link()->get_link()->get_data() << endl;
    remove_nonhead(head2->get_link()->get_link()->get_link()); // 지우고자 하는 것 앞의 노드 줘야 함
    cout << "non-head deleted: " << head2->get_link()->get_link()->get_link()->get_link()->get_data() << endl << endl;

    // Program 7. 검색
    cout << "location of " << head2->get_link()->get_link()->get_link()->get_link()->get_data() << " : " <<  head2->get_link()->get_link()->get_link()->get_link() << endl;
    cout << "search 4 : " << list_search(head2, 4) << endl << endl;

    return 0;
}