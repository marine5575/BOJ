/*********************/
// BOJ 2667 단지번호붙이기
// 핵심: DFS / BFS 
/*********************/
#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>
#define MAX 35

using namespace std;

typedef struct pt {
	int x, y;
} pt;

int n;	// 지도 크기 
int visited[MAX][MAX], ans[MAX * MAX];	// 단지 체크, ans[i] = (i + 1)번 단지에 있는 집 개수 
int dx[] = {1, 0, -1, 0};	// right, down, left, up
int dy[] = {0, 1, 0, -1};
char map[MAX][MAX];

void input_Data(void) {
	scanf("%d", &n);
	
	for(int i = 0; i < n; i++) {
		scanf(" %s", map[i]);
	}
}

int bfs(int sx, int sy, int flag) {
	// (sx, sy)에서 시작해서 연결된 집을 flag로 채우는 함수
	
	queue<pt> q;
	pt init = {sx, sy};
	q.push(init);
	visited[sy][sx] = flag;
	int homeNum = 1;	// flag번 단지 안 집의 개수 
	
	while(!q.empty()) {
		pt cur = q.front(); q.pop();
		
		for(int i = 0; i < 4; i++) {
			int mx = cur.x + dx[i];
			int my = cur.y + dy[i];
			
			// 범위 확인 
			if(mx < 0 || mx >= n || my < 0 || my >= n) continue;
			// 집이 없음 or 이미 경험함 
			if(map[my][mx] == '0' || visited[my][mx]) continue;
			
			pt tmp = {mx, my};
			q.push(tmp);
			visited[my][mx] = flag;
			homeNum++;
		}
	}
	
	return homeNum;
}

void sol(void) {
	int cnt = 0;	// 단지 개수 
	
	for(int j = 0; j < n; j++) {
		for(int i = 0; i < n; i++) {
			// 집이 없음 or 이미 단지에 속함 
			if(map[j][i] == '0' || visited[j][i]) continue;
			
			ans[cnt] = bfs(i, j, cnt + 1);
			cnt++;
		}
	}
	
	printf("%d\n", cnt);
	
	sort(ans, ans + cnt);	// 오름차순 정렬 
	
	for(int i = 0; i < cnt; i++) {
		printf("%d\n", ans[i]);
	}
}


int main(void) {
	input_Data();
	sol();
	
	return 0;
}
