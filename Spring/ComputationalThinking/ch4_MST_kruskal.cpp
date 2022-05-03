#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define MAX 5
#define INF 9999

// [ Kruskal MST ]
// 출발지 개념 아예 X, 각각의 정점에서의 최소 비용을 찾음
// cycle이 생기지 않도록 check하는 과정 필요

// 속한 집합 찾기
int getSet(int set[], int x) {
	if (set[x] == x) return x;
	return set[x] = getSet(set, set[x]);
}

// 두 집합 합치기
void unionSet(int set[], int a, int b) {
	a = getSet(set, a);
	b = getSet(set, b);
	if (a < b)
		set[b] = a;
	else
		set[a] = b;
}

// 동일한 집합 내에 속해있는지 확인
int find(int set[], int a, int b) {
	a = getSet(set, a);
	b = getSet(set, b);
	return a == b;
}

// 간선 정보 클래스
class Edge {
public:
	int vtx[2]; // 연결된 2개의 정점
	int distance; // 거리(비용)

	Edge(int a, int b, int distance) {
		this->vtx[0] = a;
		this->vtx[1] = b;
		this->distance = distance;
	}
    
	bool operator <(Edge& edge) {
		return this->distance < edge.distance; // 적은 거리 우선 정렬
	}
};
int main() {
	int v = 9; // 정점 수 (0~8)

	vector<Edge> data; // 간선 데이터 배열
	data.push_back(Edge(0, 1, 8)); // 정점0과 정점1의 간선 비용8
	data.push_back(Edge(0, 2, 12));
	data.push_back(Edge(1, 2, 13));
	data.push_back(Edge(1, 3, 25));
	data.push_back(Edge(1, 4, 9));
	data.push_back(Edge(2, 3, 14));
	data.push_back(Edge(2, 6, 21));
	data.push_back(Edge(3, 4, 20));
	data.push_back(Edge(3, 5, 8));
	data.push_back(Edge(3, 6, 12));
	data.push_back(Edge(3, 7, 12));
	data.push_back(Edge(3, 8, 16));
	data.push_back(Edge(4, 5, 19));
	data.push_back(Edge(5, 7, 11));
	data.push_back(Edge(6, 8, 11));
	data.push_back(Edge(7, 8, 9));

	// 간선 비용을 기준으로 정렬
	sort(data.begin(), data.end());

	int set[9];
	for (int i = 0; i < v; i++) {
		set[i] = i;
	}
	int sum = 0; // 최소 비용 합

	for (int i = 0; i < data.size(); i++) {
		// 사이클이 발생하지 않으면 그래프에 포함
		if (!find(set, data[i].vtx[0], data[i].vtx[1])) {
			sum += data[i].distance;
			unionSet(set, data[i].vtx[0], data[i].vtx[1]);
		}
	}
	cout << sum;
}