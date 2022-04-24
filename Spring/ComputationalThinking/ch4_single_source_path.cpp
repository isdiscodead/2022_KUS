#include <iostream>
using namespace std;

#include <vector>
#include <queue>

// vertex = node
// edge = 연결 다리 ( relation ) -> n ~ n^2개 


// < Triangle Inequality > ; 삼각 부등식, 임의의 두 변의 합 >= 하나의 변
// v1 - v3 간의 거리 Infinite
// vi - v2 - v3 거쳐갈 수 있는 경우 
// delta() -> 반복문 종료 시 최단 거리 
// w() -> 입력 그래프 상의 거리
// delta(v1, v3) <= delta(v1, v2) + w(v2, v3)


// [ Dijkstra's Algorithm for Shortest Path ]
// 특정한 하나의 정점에서 다른 모든 정점까지의 최단 경로 탐색 
// 방문한 vertex, 미방문 vertex로 나누어 방문한 vertex의 최단 경로는 경유지로 사용
// 만약 경유지 사용 시 더 짧다면 update !!  

// 1. 출발 노드 ( source ) 설정
// 2. source 기준으로 각 노드의 최소 비용 저장
// 3. 방문하지 않은 노드 중에서 가장 비용이 적은 노드 선택
// 4. 해당 노드를 거쳐서 특정한 노드로 가는 경우를 확인, 최소 비용 갱신
// 5. 3~4번 과정 반복 

int n = 6; // size
int INF = 1000000000; // 거리가 무한인 경우 

// 각 행 -> 열 vertex로 가는 비용 
int a[6][6] = {
    {0, 2, 5, 1, INF, INF},
    {2, 0, 3, 2, INF, INF},
    {5, 3, 0, 3, 1, 5},
    {1, 2, 3, 0, 1, INF},
    {INF, INF, 1, 1, 0, 2},
    {INF, INF, 5, INF, 2, 0}
};

bool v[6]; // vertex의 visited 여부 
int d[6]; // source에서 각 vertex까지의 최단 거리 

// 가장 최소 거리를 가지는 정점 반환
// 선형으로 구현 
int getSmallIndex() {
    int min = INF;
    int index = 0;
    for ( int i=0 ; i<n ; i++ ) {
        // i번째 vertex로 가는 distance가 min보다 짧고, 아직 i번째 방문 X 
        if ( d[i] < min && !v[i] ) {
            min = d[i];
            index = i;
        }
    }
    return index;
}

// 다익스트라를 수행하는 함수 ( 선형 구현 )
void dijkstra_linear(int source) {
    for ( int i=0 ; i<n ; i++ ) {
        d[i] = a[source][i]; // 현재 그래프 상의 최단 거리 저장 
    }

    v[source] = true; // 자기 자신은 방문한 vertex

    for ( int i=0 ; i<n-2 ; i++ ) { // 자기 자신과 맨 마지막에 남는 Node 제외 
        int vnear = getSmallIndex(); // source에서 가장 짧은 distance 
        v[vnear] = true;
        
        for ( int j=0 ; j<n ; j++ ) {
            if ( !v[j] ) {  // 아직 방문하지 않은 j번째 노드로 가는 길 update 
                // 경유지 vnear를 거쳐서 j로 가는 게 더 짧다면 ... 
                if ( d[vnear] + a[vnear][j] < d[j] ) { 
                    d[j] = d[vnear] + a[vnear][j];
                } 
            }
        }
    }
}


// pseudo code 기반 구현 
void dijkstra( int n, const int w[][6], int* &F ) { // w =  , F = 

}
 

int main( void ) {
    // dijkstra_linear(0);
    for ( int i=0 ; i<n ; i++ ) {
        cout << d[i] << " ";
    }
}