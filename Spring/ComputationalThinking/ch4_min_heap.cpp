#include <iostream>
using namespace std;



// [ Huffman Code ]
// 1. Min Heap또는 Priority Queue 사용하여 frequency 낮은 애들 두 개 합성 노드로 만들기 
// 2. 다시 Tree에 합성 노드 집어넣고 비교 ... 무한 반복 
// 3. n-1번 for문 돌고 종료되면 n개의 노드 다 합쳐짐 -> root만 남음 ! 
/*
for (i=1 ; i<=n-1 ; i++ ) {
    p = delete_min( priority_queue );
    q = delete_min( priority_queue );

    r = new nodetype;
    r.left = p;
    r.right = q;
    r.frequency = p.frequency + q.frequency;
    insert( priority_queue, r ); // 합성 노드를 큐에 추가 
}

r = delete_min(PQ); // 완성된 oot node 
return r;
*/



// min_heap 구현 코드 
class MinHeap {
private:
    int size;
    int* a;

    void heapify(int position) {
        int l = 2 * position + 1; // left child의 position
        int r = l+1; // right child의 position
        int i = position; // 유효성 검증할 position ( parent )

        if ( l < size && a[l] < a[i]) { // size 넘지 않는다면 + parent 노드가 더 작다면
            i = l;  // 왼쪽 자식의 자리 담아두기 
        } else if ( r < size && a[r] < a[i] ) {// size 넘지 않는다면 + parent 노드가 더 작다면
            i = r;  // 오른쪽 자식의 자리 담아두기 
        }

        if ( i != position ) { // 현재 position의 위치 바뀌어야 한다면 
            swap(a[i], a[position]);
            heapify(i); // 바뀐 자리에서 다시 검증 -> 재귀 호출 
        }
    }

public: 
    MinHeap() {
        size = 0;
    }

    int top() {
        return a[0];
    }

    void pop() {
        a[0] = a[--size]; // 맨 마지막 노드를 헤드로 옮기기 
        heapify(0); // 새로 root 바뀔 때 검증하는 method 
    }

    void push( int data ) {
        a[size] = data;
        for ( int i=size++ ; i ; ) { // 최하위에 추가했으므로 아래서부터 확인 
            int position = (i-1) >> 1; // (i-1)/2 -> parent node 위치
            if ( a[position] < a[i] ) break;   // parent가 더 작으면 냅두기 
            swap(a[position], a[i]);    // parent가 더 큰 경우, 바꿔주기
            i = position;   // 바뀌었을 때만 i 변경 
        }
    }

};