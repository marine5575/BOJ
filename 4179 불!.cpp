/*******************/
// BOJ 4179 불!
// 핵심: 순서가 있는 BFS
// 			 => 시간 줄이겠다고 다음 위치에서 조건 충족하면 나가게 하는 것
// 					하지 말 것! (<- 첫 위치가 조건을 만족할 수도 있음) 
/*******************/ 
#include <stdio.h>
#include <queue>
#define MAX 1010

using namespace std;

typedef struct pt {
	int x, y, t, type;
} pt;

int r, c;	// 지도의 세로, 가로 
int dx[] = {1, 0, -1, 0};	// right, down, left, up
int dy[] = {0, 1, 0, -1};
char map[MAX][MAX];
pt start;	// 지훈이 시작 지점 
queue<pt> q;

void input_Data(void) {
	scanf("%d %d", &r, &c);
	
	for(int j = 0; j < r; j++) {
		scanf(" %s", map[j]);
		
		for(int i = 0; i < c; i++) {
			// 지훈이 
			if(map[j][i] == 'J') {
				start.x = i; start.y = j;
				start.t = 0; start.type = 0;
			}
			// 불난 위치 => 먼저 queue에 넣어서 확산 
			else if(map[j][i] == 'F') {
				pt tmp = {i, j, 0, 1};
				q.push(tmp);
			}
		}
	}
}

inline int check(int x, int y) {
	// 외곽 지역임 
	if(x == 0 || x == c - 1 || y == 0 || y == r - 1) return 1;
	// 외곽 지역이 아님 
	else return 0;
}

int bfs(void) {
	// 불을 먼저 확산 시킨 후에 지훈이를 움직여서 같은 시간에
	// 불난 곳은 갈 수 없게 함 
	
	q.push(start);
	
	while(!q.empty()) {
		pt cur = q.front(); q.pop();	// 현재 위치 
		
		// 지훈이임 & 외곽 지역임 
		if(!cur.type && check(cur.x, cur.y)) return cur.t + 1;
		
		for(int i = 0; i < 4; i++) {
			int mx = cur.x + dx[i];
			int my = cur.y + dy[i];
			
			// 범위 확인 
			if(mx < 0 || mx >= c || my < 0 || my >= r) continue;
			// 벽임 or 불임 
			if(map[my][mx] == '#' || map[my][mx] == 'F') continue;
			// 지훈이임 & 이미 들렀던 곳임 
			if(!cur.type && map[my][mx] == 'J') continue;
			
			pt tmp = {mx, my, cur.t + 1, cur.type};
			q.push(tmp);
			
			// 지훈이임 
			if(!cur.type) map[my][mx] = 'J';
			// 불임 
			else map[my][mx] = 'F';
		}
	}
	
	return -1;
}


int main(void) {
	input_Data();
	
	int ans = bfs();	// 실패하면 -1 반환 
	
	// 성공 
	if(ans != -1) printf("%d\n", ans);
	// 실패 
	else printf("IMPOSSIBLE\n");
	
	return 0;
} 
