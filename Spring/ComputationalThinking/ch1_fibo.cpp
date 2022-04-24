#include <iostream>
using namespace std;


// fibonacco sequence 
// input : n
// output : n번째 피보나치 수열 
// 재귀호출 이용
int recursive_fibo(int n) {
    if ( n < 2 ) {
        return n;
    } else {
        return recursive_fibo(n-1) + recursive_fibo(n-2); // 전항 + 전전항 return 
    }
}

// fibonacco sequence 
// input : n
// output : n번째 피보나치 수열 
// 추가 메모리 캐시 이용   용   
int iterative_fibo(int n) {
    int i=0;
    int* fibo = new int[n+1]; // 0~n까지이므로 총 n+1개 배열 필요 
    fibo[0] = 0;

    if ( n > 0 ) {
        fibo[1] = 1;
        
        for ( i=2 ; i<=n ; i++ ) {
            fibo[i] = fibo[i-1] + fibo[i-2];
        }
    }

    return fibo[n];

}

int main(void) {

    cout << "재귀 - 10번째 피보나치 수 : " << recursive_fibo(10) << endl;
    cout << "캐시 - 10번째 피보나치 수 : " << iterative_fibo(10) << endl;

    return 0;
}