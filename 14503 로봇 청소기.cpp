/************************/
// BOJ 14503 로봇 청소기
// 핵심: 중간에 끊기는 DFS 
/************************/
#include <iostream>
#include <cstring>

using namespace std;

int n, m, cnt;	// height, width, 청소한 칸 
int rx, ry, dir;	// robot (x, y), 바라보는 방향 
int map[51][51];	// map
int dx[] = {0, 1, 0, -1};	// up, right, down, left (오른쪽으로 도는 순) 
int dy[] = {-1, 0, 1, 0};	// up, right, down, left


void move(int x, int y, int dir) {
	// 벽임 => 끝 
	if(map[y][x] == 1) return;
	
	// 더러움 
	if(map[y][x] == 0) {
		map[y][x] = -1;
		cnt++;
	}
	
	// 모든 방향 가봄 
	for(int i = 0; i < 4; i++) {
		int searchDir = (dir - 1 < 0) ? 3 : dir - 1;	// 왼쪽으로 돔 
		// int searchDir = (dir + 3) % 4;
		int mx = x + dx[searchDir], my = y + dy[searchDir];	// 가려는 (mx, my) 
		
		// 더러움? 
		if(map[my][mx] == 0) {
			// 닦으러 감 
			move(mx, my, searchDir);
			return;	// 더 가지 않아 
		}
		// 갈 수 없는 상태 
		else {
			dir = searchDir;	// 일단 회전 
		}
	}
	
	// 이미 모든 방향 봤음 -> 후진 
	int mx = x - dx[dir], my = y - dy[dir];
	
	move(mx, my, dir);
}


int main(void) {
	cin.tie(0);
	ios::sync_with_stdio(0);
	
	cin >> n >> m >> ry >> rx >> dir;
	memset(map, 1, sizeof(map));
	
	for(int j = 0; j < n; j++) {
		for(int i = 0; i < m; i++) {
			cin >> map[j][i];
		}
	}
	
	move(rx, ry, dir);
	
	cout << cnt << "\n";
	
	return 0;
}
