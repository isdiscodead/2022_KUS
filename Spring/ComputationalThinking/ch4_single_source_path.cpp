#include <iostream>
using namespace std;

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

typedef struct {
    int weight; // 가중치 ( 비용 )
    int v1; 
    int v2;
} edge;

#define N 5 // size
#define INF 1000000000 // 거리가 무한인 경우 

// pseudo code 기반 구현 
// https://nolzaheo.tistory.com/17
void dijkstra( int n, const int w[][N+1], edge* F, int &f_index) { // w = 그래프 정보 , F = edge 정보
    int vnear; // 최근 방문한 가장 가까운 정점 
    edge e;

    int touch[N+1]; // source -> vi까지 경로에서 마지막에 touch한 정점 인덱스 
    int length[N+1]; // source -> vi까지의 최단 거리 저장

    for ( int i=2 ; i<=n ; i++ ) { // 자기 자신(1행), 첫행첫열(0) 제외 
        touch[i] = 1; // 우선 경유지 없으므로 가장 마지막 touch는 v1
        length[i] = w[1][i]; // 자기 자신 -> vi까지의 그래프 정보 
    }

    while ( true ) {
        int min = INF;  // 처음엔 최솟값 INF로 두기

        for ( int i=2; i<=n ; i++ ) {
            if ( 0<=length[i] && length[i] <= min ) {
                // 그래프 기반으로 가장 가까운 vertex 선택, vnear로 설정하여 방문 
                min = length[i];
                vnear = i;
            }
        }

        // 첫 번째 경로는 위에서 찾은 최단 경로로 고정 ... 
        e.v1 = touch[vnear];
        e.v2 = vnear;

        F[++f_index] = e; // i번째에 edge 정보 저장 ( 현재 최단 경로 )
    
        for ( int i=2 ; i<=n ; i++ ) { // 자기 자신 제외하고 다시 전체 탐색하여 업데이트   
            // vnear를 경유지로 하여 vi까지 가는 더 짧은 경로가 있다면 ... 
            if ( length[vnear] + w[vnear][i] < length[i] ) {
                length[i] = length[vnear] + w[vnear][i];
                touch[i] = vnear;
            }
        }

        length[vnear] = -1; // 이미 방문한 vertex이므로 더이상 거리 따질 일 X 
        // 가까운 vertex로 다시 선택되지 않도록 ... 
 
        if ( f_index == n-1 ) { // 5개의 정점 모두 방문했다면 
            break;
        }
    }
}
 

int main( void ) {
    // 각 행 -> 열 vertex로 가는 비용 
    int W[N+1][N+1] = {
        {0, 0, 0, 0, 0, 0},
        {0, 0, 7, 4, 6, 1},
        {0, INF, 0, INF, INF, INF},
        {0, INF, 2, 0, 5, INF},
        {0, INF, 3, INF, 0, INF},
        {0, INF, INF, INF, 1, 0},
    };

    edge F[N];
    int f_index = -1;

    dijkstra(N, W, F, f_index);

    for ( int i=0 ; i<f_index ; i++ ) {
        cout << F[i].v1 << " - " << F[i].v2 << endl;
    }

    return 0;
}