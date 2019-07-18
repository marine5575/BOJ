#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>
#define INF 987654321

using namespace std;

int N, M;	// ��� ��, ���� �� 
vector<pair<int, int>> adj[501];	// ���� ��� 
vector<pair<int, int>> trace[501];	// �ִ� �Ÿ��� ���� 

vector<int> dijkstra(int start) {
	vector<int> dist(N, INF);	// �Ÿ� 
	priority_queue<pair<int, int>> pq;	// �ּ� �� ã�� ���� 
	pq.push(make_pair(0, start));	// ó������ ������ �ȵǹǷ� 

	dist[start] = 0;	// ���� ����� �Ÿ� 

	while (!pq.empty()) {
		int now = pq.top().second;	// ���� ��ġ 
		int cost = -pq.top().first;	// ���� �Ÿ� 
		pq.pop();

		if (dist[now] < cost) continue;	// �ּ� �Ÿ��� ��� 

		// ���� ��� ������ŭ �ݺ� 
		for (int i = 0; i < adj[now].size(); i++) {
			int next = adj[now][i].second;	// ���� ��� 
			int n_dist = adj[now][i].first + cost;	// ���� ����� �ĺ� �Ÿ� 
			
			if (adj[now][i].first == -1) continue;	// ���� �ִ� �Ÿ����� ���� ���� 
			
			// �ĺ��� �� ���� �� ���� 
			if (dist[next] > n_dist) {
				dist[next] = n_dist;
				pq.push(make_pair(-n_dist, next));
				
				// ���� ������ �ǹ� x. ���� ���� ���� 
				trace[next].clear();
				trace[next].push_back(make_pair(n_dist, now));
			}
			// �ִܰŸ��� �� ���� �ƴ� �� �����Ƿ�
			// ���Ƶ� ������ ���� 
			else if (dist[next] == n_dist) {
				trace[next].push_back(make_pair(n_dist, now));
			}
		}
	}
	
	return dist;
}

void bfs(int dest) {
	queue<int> q;	// �������� ���� ���� 
	
	q.push(dest);
	
	while(!q.empty()) {
		int now = q.front();	// ���� ��ġ 
		q.pop();
		
		// ���� ������ŭ ����
		// bfs�� ���� 
		for (int i = 0; i < trace[now].size(); i++) {
			int next = trace[now][i].second;	// ���� ��ġ 
			
			// ��� ���� �Ųٷ� ��¤�� �ִ� ���̹Ƿ� 
			for(int j = 0; j < adj[next].size(); j++) {
				// ���� ��ġ�� ������ �͵� �� ���� ��ġ�� �ִ°�? 
				if(adj[next][j].second == now) {
					adj[next][j].first = -1;	// �� ���� ���Ƴ��� 
				}
			}
			
			q.push(next);
		}
	}
}


int main(void) {
	// 0 0�� �Է� ������ ���� 
	while(scanf("%d %d", &N, &M) && !(N == 0 && M == 0)) {
		int start, end;	// ����, �� ���� 
		
		scanf("%d %d", &start, &end);
		
		// ������ ���� ��� �ʱ�ȭ 
		for (int i = 0; i < 501; i++) {
			adj[i].clear();
			trace[i].clear();
		}
		
		// ���� ���� �ޱ� 
		for(int i = 0; i < M; i++) {
			int from, to, w;
			
			scanf("%d %d %d", &from, &to, &w);
			
			adj[from].push_back(make_pair(w, to));
		}
		
		// �ּ��� �ִ� �Ÿ� ã�� 
		dijkstra(start);
		
		// �ִ� �Ÿ����� ���������� 
		bfs(end);
		
		vector<int> ans = dijkstra(start);	// ���� �ִ� �Ÿ� 
		
		if(ans[end] == INF) printf("-1\n");
		else printf("%d\n", ans[end]);
	}

	return 0;
}
