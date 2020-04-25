/*********************/
// BOJ 6593 상범 빌딩
// 핵심: BFS 
/*********************/
#include <stdio.h>
#include <queue>
#define MAX 40

using namespace std;

typedef struct pt {
	int x, y, z, t;
} pt;

int l, r, c;	// 지도의 높이, 세로, 가로 
int dx[] = {1, -1, 0, 0, 0, 0};	// 동서남북상하 
int dy[] = {0, 0, 1, -1, 0, 0};
int dz[] = {0, 0, 0, 0, -1, 1};
char map[MAX][MAX][MAX]; 
pt start;	// 시작 지점 

void input_Data(void) {
	int flag = 0;	// 시작 지점 찾았나? 
	
	for(int k = 0; k < l ; k++) {
		for(int j = 0; j < r; j++) {
			scanf(" %s", &map[k][j]);
			
			if(flag) continue;
			
			for(int i = 0; i < c; i++) {
				// 시작 지점 
				if(map[k][j][i] == 'S') {
					start.x = i; start.y = j; start.z = k;
					start.t = 0;
					flag = 1;
					break;
				}
			}
		}
	}
}

int bfs(void) {
	// start에서 E까지 가는 함수
	
	queue<pt> q;
	q.push(start);
	
	while(!q.empty()) {
		pt cur = q.front(); q.pop();	// 현재 위치 
		
		for(int i = 0; i < 6; i++) {
			int mx = cur.x + dx[i];
			int my = cur.y + dy[i];
			int mz = cur.z + dz[i];
			
			// 범위 확인 
			if(mx < 0 || mx >= c || my < 0 || my >= r || mz < 0 || mz >= l) continue;
			// 도착함 
			if(map[mz][my][mx] == 'E') return cur.t + 1;
			// 갈 수 없는 곳('#') or 이미 들렀음('S') 
			if(map[mz][my][mx] != '.') continue;
			
			pt tmp = {mx, my, mz, cur.t + 1};
			q.push(tmp);
			map[mz][my][mx] = 'S';
		}
	}
	
	return -1;	// 탈출 불가 
}


int main(void) {
	while(1) {
		scanf("%d %d %d", &l, &r, &c);
		
		// 테스트 케이스 끝 
		if(l == 0 && r == 0 && c == 0) break;
		
		input_Data();
		
		int ans = bfs();	// 탈출하는데 걸린 시간 
		
		if(ans != -1) printf("Escaped in %d minute(s).\n", ans);
		else printf("Trapped!\n");
	}
	
	return 0;
}
