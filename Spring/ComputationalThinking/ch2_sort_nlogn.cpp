 #include <iostream>
 using namespace std;

// [ merge sort ] O(n log n)
// input : arr, n
// output : arr 
// 추가 메모리 ( 왼쪽 U[], 오른쪽 V[] ) 사용하여 size 1까지 쪼개기
// 사이즈가 1이 되었다면 작은 리스트부터 합쳐서 원본 리스트에 담기 
// U[i]와 V[i] 비교해서 작은 애들부터 왼쪽에 넣기
// 하나가 끝까지 갔으면 나머지 배열 쭈르륵 넣기 

void merge( int* arr, int* U, int* V, int n, int h, int m );

void merge_sort(int* arr, int n) {
    // 3way로 구현할 경우 mid1 = n/3, mid2 = n - mid1
    // mid1 / mid2-mid2 / n-mid2로 나눠서 진행 
    // 합병 시에는 이중 if문 사용해서 모든 케이스 비교 ...
    int h = n/2;
    int m = n-h;

    int* U = new int[h];
    int* V = new int[m];

    if ( n > 1 ) {
        // copy arr -> O(n)
        for ( int i=0 ; i < h ; i++ ) {
            U[i] = arr[i];
        }

        for ( int i=0 ; i < m ; i++ ) {
            V[i] = arr[h+i];
        }

        // 더 작게 분할
        merge_sort(U, h);
        merge_sort(V, m);

        // 분할 후에 합치기 
        // 여기가 실행되는 시점 -> 하위 배열이 합쳐진 뒤
        merge(arr, U, V, n, h, m);
    }
}

// 합병
void merge( int* arr, int* U, int* V, int n, int h, int m ) {
    int i=0, k=0, l=0; // arr, U, V의 위치 인덱스 

    while ( k<h && l<m ) { // 각자 크기만큼 
        // 더 작은 애를 원본 배열에 ...
        if ( U[k] > V[l] ) {
            arr[i++] = V[l++]; 
        } else {
            arr[i++] = U[k++]; 
        }
    }

    while ( l<m ) { // V 원소 모두 소모하기
        arr[i++] = V[l++];
    }

    while ( k<h ){ // U 원소 모두 소모하기 
        arr[i++] = U[k++];
    } 
}



// [ quick sort ] O(n log n)
// input : arr, low, high ( idx )
// output : arr 
// pivot( 첫번째, 중간값, 무작위... 등등 )을 기준으로 작은 애들은 왼쪽에, 큰 애들은 오른쪽에 ... 
// 1. 첫번째 값을 pivot으로, 처음 ~ 끝까지 탐색해서 pivot보다 작은 애들은 왼쪽으로 밀기 
// 2. for문 종료 후 pivot보다 작은 애들 중에 가장 뒤가 pivot의 새 위치 
// 3. 기존 pivot을 새 위치로 변경 ... 

void partition(int* arr, int low, int high, int& pivot);

void quick_sort(int* arr, int low, int high) {
    int pivot; // 재귀 호출 시마다 변경될 pivot 위치  

    if ( high > low ) { // high == low면 크기가 1이므로 재귀호출 종료 ! 
        // pivot 기준 정렬
        partition(arr, low, high, pivot);

        // pivot 제외 하위 배열 재귀호출
        quick_sort(arr, low, pivot-1);
        quick_sort(arr, pivot+1, high);
    }
}

// 정렬 
void partition(int* arr, int low, int high, int& pivot) {

    int i, j, tmp;
    int pivot_item = arr[low]; // 하위 배열의 첫 번째 값을 pivot 아이템으로 
    j = low; // 따라서 바뀔 pivot 위치는 처음부터 시작 ! 

    for ( i=low+1 ; i<=high ; i++ ) { // i는 방문 인덱스 -> 맨 끝까지 뒤져야 함 ...
        if ( arr[i] < pivot_item ) { // pivot item보다 작은 값은 뒤로 ...
            j++; // pivot 위치가 될 j++하여 자리 만들기 
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
        }
    }

    // 새 pivot 위치로 지정 
    pivot = j;

    // 맨 앞의 값과 Pivot 값 위치 변경 
    tmp = arr[low];
    arr[low] = arr[pivot];
    arr[pivot] = tmp;
}


int main(void) {
    int nums[10] = {2, 312, 4, 13, 21, 305, 301, -2, 31, 0};
    int* arr = nums;

    // merge_sort(arr, 10);
    quick_sort(arr, 0, 9);
    cout << "sorted : ";
    for ( int i=0 ; i<10 ; i++ ) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
 }