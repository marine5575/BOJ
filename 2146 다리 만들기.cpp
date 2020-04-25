/***********************/
// BOJ 2146 다리만들기
// 핵심: Flood Fill + BFS
/***********************/ 
#include <stdio.h>
#include <queue>
#define MAX 101
#define INF ((int)1e4 + 1)

using namespace std;

typedef struct pt {
	int x, y, t;
} pt;

int n, minLen = INF;	// 지도 크기, 가장 짧은 다리 
int map[MAX][MAX], visited[MAX][MAX];
int dx[] = {1, 0, -1, 0};	// right, down, left, up
int dy[] = {0, 1, 0, -1}; 

void input_Data(void) {
	scanf("%d", &n);
	
	for(int j = 0; j < n; j++) {
		for(int i = 0; i < n; i++) {
			scanf("%d", &map[j][i]);
		}
	}
}

int bfs(int x, int y, int color) {
	// (x, y)에서 연결된 바다로만 길을 찾는 함수(방문은 color로)
	
	int flag = map[y][x];	// 시작 대륙 색깔 
	queue<pt> q;
	pt init = {x, y, 0};
	q.push(init);
	visited[y][x] = color;
	
	while(!q.empty()) {
		pt cur = q.front(); q.pop();	// 현재 위치 
		
		// 예전이 더 좋았음 
		if(minLen < cur.t) return cur.t;
		
		for(int i = 0; i < 4; i++) {
			int mx = cur.x + dx[i];
			int my = cur.y + dy[i];
			
			// 범위 확인 & 이미 경험함 
			if(mx < 0 || mx >= n || my < 0 || my >= n || visited[my][mx] == color) continue;
			// 바다에서 출발해서 다른 대륙에 도착함 
			if(!map[cur.y][cur.x] && map[my][mx] && map[my][mx] != flag) return cur.t;
			// 같은 대륙 안임 
			if(map[my][mx] == flag) continue;
			
			pt tmp = {mx, my, cur.t + 1};
			q.push(tmp);
			visited[my][mx] = color;
		}
	}
	
	return INF;
}

int check(int x, int y) {
	// (x, y) 좌표 사방에 바다가 하나라도 있으면 1 반환, 아니면 0 반환
	
	for(int i = 0; i < 4; i++) {
		int mx = x + dx[i];
		int my = y + dy[i];
		
		// 범위 확인 
		if(mx < 0 || mx >= n || my < 0 || my >= n) continue;
		// 바다있음! 
		if(!map[my][mx]) return 1;
	}
	
	return 0;	// 바다 없음 
}

void connect(int x, int y, int color) {
	// (x, y)에 연결되어 있는 대륙을 color로 칠함
	
	queue<pt> q;
	pt init = {x, y, 0};
	q.push(init);
	map[y][x] = color;
	
	while(!q.empty()) {
		pt cur = q.front(); q.pop();	// 현재 위치 
		
		for(int i = 0; i < 4; i++) {
			int mx = cur.x + dx[i];
			int my = cur.y + dy[i];
			
			// 범위 확인 & 미발견 대륙 아님 
			if(mx < 0 || mx >= n || my < 0 || my >= n || map[my][mx] != 1) continue;
			
			pt tmp = {mx, my, 0};
			q.push(tmp);
			map[my][mx] = color;
		}
	}
}

void paint(void) {
	int color = 2;	// 대륙에 칠할 색깔 
	
	for(int j = 0; j < n; j++) {
		for(int i = 0; i < n; i++) {
			// 미발견 대륙 아님 
			if(map[j][i] != 1) continue;
			
			connect(i, j, color++);
		}
	}
}

int sol(void) {
	// 섬의 외곽에서 BFS할 수 있도록 하는 함수
	
	paint();	// 대륙별로 색칠함 
	
	int cnt = 0;	// 방문 표시할 색 
	
	for(int j = 0; j < n; j++) {
		for(int i = 0; i < n; i++) {
			// 바다임 or 육지인데 내륙 한가운데임 
			if(!map[j][i] || !check(i, j)) continue;
			
			int result = bfs(i, j, ++cnt);	// 여기서 제일 짧은 다리 
			
			// 최소값 갱신 
			if(minLen > result) minLen = result;
		}
	}
	
	return minLen;
}


int main(void) {
	input_Data();
	printf("%d\n", sol());
	
	return 0;
}
