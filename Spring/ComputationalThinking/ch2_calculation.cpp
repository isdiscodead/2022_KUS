#include <iostream>
using namespace std;

// [ Strassen Matrix Multiple ] 
// 다 쪼개졌을 경우엔 C = A*B ( 그냥 곱하면 끝 )
// 매트릭스를 1x1 행렬이 될 때까지 4개로 쪼개기 ... 
// m1 ~ m7을 strassen 공식으로 구하기, n/2*n/2 행렬이 됨
// 그리고 마지막이 되어서 C 구하기 ... 
void strassen(int n, int** A, int** B, int** C) {
    if ( n < 2 ) {
        // compute C = A * B 
    } else {
        // partition A into 4 submatrices a11, a12, a21, a22
        // partition B into 4 submatrices b11, b12, b21, b22

        // matrix m1, m2, m3, m4, m5, m6, m7;

        // strassen( n/2, a11+a12, b11+b22, m1); 
        // ...
        
        // c11 = m1 + m4 - m5 + m7 -> 최종적으로는 n/2 사이즈 배열들이 됨, c들 모두 합치면 n
        // ...
    }
}


#define THRESHOLD 5;
// [ Arithmetic with Large Integers ]
// 큰 자릿수의 숫자를 digit 절반씩 나누어 계산하고 더하기

// u = x * 10^m + y
// u -> n digits
// m -> ceiling(n/2)
// y -> floor(n/2)

// v = w * 10^m +z
// u*v = xw * 10^2m + ( xz + wy ) * 10^m + yz
// 4개의 항( sub problem )으로 이루어짐 !! 
long int prod( long int u, long int v ) {
    long int x, y, w, z;
    int n, m; // digits 

    // n = max digits of u and v

    if ( u==0 || v==0 ) {
        return 0;

    } else if ( n <= 5 ) { // 적당히 풀 정도가 되면 ...
        return u*v;

    } else {
        m = n/2;
        // x = u / 10^m;
        // y = u % 10^m;
        // w = v / 10^m;
        // z = v % 10^m;

        // return prod(x, w) * 10^2m + ( prod(x,z) + prod(w, y) ) * 10^m + prod(y,z);
    }
}