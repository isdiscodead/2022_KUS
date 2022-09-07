#include <iostream>
using namespace std;
#include <iomanip> // setw() 사용을 위함 
#include <string> // stoi() 사용을 위함 

// 운영체제 프로그래밍 과제 1 : 구구단 테이블 
// 2021270660 이지원

// 원하는 단은 실행 시 argument로 전달 ( 해당 디렉토리로 가서 cmd로 실행 )
// 기본적으로 한 블록에 5개의 단 출력
// dan 수만큼의 세로 길이를 가지게 됨 

int main(int argc, char** argv) {
    cout.setf(ios::left); // setw 왼쪽 정렬 
    
    int max = stoi(argv[1]); // 매개변수 받아오기 -> int로 변환 
    int line = 0;
    int cnt = 1;
    int i, j;

    for ( j=1 ; j<=line+5 ; j++ ) { // 행 바꿈 

        if ( line>max ) return 0;
		
        for ( i=line+1 ; i<=max ; i++ ) { // 열 바꿈 
            if ( i>=j && cnt<=5 ) { // 단을 넘어가지 않는 한에서 5줄 출력  
                cout << i << " x " << setw(3) << j << " = " << setw(8) << j * i;

            } else if ( cnt <= 5 ) { // 단을 넘어갈 경우 출력 생략 
                cout << "                  ";
            }
            cnt++; // 한 행 출력 완료 
        }

        cout << endl;
        cnt=1; // 다음 행 출력을 위한 초기화 

        // 하나의 블록에 5개의 단까지만 출력되도록 처리 
        if ( j == line + 5 ) { // j가 끝까지 갔으면 다섯번째 단의 끝까지 출력 완료 !
            line += 5;
            cout << "\n\n";
            j = 0;
        }
    }
}