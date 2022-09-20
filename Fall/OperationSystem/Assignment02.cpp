#include <iostream>

// EnumProcesses()를 사용하기 위한 헤더 파일, 라이브러리 링크 
#include <psapi.h>
#pragma comment( lib, "Psapi.lib" ) // #pragma comment(lib, "라이브러리.lib") -> 명시적 라이브러리 링크

// GetSystem() -> UTC 기준... 따라서 GetLocalTime()을 사용해 시간을 가져옴
#include <windows.h>

// 현재 시간을 출력하는 함수 
void printTime() {

}

// 현재 프로세스 수를 반환하는 함수
int getProcessNum() {
   return 0;
}

int main(void) {


   return 0;
}