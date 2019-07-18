#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>
#define INF 987654321

using namespace std;
typedef pair<int, int> pii;

priority_queue<int> dist[1001];	// k번째까지 거리 저장 (최대 힙) 
vector<pii> adj[1001];	// 인접 노드 

int k;	// k번째 최단 거리 구해야 됨 

void dijkstra(int start) {
	priority_queue<pii, vector<pii>, greater<>> pq;	// 최솟값 비교를 위한 우선순위 큐 (최소 힙) 
	pq.push(make_pair(0, start));	// 처음부터 종료 막기 
	dist[start].push(0);	// 시작 노드의 최단 거리 
	
	while(!pq.empty()) {
		int now = pq.top().second;	// 현재 위치 
		int cost = pq.top().first;	// 현재 가중치 
		pq.pop(); 
		
		// 인접 노드 모두 살펴봄 
		for(int i = 0; i < adj[now].size(); i++) {
			int next = adj[now][i].second;	// 다음 위치 
			int n_dist = adj[now][i].first + cost;	// 다음 거리 후보 
			
			// dist는 최대힙이므로
			// dist의 크기가 k 이하라면 먼저 마구잡이로 넣음 
			if(dist[next].size() < k) {
				dist[next].push(n_dist);
				pq.push(make_pair(n_dist, next));
			}
			// dist가 딱 k이므로
			// 이전에 들어갔던 값 중 가장 큰 값을
			// 거리값이 작은 것들로 갱신 
			else if (dist[next].top() > n_dist) {
				dist[next].pop();	// dist[next].size() == k - 1
				dist[next].push(n_dist);	// dist[next].size() == k
				pq.push(make_pair(n_dist, next));
			}
		}
	}
}


int main(void) {
	int n, m;	// 도시, 도로 수 
	
	scanf("%d %d %d", &n, &m, &k);
	
	for(int i = 0; i < m; i++) {
		int from, to, w;	// 출발, 도착, 가중치 
		
		scanf("%d %d %d", &from, &to, &w);
		from--; to--;	// 0부터 시작 
		
		adj[from].push_back(make_pair(w, to));
	}
	
	// k번째 최단경로를 top에 담고 있는 dist 큐 만들기 
	dijkstra(0);
	
	for(int i = 0; i < n; i++) { 
		if (dist[i].size() == k) printf("%d\n", dist[i].top());	// 이래야 k번째 최단경로가 top에 있음 
		else printf("-1\n");	// 다른 경우는 k번째 최단 경로가 없는 경우 
	}
	
	return 0;
}
