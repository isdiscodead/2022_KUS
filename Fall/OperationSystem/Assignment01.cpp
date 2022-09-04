#include <iostream>
using namespace std;

// 운영체제 프로그래밍 과제 1 : 구구단 테이블 
// 2021270660 이지원

// 원하는 단은 실행 시 argument로 전달 ( 해당 디렉토리로 가서 cmd로 실행 )
// 기본적으로 한 블록에 5개의 단 출력
// dan 수만큼의 세로 길이를 가지게 됨 

int main(void) {
    // 블록 변경을 위한 block 변수
    int max = 12;
    int mul = 0;
    int dan = 1;
    int line = 1;
    
    for ( int i=1 ; dan < max ; i++ ) {
        for ( int j=1 ; j <= 5 ; j++ ) {
            // 단 수보다 더 높은 수와의 곱셈은 생략 
            if ( j + mul < i ) {
                cout << "\t\t\t\t";
                continue;
            } 

            // 출력 
            cout << j + mul << " x " << i << " = " << (j + mul) * i << "\t\t";
        }

        cout << endl;

        // 하나의 블록에 5개의 단까지만 출력되도록 처리 
        if ( i == mul + 5 ) {
            line += 5;
            mul += 5;
            cout << "\n\n";
            i = 1;
        }

        // dan 증가 처리 
        if ( dan < mul + 5 ) {
            dan ++;
        }
    }
}