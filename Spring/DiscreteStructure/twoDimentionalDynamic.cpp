#include <iostream>
using namespace std;

int main(void) {
    
    // 2차원 배열의 동적 할당을 위해서는 더블포인터 사용 ( 포인터 배열의 주소 )
    int row = 10;
    int col = 10;

    int** arr = new int*[row];

    for ( int i=0 ; i<row ; i++ ) {
        arr[i] = new int[col];
    }

    // 해제 시에도 동일한 방식으로 ... 반대로 !!
    for ( int i=0 ; i<row ; i++ ) {
        delete[] arr[i];
    }

    delete[] arr;

    return 0;
}