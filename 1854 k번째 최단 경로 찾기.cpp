#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>
#define INF 987654321

using namespace std;
typedef pair<int, int> pii;

priority_queue<int> dist[1001];	// k��°���� �Ÿ� ���� (�ִ� ��) 
vector<pii> adj[1001];	// ���� ��� 

int k;	// k��° �ִ� �Ÿ� ���ؾ� �� 

void dijkstra(int start) {
	priority_queue<pii, vector<pii>, greater<>> pq;	// �ּڰ� �񱳸� ���� �켱���� ť (�ּ� ��) 
	pq.push(make_pair(0, start));	// ó������ ���� ���� 
	dist[start].push(0);	// ���� ����� �ִ� �Ÿ� 
	
	while(!pq.empty()) {
		int now = pq.top().second;	// ���� ��ġ 
		int cost = pq.top().first;	// ���� ����ġ 
		pq.pop(); 
		
		// ���� ��� ��� ���캽 
		for(int i = 0; i < adj[now].size(); i++) {
			int next = adj[now][i].second;	// ���� ��ġ 
			int n_dist = adj[now][i].first + cost;	// ���� �Ÿ� �ĺ� 
			
			// dist�� �ִ����̹Ƿ�
			// dist�� ũ�Ⱑ k ���϶�� ���� �������̷� ���� 
			if(dist[next].size() < k) {
				dist[next].push(n_dist);
				pq.push(make_pair(n_dist, next));
			}
			// dist�� �� k�̹Ƿ�
			// ������ ���� �� �� ���� ū ����
			// �Ÿ����� ���� �͵�� ���� 
			else if (dist[next].top() > n_dist) {
				dist[next].pop();	// dist[next].size() == k - 1
				dist[next].push(n_dist);	// dist[next].size() == k
				pq.push(make_pair(n_dist, next));
			}
		}
	}
}


int main(void) {
	int n, m;	// ����, ���� �� 
	
	scanf("%d %d %d", &n, &m, &k);
	
	for(int i = 0; i < m; i++) {
		int from, to, w;	// ���, ����, ����ġ 
		
		scanf("%d %d %d", &from, &to, &w);
		from--; to--;	// 0���� ���� 
		
		adj[from].push_back(make_pair(w, to));
	}
	
	// k��° �ִܰ�θ� top�� ��� �ִ� dist ť ����� 
	dijkstra(0);
	
	for(int i = 0; i < n; i++) { 
		if (dist[i].size() == k) printf("%d\n", dist[i].top());	// �̷��� k��° �ִܰ�ΰ� top�� ���� 
		else printf("-1\n");	// �ٸ� ���� k��° �ִ� ��ΰ� ���� ��� 
	}
	
	return 0;
}
