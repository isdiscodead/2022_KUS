#include <iostream>
#include <iomanip> // setw() 사용을 위함 
using namespace std;

// 운영체제 프로그래밍 과제 1 : 구구단 테이블 
// 2021270660 이지원

// 원하는 단은 실행 시 argument로 전달 ( 해당 디렉토리로 가서 cmd로 실행 )
// 기본적으로 한 블록에 5개의 단 출력 ... -> 한 행에 5개 출력, cnt로 체크 
// line 수만큼의 세로 길이를 가지게 됨 

int main(void) {
	cout.setf(ios::left); // setw 왼쪽 정렬 

    int i, j;
	int max = 12;
	int line = 1; 
	int cnt = 1; 

	for ( line=0 ; line<=max ; line+=5  ){ 

		for ( j=1 ; j<=line+5 ; j++ ) { // 행 바꿈 
		
			for ( i=line+1 ; i<=max ; i++ ) { // 열 바꿈 
				if ( i>=j && cnt<=5 ) { // 단을 넘어가지 않는 한에서 5줄 출력  
					cout << i << " x " << setw(3) << j << " = " << setw(8) << j * i;

				} else if ( cnt <= 5 ) { // 단을 넘어갈 경우 출력 생략 
					cout << "                  ";
				}
				cnt++; // 한 행 출력 완료 
			}

            printf("\n");
            cnt=1; // 다음 행 출력을 위한 초기화 
		}

		printf("\n\n");	// block 구분 
	}
	
	return 0;
}