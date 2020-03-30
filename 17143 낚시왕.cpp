/*******************/
// BOJ 17143 낚시왕
// 핵심: '동시에' 움직임
// 				=> 다른 지도에 움직임을 표시함으로서 이미 움직인 것들이
// 					 다음 것들에 영향을 주지 못하도록 함 
/*******************/
#include <stdio.h>
#include <string.h>
#define MAX 102

typedef struct shark {
	int speed, dir, size;
} shark;

int r, c, m, ans;	// 세로, 가로, 상어 수, 낚시왕이 잡은 상어 크기 합 
shark map[MAX][MAX];	// 상어가 들어있는 지도 
int dx[] = {0, 0, 1, -1};	// up, down, right, left
int dy[] = {-1, 1, 0, 0};

int changeDir(int dir) {
	// dx[dir]의 반대로 갈 수 있도록 만들어주는 함수
	 
	switch(dir) {
		case 0: return 1;
		case 1: return 0;
		case 2: return 3;
		case 3: return 2;
	}
}

int abs(int a) {
	return a < 0 ? -a : a;
}

void move(int time) {
	// 현재 time초일 때 전체 움직임
	
	// 1. 상어왕이 물고기를 잡음 
	for(int i = 0; i < r; i++) {
		if(map[i][time].size) {
			ans += map[i][time].size;
			map[i][time].size = 0;
			break;
		}
	}
	
	shark copied[MAX][MAX] = {0, };	// 새로운 지도 
	
	// 2. 모든 상어가 동시에 움직임 
	for(int y = 0; y < r; y++) {
		for(int x = 0; x < c; x++) {
			// 존재하지 않으면 통과 
			if(!map[y][x].size) continue;
			
			int speed = map[y][x].speed;	// 현재 상어의 속도 
			int size = map[y][x].size;	// 현재 상어의 크기 
			int dir = map[y][x].dir;	// 현재 상어가 향하는 방향 
			int dist = speed;	// 남은 거리 
		
			int mx = x + dist * dx[dir];	// 다음 위치 
			int my = y + dist * dy[dir];
			
			// 맨 처음에 왼쪽으로 향했을 때 
			if(mx < 0) {
				dist = -mx;
				mx = 0;
				dir = changeDir(dir);
				
				int go = dist % (c - 1);	// 맨마지막에 움직일 거리 관련 
				int dirOrder = dist / (c - 1);	// 맨마지막 방향 관련 
				
				// 방향 바꿔야 될 때 
				if(dirOrder % 2) {
					dir = changeDir(dir);
					mx = c - 1 - go;
				}
				else mx = go;
			}
			// 오른쪽으로 향했을 때 
			else if(mx >= c) {
				dist = mx - c + 1;
				mx = c - 1;
				dir = changeDir(dir);
				
				int go = dist % (c - 1);
				int dirOrder = dist / (c - 1);
				
				if(dirOrder % 2) {
					dir = changeDir(dir);
					mx -= (c - 1 - go);
				}
				else mx -= go;
			}
			// 위로 향했을 때 
			else if(my < 0) {
				dist = -my;
				my = 0;
				dir = changeDir(dir);
				
				int go = dist % (r - 1);
				int dirOrder = dist / (r - 1);
				
				if(dirOrder % 2) {
					dir = changeDir(dir);
					my = r - 1 - go;
				}
				else my = go;
			}
			// 아래로 향했을 때 
			else if(my >= r) {
				dist = my - r + 1;
				my = r - 1;
				dir = changeDir(dir);
				
				int go = dist % (r - 1);
				int dirOrder = dist / (r - 1);
				
				if(dirOrder % 2) {
					dir = changeDir(dir);
					my -= (r - 1 - go);
				}
				else my -= go;
			}
			
			// 상어가 없거나 작은 상어가 있으면 자리 차지 
			if(!copied[my][mx].size || copied[my][mx].size < size) {
				shark tmp = {speed, dir, size};
				copied[my][mx] = tmp;
			}
		}
	}
	
	memcpy(map, copied, sizeof(copied));	// 완성된 지도 복사 
}


int main(void) {
	scanf("%d %d %d", &r, &c, &m);
	
	for(int i = 0; i < m; i++) {
		int x, y, s, d, z;
		scanf("%d %d %d %d %d", &y, &x, &s, &d, &z);
		
		// 상어가 없거나 작은 상어가 있을 때 
		if(!map[--y][--x].size || map[y][x].size < z) {
			shark tmp = {s, --d, z};
			map[y][x] = tmp;
		}
	}
	
	for(int i = 0; i < c; i++) {
		move(i);
	}
	
	printf("%d\n", ans);

	return 0;
}
