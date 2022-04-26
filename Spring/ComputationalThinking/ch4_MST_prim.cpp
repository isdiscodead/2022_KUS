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
    int* distance = new int[n];

    // nearest, distance 초기화
    for ( i=2 ; i<n ; i++ ) {
        nearest[i] = 1; // v1로 초기화 
        distance[i] = W[1][i]; // v1 ~ vi 거리 
    }

    // 각 정점에서 가까운 거리 찾기 
    for ( i=2 ; i<=n ; i++ ) { // repeat n-1 times
        min = INF;

        for ( j=1 ; j<n ; j++ ) {

        }
    }
}