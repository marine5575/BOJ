#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int inDegree[501];	// 위상 
int cost[501];	// 값 
vector<int> adj[501];	// 인접 노드 
int sum[501];	// 나까지 도달하기 전까지의 최대 값 

queue<int> q;	// 우선순위 큐 

int main(void) {
	int N;	// 노드 수 

	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		int c, from;	// 값, 나보다 먼저 실행 되어야 하는 노드 

		scanf("%d", &c);
		cost[i] = c;

		while (scanf("%d", &from) && from != -1) {
			from--;	// 다른 것들과 index 맞춰줌 
			adj[from].push_back(i);	// 인접행렬에 넣어 줌 
			inDegree[i]++;	// 위상 증가 
		}
	}
	
	for (int i = 0; i < N; i++) {
		if (inDegree[i] == 0) q.push(i);	
	}
	
	while(!q.empty()) {
		int cnt = q.size(); 
		
		// 큐에 있는 노드에 연결 되어 있는 것들 위상 바꿔주기 
		for (int i = 0; i < cnt; i++) {
			int now = q.front();
			q.pop();
			inDegree[now]--;
			
			// 인접 벡터 빌 때까지 
			for(int next : adj[now]) {
				inDegree[next]--;
				
				if (inDegree[next] == 0) q.push(next);
				
				int preTime = cost[now] + sum[now];	// 다음 직전까지의 후보값 
				
				if (preTime > sum[next]) sum[next] = preTime;	// 더 큰 것을 후보로 
			}
		}
	}
	
	for (int i = 0; i < N; i++) {
		printf("%d\n", cost[i] + sum[i]);	// 직전 값 + 나 자신 
	}

	return 0;
}

