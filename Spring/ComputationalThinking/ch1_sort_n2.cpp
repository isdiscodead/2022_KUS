#include <iostream>
using namespace std;

// [ exchange_sort ]
// input : arr, n
// output : arr
// 반복문 돌면서 안쪽 반복문에서 i와 j 비교하여 swap 
// j, j+1을 비교하는 bubble sort와는 다른 방법 !
// 뒷부분은 이미 정렬되었으므로 j=i+1 시작
void exchange_sort( int* arr, int n ) {
    for ( int i=0 ; i<n ; i++ ) {
        for ( int j=i+1 ; j<n ; j++ ) {
            if ( arr[i] > arr[j] ) {
                int tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }
}


// [ selection sort ]
// input : arr, n
// output : arr
// min_idx사용하여 바깥 for문마다 변경, 앞부분은 이미 정렬되었으므로 j=i+1 시작
void select_sort( int* arr, int n ) {
    for ( int i=0 ; i<n ; i++ ) {
        int min_idx = i;
        for ( int j=i+1 ; j<n ; j++ ) {
            if ( arr[min_idx] > arr[j] ) {
                min_idx = j;
            }
        }
        int tmp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = tmp;
    }
} 


// [ insertion sort ]
// input : arr, n
// output : arr
// 새로 삽입할 i번째 값을 x로 두고 for문 돌리면서 하나씩 미뤄서 끼워넣기
// i-1부터 탐색하므로 값을 덮어써도 사라지는 값 없이 되는 것 !! 
void insert_sort(int* arr, int n) {
    for ( int i=1 ; i<n ; i++ ) {
        int x = arr[i];
        int j;
        for ( j=i-1; j>=0 ; j-- ) { // 정렬된 list 중 맨 뒤부터 역순으로 조사 (  )
            if ( arr[j] > x ) {
                // x 보다 크면 뒤로 미루기
                arr[j+1] = arr[j];
            } else {
                break;
            }
        }
        // 위치 찾았으면 마지막 j 위치에 삽입 ( 마지막에 --하고 끝나므로 +1 )
        arr[j+1] = x;
    }
}

int main(void) {
    int nums[10] = {2, 312, 4, 13, 21, 305, 301, -2, 31, 0};
    int* arr = nums;

    insert_sort(arr, 10);
    cout << "sorted : ";
    for ( int i=0 ; i<10 ; i++ ) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}