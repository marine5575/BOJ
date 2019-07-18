#include <iostream>
#include <vector>	// vector, pair
#include <queue>	// priority queue
#include <cstdio>
#define INF 987654321

using namespace std;

vector<pair<int, int>> adj[20001];	// 인접 노드와 그에 해당하는 가중치

vector<int> dijkstra(int start, int vertax) {
	priority_queue<pair<int, int>> pq;	// 최솟값 뽑아내는 우선순위 큐

	vector<int> dist(vertax, INF);	// 결과 거리 저장
	dist[start] = 0;	// 시작 노드의 거리 초기화

	pq.push(make_pair(0, start));	// 처음부터 죽으면 안되니까

	while (!pq.empty()) {
		int cost = -pq.top().first;	// 최대 힙이라서 마이너스로 정렬한거 뒤집어 줌
		int now = pq.top().second;	// 현재 위치
		pq.pop();

		if (dist[now] < cost) continue;	// 현재 값이 최선이라서 업데이트 필요하지 않음

		// 인접한 모든 애들 조사
		for (int i = 0; i < adj[now].size(); i++) {
			int n_dist = adj[now][i].first + cost;	// 새로 계산한 옆집 거리
			int next = adj[now][i].second;	// 옆집 놈

			// 새로 계산한 값보다 원래 들어있던 값이 크면 업데이트
			if (n_dist < dist[next]) {
				dist[next] = n_dist;
				pq.push(make_pair(-n_dist, next));	// 최대 힙이어서 가중치에 (-) 붙여줌
			}
		}
	}

	return dist;
}


int main(void) {
	int V, E;	// 노드 수, 간선 수

	scanf("%d %d", &V, &E);

	int start;	// 시작 노드

	scanf("%d", &start);
	start--;	// 난 0부터 시작하길 원해

	for (int i = 0; i < E; i++) {
		int from, to, w;	// from에서 to로 향할 때 w가 걸림
		scanf("%d %d %d", &from, &to, &w);
		from--; to--;	// 0부터 시작합시다

		adj[from].push_back(make_pair(w, to));	// 인접행렬에 넣어줌
	}

	vector<int> dist = dijkstra(start, V);	// 최종 최소 거리 저장

	for (int i = 0; i < dist.size(); i++) {
		int a = dist[i];	// i에서의 최소값

		if (a != INF) printf("%d\n", dist[i]);	// 무한일 경우
		else printf("INF\n", dist[i]);
	}

	return 0;
}
