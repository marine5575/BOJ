/****************/
// BOJ 17142 연구소
// 핵심: DFS (백트래킹) + BFS
// 			 +) 문제파악 잘하자^^
/****************/
// 1. 처음 생각한 것 (단순 DFS 후 모든 경우 BFS) 
#if 0 

#include <stdio.h>
#include <vector>
#include <queue>
#define MAX 		51
#define PLC_MAX 11
#define INF 		987654321

using namespace std;

typedef struct pt {
	int x, y;
} pt;

int n, m;	// 연구소 크기, 놓을 수 있는 바이러스 개수 
int minTime = INF, road;	// 정답, 총 빈칸 개수 
int map[MAX][MAX];
int visited[PLC_MAX];	// 바이러스 가져갔는지 
int dx[] = {1, 0, -1, 0};	// right, down, left, up
int dy[] = {0, 1, 0, -1};
vector<pt> place;	// 바이러스 놓을 수 있는 위치들

void bfs(void) {
	// 모든 시작 지점에서 바이러스를 동시에 퍼뜨리는 함수
	
	int time = 1;	// 모두 다 퍼지는데 걸리는 시간
	int remain = 0;	// 바이러스 침투한 칸 수 
	int spread[MAX][MAX] = {0, };
	queue<pt> q;
	
	for(int i = 0; i < place.size(); i++) {
		// 놓을 바이러스가 아니면 통과 
		if(!visited[i]) continue;
		
		int x = place[i].x, y = place[i].y;
		q.push(place[i]);
		spread[y][x] = 1;
	}
	
	while(!q.empty()) {
		pt cur = q.front();
		q.pop();
		int cnt = spread[cur.y][cur.x];	// 현재까지 오는데 걸린 시간 
		
		for(int i = 0; i < 4; i++) {
			int mx = cur.x + dx[i];
			int my = cur.y + dy[i];
			
			// 범위 확인 
			if(mx < 0 || mx >= n || my < 0 || my >= n) continue;
			// 벽임 or 이미 들림 
			if(map[my][mx] == 1 || spread[my][mx]) continue;
			
			pt tmp = {mx, my};
			q.push(tmp);
			spread[my][mx] = cnt + 1;
			
			// 빈칸이었을 경우만 시간이 흐름^^ 
			if(!map[my][mx]) {
				time = cnt + 1;
				remain++;
			}
		}
	}
	
	// 빈칸 모조리 감염됨 
	if(remain == road) {
		// 최소값 갱신 
		if(minTime > time) time = maxTime;
	}
}

void dfs(int idx, int cnt) {
	// 이제 place[idx]에 바이러스를 놓을 차례고 
	// 지금까지 총 cnt개 바이러스 놓음
	
	// 다 놓았다 
	if(cnt == m) {
		bfs();
		return;
	}
	
	for(int i = idx; i < place.size(); i++) {
		// 이미 놓았으면 패스 
		if(visited[i]) continue;
		
		visited[i] = 1;
		
		dfs(i + 1, cnt + 1);
		
		visited[i] = 0;
	}
}

int main(void) {
	scanf("%d %d", &n, &m);
	
	for(int j = 0; j < n; j++) {
		for(int i = 0; i < n; i++) {
			scanf("%d", &map[j][i]);
			
			if(map[j][i] == 2) {
				pt tmp = {i, j};
				place.push_back(tmp);
			}
			else if(map[j][i] == 0) road++;
		}
	}
	
	dfs(0, 0);
	
	// 다 감염 시키는 건 불가능
	if(minTime == INF) printf("-1\n");
	// 가능했음 
	else printf("%d\n", minTime - 1);
	
	return 0;
}
#endif

// 2. 각 바이러스가 퍼졌을 경우를 가정해서 나중에 최소값 찾는 방법 
#if 0

#include <stdio.h>
#include <vector>
#include <queue>
#define MAX 		51
#define PLC_MAX	11
#define INF 987654321

using namespace std;

typedef struct pt {
	int x, y;
} pt;

int n, m;	// 연구소 크기, 퍼뜨릴 바이러스 개수 
int minTime = INF;	// 다 퍼지는데 걸리는 최소 시간 
int map[MAX][MAX];	// 지도
int spread[PLC_MAX][MAX][MAX];	// spread[k][y][x] : k번째 바이러스가 퍼졌을 때
int visited[PLC_MAX];	// 이번에 퍼질 바이러스 표시 
int dx[] = {1, 0, -1, 0};	// right, down, left, up
int dy[] = {0, 1, 0, -1};
vector<pt> place;	// 바이러스 놓을 수 있는 위치들 

void bfs(int at) {
	// place[at]에 있는 것부터 연결된 모든 길에 대해 BFS하는 함수
	
	int x = place[at].x, y = place[at].y;
	queue<pt> q;
	q.push(place[at]);
	spread[at][y][x] = 1;
	
	while(!q.empty()) {
		pt cur = q.front();
		q.pop();
		int cnt = spread[at][cur.y][cur.x];
		
		for(int i = 0; i < 4; i++) {
			int mx = cur.x + dx[i];
			int my = cur.y + dy[i];
			
			// 범위 확인 
			if(mx < 0 || mx >= n || my < 0 || my >= n) continue;
			// 벽이거나 이미 퍼졌거나 
			if(map[my][mx] == 1 || spread[at][my][mx]) continue;
			
			pt tmp = {mx, my};
			q.push(tmp);
			spread[at][my][mx] = cnt + 1;
		}
	}
}

void findMinTime(void) {
	// 모두 다 퍼진 시간을 구해서 정답과 비교하여 정답 갱신
	 
	int maxTime = 1;	// 모두 다 퍼지는 시간 
	
	for(int j = 0; j < n; j++) {
		for(int i = 0; i < n; i++) {
			// 빈칸 아니면 통과 
			if(map[j][i] != 0) continue;
			
			int min = INF;	// 각 칸에서 가장 최소 값 
			
			for(int k = 0; k < place.size(); k++) {
				// 바이러스 놓은 곳 아니면 통과 
				if(!visited[k]) continue;
				
				// 퍼진적이 있음 &  최소값 갱신 
				if(spread[k][j][i] && min > spread[k][j][i]) {
					min = spread[k][j][i];
				}
			}
			
			// 최대값 갱신 
			if(maxTime < min) maxTime = min;
		}
	}
	
	// 최소값 갱신 
	if(minTime > maxTime) minTime = maxTime;
}

void dfs(int idx, int cnt) {
	// place[idx]에 바이러스를 놓을 차례이고,
	// 여태 cnt개의 바이러스를 놓았음
	
	// 원하는 만큼 놓았음 
	if(cnt == m) {
		findMinTime();
		return;
	}
	
	for(int i = idx; i < place.size(); i++) {
		// 이미 방문했으면 통과 
		if(visited[i]) continue;
		
		visited[i] = 1;	// 방문 체크 
		dfs(i + 1, cnt + 1);
		visited[i] = 0;	// 방문 해제 
	} 
}


int main(void) {
	scanf("%d %d", &n, &m);
	
	for(int j = 0; j < n; j++) {
		for(int i = 0; i < n; i++) {
			scanf("%d", &map[j][i]);
		
			if(map[j][i] == 2) {
				pt tmp = {i, j};
				place.push_back(tmp);
			}
		}
	}
	
	// 일단 모든 자리에서 바이러스 퍼트림 
	for(int i = 0; i < place.size(); i++) {
		bfs(i);
	}
	
	dfs(0, 0);
	
	// 모든 곳에 퍼트릴 수 없을 때 
	if(minTime == INF) printf("-1\n");
	// 가능했음 
	else printf("%d\n", minTime - 1);
	
	return 0;
}

#endif
