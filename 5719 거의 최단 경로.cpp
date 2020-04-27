/**************************/
// BOJ 5719 거의 최단 경로
// 핵심: dijkstra + DFS / BFS
// 	 => 속도: BFS <<<<< DFS (그냥 500 * 500 이면 BFS 돌리기)
/**************************/
#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>
#define INF 987654321

using namespace std;

int N, M;	// 장소 수, 도로 수 
vector<pair<int, int>> adj[501];	// 인접 노드 
vector<pair<int, int>> trace[501];	// 최단 거리의 흔적 

vector<int> dijkstra(int start) {
	vector<int> dist(N, INF);	// 거리 
	priority_queue<pair<int, int>> pq;	// 최소 값 찾기 위해 
	pq.push(make_pair(0, start));	// 처음부터 막히면 안되므로 

	dist[start] = 0;	// 시작 노드의 거리 

	while (!pq.empty()) {
		int now = pq.top().second;	// 현재 위치 
		int cost = -pq.top().first;	// 현재 거리 
		pq.pop();

		if (dist[now] < cost) continue;	// 최소 거리만 통과 

		// 인접 노드 갯수만큼 반복 
		for (int i = 0; i < adj[now].size(); i++) {
			int next = adj[now][i].second;	// 다음 노드 
			int n_dist = adj[now][i].first + cost;	// 다음 노드의 후보 거리 
			
			if (adj[now][i].first == -1) continue;	// 가장 최단 거리였던 노드는 제외 
			
			// 후보가 더 작을 때 갱신 
			if (dist[next] > n_dist) {
				dist[next] = n_dist;
				pq.push(make_pair(-n_dist, next));
				
				// 이전 흔적은 의미 x. 새로 흔적 갱신 
				trace[next].clear();
				trace[next].push_back(make_pair(n_dist, now));
			}
			// 최단거리는 한 개가 아닐 수 있으므로
			// 같아도 흔적을 남김 
			else if (dist[next] == n_dist) {
				trace[next].push_back(make_pair(n_dist, now));
			}
		}
	}
	
	return dist;
}

void bfs(int dest) {
	queue<int> q;	// 차근차근 넣을 공간 
	
	q.push(dest);
	
	while(!q.empty()) {
		int now = q.front();	// 현재 위치 
		q.pop();
		
		// 현재 흔적만큼 조사
		// bfs인 이유 
		for (int i = 0; i < trace[now].size(); i++) {
			int next = trace[now][i].second;	// 다음 위치 
			
			// 사실 지금 거꾸로 되짚고 있는 것이므로 
			for(int j = 0; j < adj[next].size(); j++) {
				// 다음 위치의 인접한 것들 중 현재 위치가 있는가? 
				if(adj[next][j].second == now) {
					adj[next][j].first = -1;	// 못 오게 막아놓기 
				}
			}
			
			q.push(next);
		}
	}
}


int main(void) {
	// 0 0을 입력 받으면 종료 
	while(scanf("%d %d", &N, &M) && !(N == 0 && M == 0)) {
		int start, end;	// 시작, 끝 지점 
		
		scanf("%d %d", &start, &end);
		
		// 흔적과 인접 노드 초기화 
		for (int i = 0; i < 501; i++) {
			adj[i].clear();
			trace[i].clear();
		}
		
		// 인접 정보 받기 
		for(int i = 0; i < M; i++) {
			int from, to, w;
			
			scanf("%d %d %d", &from, &to, &w);
			
			adj[from].push_back(make_pair(w, to));
		}
		
		// 최선의 최단 거리 찾기 
		dijkstra(start);
		
		// 최단 거리들을 지워버리기 
		bfs(end);
		
		vector<int> ans = dijkstra(start);	// 거의 최단 거리 
		
		if(ans[end] == INF) printf("-1\n");
		else printf("%d\n", ans[end]);
	}

	return 0;
}
