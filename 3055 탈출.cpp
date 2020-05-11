/*****************/
// BOJ 3055 탈출
// 핵심: BFS + 순서 파악 
/*****************/
#include <stdio.h>
#include <queue>
#define MAX 60

using namespace std;

typedef struct pt {
	int x, y, t, type;
} pt;

int r, c;	// 지도의 세로, 가로 
int dx[] = {0, 0, 1, -1};	// up, down, right, left
int dy[] = {-1, 1, 0, 0};
char map[MAX][MAX];
pt start;	// 고슴도치 시작점 
queue<pt> q;

void input_Data(void) {
	scanf("%d %d", &r, &c);
	
	for(int j = 0; j < r; j++) {
		scanf("%s", map[j]);
		
		for(int i = 0; i < c; i++) {
			// 고슴도치가 있을 때 
			if(map[j][i] == 'S') {
				start.x = i;
				start.y = j;
			}
			// 물일 때 
			else if(map[j][i] == '*') {
				pt tmp = {i, j, 0, 1};
				q.push(tmp);
			}
		}
	}
}

int bfs(void) {
	// 먼저 모든 물을 움직인 후에 고슴도치를 움직이는 함수 
	
	q.push(start);	// 고슴도치 위치를 넣음 
	
	while(!q.empty()) {
		pt cur = q.front(); q.pop();	// 현재 위치 
		
		for(int i = 0; i < 4; i++) {
			int mx = cur.x + dx[i];
			int my = cur.y + dy[i];
			
			// 범위 확인 
			if(mx < 0 || mx >= c || my < 0 || my >= r) continue;
			// 돌 or 이미 물이 차있음 
			if(map[my][mx] == 'X' || map[my][mx] == '*') continue;
			// 비버 굴 도착 
			if(map[my][mx] == 'D') {
				// 지금 움직이는것이 고슴도치일 때 
				if(!cur.type) return cur.t + 1;
				// 물일 때 
				else continue;
			}
			// 고슴도치임 & 이미 고슴도치가 들렀던 곳임 
			if(!cur.type && map[my][mx] == 'S') continue;
			
			pt tmp = {mx, my, cur.t + 1, cur.type};
			q.push(tmp);
			
			// 고슴도치임 
			if(!cur.type) map[my][mx] = 'S';
			// 물임 
			else map[my][mx] = '*';
		}
	}
	
	return -1;
}


int main(void) {
	input_Data();
	int ans = bfs();
	
	if(ans != -1) printf("%d\n", ans);
	else printf("KAKTUS\n");
	
	return 0;
}
