#include <iostream>
#include <vector>
#include <queue>
#define INF 987654321

using namespace std;

int N, M;
vector<int> dist(N, INF);
vector<pair<int, int>> adj[501];

void dijkstra(int start) {
	priority_queue<pair<int, int>> pq;
	pq.push(make_pair(0, start));

	dist[start] = 0;

	while (!pq.empty()) {
		int now = pq.top().second;
		int cost = -pq.top().first;
		pq.pop();

		if (dist[now] < cost) continue;

		for (int i = 0; i < adj[now].size(); i++) {
			int next = adj[now][i].second;
			int n_dist = adj[now][i].first + cost;

			if (dist[next] > n_dist) {
				dist[next] = n_dist;
				pq.push(make_pair(-n_dist, next));
			}
		}
	}
}


int main(void) {


	return 0;
}
