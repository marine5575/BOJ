#include <cstdio>
#include <queue>

using namespace std;

int adj[1001][1001];	// adj[i][j] = (1 or 0) : i에서j로가는 양방향 길이 (있다 or 없다) 
int visited[1001];	// visited[i] = (1 or 0) : i를 (방문함 or 하지 x) 

int n;	// 노드 개수 

void dfs(int start) {
	printf("%d ", start);
	
	// 연결된 모든 노드 검사 
	for(int i = 1; i <= n; i++) {
		// 연결되어 있는가? 방문한 적이 없는가? 
		while(adj[start][i] == 1 && !visited[i]) {
			visited[i] = 1;	// 방문 체크 
			dfs(i);	// 그쪽으로 계속 진행 
		}
	}
}

void bfs(int start) {
	queue<int> q;
	
	q.push(start);
	
	// 인접 노드가 없어질 때까지 
	while(!q.empty()) {
		int now = q.front();	// 현재 위치 
		q.pop();
		printf("%d ", now);
		
		// 모든 노드에 대해서 검사 
		for(int i = 1; i <= n; i++) {
			// 연결되어 있는가? 방문한 적 없는가? 
			if(adj[now][i] && !visited[i]) {
				q.push(i);
				visited[i] = 1;	// 방문 체크 
			}
		}
	}
}


int main(void) {
	int m, v;	// 간선 개수, 시작점 
	scanf("%d %d %d", &n, &m, &v);
	
	for(int i = 0, x, y; i < m; i++) {
		scanf("%d %d", &x, &y);
		adj[x][y] = 1;
		adj[y][x] = 1;
	}
	
	visited[v] = 1;	// 시작점 방문체크 
	dfs(v);
	printf("\n");
	
	// 방문 배열 다시 초기화 
	fill_n(visited, n + 1, 0);
	visited[v] = 1;	// 시작점 방문체크 
	bfs(v);
	printf("\n"); 
	
	
	return 0;
}
