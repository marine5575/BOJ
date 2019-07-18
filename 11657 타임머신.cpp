#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>
#define INF 987654321

using namespace std;

int N, M;	// 도시, 버스 노선
vector<pair<int, int>> adj[501];	// 인접 노드와 그에 해당하는 가중치
vector<int> dist(501, INF);	// 떨어진 거리

int belmanFord(int nLoop) {
	int isUpdate = 0;	// 바뀌었나?

	// 모든 노드에 대해서 수행
	for (int i = 0; i < N; i++) {
		// 모든 간선에 대해서 수행
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < adj[j].size(); k++) {
				int new_dist = dist[j] + adj[j][k].first;	// 새로 구한 거리
				int old_dist = dist[adj[j][k].second];	// 예전 거리

				// 방문한 적이 있고 새로운 거리가 더 짧을 때
				if ((dist[j] != INF) && (new_dist < old_dist)) {
					isUpdate = 1;

					if (isUpdate * nLoop) return isUpdate;	// 2회차에는 바로 빠져나감
					dist[adj[j][k].second] = new_dist;	// 값 갱신해줌
				}
			}
		}
	}

	return isUpdate;
}


int main(void) {
	scanf("%d %d", &N, &M);

	for (int i = 0; i < M; i++) {
		int from, to, w;	// from에서 to로 가중치 w를 가지고

		scanf("%d %d %d", &from, &to, &w);
		from--; to--;	// 0부터 시작할 것임

		adj[from].push_back(make_pair(w, to));
	}

	dist[0] = 0;	// 초기 노드만 0으로

	belmanFord(0);

	if (belmanFord(1) == 1) printf("-1\n");	// 2회차 도는 중에 업데이트 되면 음의 사이클 존재
	else {
		for (int i = 1; i < N; i++) {
			if (dist[i] == INF) printf("-1\n");
			else printf("%d\n", dist[i]);
		}
	}

	return 0;
}
