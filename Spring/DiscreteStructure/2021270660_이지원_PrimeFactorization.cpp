#include <iostream>
#include <math.h>

using namespace std;

int is_prime(int n) {
    for ( int i=2 ; i < ceil(sqrt(n)) ; i++ ) {
        if ( n % i == 0 ) {
            return i;
        }
    }
    return 0; // 소수인 경우 0 반환 
}


void prime_factorization(int n) {
    cout << n << " = ";
    int i = 2;

    while ( i<=n ) {
        if ( !is_prime(i) && n%i==0 ) {
            cout << i;
            n /= i;
            if ( n != 1 ) {
                cout << " * ";
            } else {
                break;
            }
        } else {
            i++;
        }
    } 
    
    cout << "\n\n";
}


int main(void) {
    cout << "===== Prime Factorization =====" << "\n\n";

    int n;
    
    while ( true ) {
        cout << "정수 입력(종료: 1 이하 입력 ): ";
        cin >> n;
        if ( n <= 1 ) {
            cout << "프로그램을 종료합니다.\n";
            break;
        }
        prime_factorization(n);
    }

    return 0;
}