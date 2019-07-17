#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int inDegree[501];	// ���� 
int cost[501];	// �� 
vector<int> adj[501];	// ���� ��� 
int sum[501];	// ������ �����ϱ� �������� �ִ� �� 

queue<int> q;	// �켱���� ť 

int main(void) {
	int N;	// ��� �� 

	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		int c, from;	// ��, ������ ���� ���� �Ǿ�� �ϴ� ��� 

		scanf("%d", &c);
		cost[i] = c;

		while (scanf("%d", &from) && from != -1) {
			from--;	// �ٸ� �͵�� index ������ 
			adj[from].push_back(i);	// ������Ŀ� �־� �� 
			inDegree[i]++;	// ���� ���� 
		}
	}
	
	for (int i = 0; i < N; i++) {
		if (inDegree[i] == 0) q.push(i);	
	}
	
	while(!q.empty()) {
		int cnt = q.size(); 
		
		// ť�� �ִ� ��忡 ���� �Ǿ� �ִ� �͵� ���� �ٲ��ֱ� 
		for (int i = 0; i < cnt; i++) {
			int now = q.front();
			q.pop();
			inDegree[now]--;
			
			// ���� ���� �� ������ 
			for(int next : adj[now]) {
				inDegree[next]--;
				
				if (inDegree[next] == 0) q.push(next);
				
				int preTime = cost[now] + sum[now];	// ���� ���������� �ĺ��� 
				
				if (preTime > sum[next]) sum[next] = preTime;	// �� ū ���� �ĺ��� 
			}
		}
	}
	
	for (int i = 0; i < N; i++) {
		printf("%d\n", cost[i] + sum[i]);	// ���� �� + �� �ڽ� 
	}

	return 0;
}

