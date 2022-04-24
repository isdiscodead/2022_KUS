#include <iostream>
using namespace std;

// [ sequential search ] O(n)
// input : 배열, 사이즈, 검색 값
// output : index
// 처음부터 끝까지 순차적으로 하나하나 탐색 -> 중도 return 가능 
int seq_search(int n, int arr[], int x) {
    for ( int i=0 ; i<n ; i++ ) {
        if ( x == arr[i] ) {
            return i;
        }
    }
    return -1;
}

// [ binary search ] O(log n)
// input : 배열, 사이즈, 검색 값
// output : index 
// 가운데 탐색 후 비교하여 왼쪽 / 오른쪽만 탐색 -> 중도 return 가능 
int bin_search(int n, int arr[], int x) {
    int low, high, mid; // index low, high, mid 사용
    low = 0;
    high = n-1;

    while ( low <= high ) {
        mid = (low+high) / 2;
        if ( x == arr[mid] ) {
            return mid;
        } else if ( x > arr[mid] ) { // 찾는 값보다 현재 탐색 값이 작으면 오른쪽에서 탐색 
            low = mid+1;
        } else {
            high = mid-1;
        }
    }
    return -1;
}


int main( void ) {
    int arr[] = {-32, -5, 0, 3, 5, 6, 12, 23, 43, 68, 100, 111};
    
    cout << "seq : " << seq_search( sizeof(arr)/sizeof(arr[0]), arr, 12 ) << endl;
    cout << "bin : " << bin_search( sizeof(arr)/sizeof(arr[0]), arr, 12 ) << endl;

    return 0;
}