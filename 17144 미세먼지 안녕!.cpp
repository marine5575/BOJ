#include <stdio.h>
#include <string.h>
#define MAX 51

typedef struct st {
	int x, y;
} pt;

int r, c, t;	// 세로, 가로, t초 뒤의 시간을 봄 
int map[MAX][MAX], copied[MAX][MAX];
int dx[] = {1, 0, -1, 0};	// right, down, left, up
int dy[] = {0, 1, 0, -1};
pt up, down;	// 위쪽, 아래쪽 공기청정기 

void aircondition(void) {
	// up과 down의 바람이 작동하는 함수
	
	int x = up.x + 1, y = up.y, dir = 0;	// 이전 좌표 (x, y), 현재 방향 
	map[y][x] = 0;	// 공기청정기에서 갓 나온 바람 
	
	// 반시계 방향 
	for(int i = 0; i < 4; i++) {
		while(1) {
			int mx = x + dx[dir];
			int my = y + dy[dir];
			
			// 범위 확인 
			if(mx < 0 || mx >= c || my < 0 || my >= r) break;
			// 한 바퀴 돌았음 
			if(mx == up.x && my == up.y) break;
			
			map[my][mx] = copied[y][x];
			x = mx; y = my;
		}
		
		dir = dir - 1 < 0 ? 3 : dir - 1;
	}
	
	// 시계 방향 
	x = down.x + 1;
	y = down.y;
	dir = 0;
	map[y][x] = 0;
	
	for(int i = 0; i < 4; i++) {
		while(1) {
			int mx = x + dx[dir];
			int my = y + dy[dir];
			
			// 범위 확인 
			if(mx < 0 || mx >= c || my < 0 || my >= r) break;
			// 한 바퀴 다 돌았음 
			if(mx == down.x && my == down.y) break;
			
			map[my][mx] = copied[y][x];
			x = mx; y = my;
		}
		
		dir = dir + 1 < 4 ? dir + 1 : 0;
	}
}

void spread_Dust(void) {
	// 미세먼지를 동시다발적으로 퍼뜨리는 함수 
	
	memcpy(copied, map, sizeof(map));	// 이전 좌표의 영향이 남으면 안되므로 
	
	for(int j = 0; j < r; j++) {
		for(int i = 0; i < c; i++) {
			
			for(int k = 0; k < 4; k++) {
				int mx = i + dx[k];
				int my = j + dy[k];
				
				// 범위 확인 & 공기청정기인지 확인 
				if(mx < 0 || mx >= c || my < 0 || my >= r || map[my][mx] == -1) continue;
				
				copied[my][mx] += map[j][i] / 5;
				copied[j][i] -= map[j][i] / 5;
			}
		}
	}
	
	memcpy(map, copied, sizeof(copied));	// 다시 정답으로 돌려놓기 
}


int main(void) {
	scanf("%d %d %d", &r, &c, &t);
	
	int airCnt = 0, timeCnt = 0;
	
	for(int j = 0; j < r; j++) {
		for(int i = 0; i < c; i++) {
			scanf("%d", &map[j][i]);
			
			if(map[j][i] == -1) {
				pt tmp = {i, j};
				
				if(!airCnt) {
					up = tmp;
					airCnt++;
				}
				else down = tmp;
			}
		}
	}
	
	while(timeCnt < t) {
		spread_Dust();
		aircondition();
		timeCnt++;
	}
	
	int sum = 0;	// 총 미세먼지 양 
	
	for(int j = 0; j < r; j++) {
		for(int i = 0; i < c; i++) {
			if(map[j][i] <= 0) continue;
			
			sum += map[j][i];
		}
	}
	
	printf("%d\n", sum);
	
	return 0;
}
