/********************/
// BOJ 15685 드래곤 커브
// 핵심: 규칙 찾기 
/********************/
#include <stdio.h>
#include <string.h>	// memset

int n, x, y, d, g;	// 드래곤 커브 개수, 커브 시작점의 (x, y)좌표, 시작 방향, 세대 
int order_Idx;	// order 배열 크기 
int map[102][102];
int dx[] = {1, 0, -1, 0};	// right, up, left, down
int dy[] = {0, -1, 0, 1};
int order[1025];	// 해당 세대의 order를 저장하는 배열 

void draw_Dragon_Curve(void) {
	int push_Idx = order_Idx;	// 집어넣는 idx 
	
	// 역방향으로 읽으면서 dir++ 
	for(int i = order_Idx - 1; i >= 0; i--) {
		x += dx[(order[i] + 1) % 4];
		y += dy[(order[i] + 1) % 4];
		map[y][x]++;
		
		order[push_Idx++] = (order[i] + 1) % 4;
	}
	
	order_Idx = push_Idx;	// order 배열 크기 갱신 
}


int count_Square(void) {
	int cnt = 0;	// 사각형 개수 
	
	for(int j = 0; j < 100; j++) {
		for(int i = 0; i < 100; i++) {
			if(!map[j][i]) continue;
			
			// 꼭지점 모두 dragon curve 일부 
			if(map[j + 1][i] && map[j][i + 1] && map[j + 1][i + 1]) {
				cnt++;
			}
		}
	}
	
	return cnt;
}


int main(void) {
	scanf("%d", &n);
	
	for(int i = 0; i < n; i++) {
		scanf("%d %d %d %d", &x, &y, &d, &g);
		
		// 초기화 
		memset(order, -1, sizeof(order));
		order_Idx = 0;
		
		// 0세대 미리 작업 
		map[y][x]++;
		x += dx[d]; y += dy[d];
		map[y][x]++;
		order[order_Idx++] = d;
		
		// 1 ~ g세대까지 
		for(int j = 0; j < g; j++) {
			draw_Dragon_Curve();
		}
	}
	
	printf("%d\n", count_Square());
	
	return 0;
}
