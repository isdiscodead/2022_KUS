#include <iostream>
using namespace std;

// MST ( Minimum Spanning Tree ) : cycle없이 최소의 edge로 연결된 그래프 

// [ Prim's Algorithm ]
// 한 점에서 시작하여 각각의 vertex에서 가장 가까운 경로 선택
// 출발지 - 도착지 개념이 없으므로 경유지도 존재 X
// 방문한 vertex의 집합 = 전체 vertex 집합이 되면 종료 

#define INF 9999
#define SIZE 5

struct edge {
    int v1;
    int v2;
};


void prim( int n, const int W[][SIZE], edge* F ) {
    int vnear; // 최근 방문 vertex의 인덱스 
    int min;
    int i, j;
    int f_size = 0; // F의 index position 

    // vi에서 가장 가까운 노드의 index
    int* nearest = new int[n+1]; // 0, 1 인덱스는 사용 X ( 0은 무시, 1은 출발지인 v1 )

    // vi에서 가장 가까운 노드까지의 비용 
    int* distance = new int[n+1];

    // nearest, distance 초기화
    for ( i=2 ; i<=n ; i++ ) {
        nearest[i] = 1; // v1로 초기화 
        distance[i] = W[0][i-1]; // v1 ~ vi 거리 
    }

    // 각 정점 i에서 가까운 거리 찾기 
    for ( i=0 ; i<n ; i++ ) { // repeat n-1 times
        min = INF;

        for ( j=2 ; j<=n ; j++ ) {
            if ( distance[j] < min && distance[j] >= 0 ) { // 그래프 상에서 짧은 경로 발견 시 
                min = distance[j];
                vnear = j;
            }
        }

        // 추가할 경로 저장 
        edge new_edge;
        new_edge.v1 = vnear;
        new_edge.v2 = nearest[vnear];

        F[f_size] = new_edge;
        f_size++;

        distance[vnear] = -1; // 이미 방문한 곳은 다시 탐색하지 않도록 ... 

        // 현재 선택한 경유지 사용하여 갈 수 있는 빠른 길이 있다면 update
        for ( j=2; j<=n ; j++ ) {
            if ( W[j-1][vnear-1] < distance[j] ) {
                distance[j] = W[j-1][vnear-1];
                nearest[j] = vnear;
            }
        }
    }
}

int main() {
    int weigth_matrix[SIZE][SIZE] = {
        { 0, 1, 3, INF, INF },
        { 1, 0, 3, 6, INF },
        { 3, 3, 0, 4, 2 },
        { INF, 6, 4, 0, 5},
        { INF, INF, 2, 5, 0 }
    };

    // MST's maximum edge number is n-1
    edge* F = new edge[SIZE-1];

    prim(SIZE, weigth_matrix, F);

    int i;
    for ( i=0; i < SIZE-1 ; i++ ) {
        cout << F[i].v1 << ", " << F[i].v2 << endl;
    }
}