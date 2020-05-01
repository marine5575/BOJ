/*******************/
// <<< 한참 해멤 >>> 
// BOJ 2933 미네랄
// 핵심: Flood Fill & 문제 파악
// 			 => 각 '열'의 맨 아래 부분 중 하나가 떨어짐
// 			 => 몽땅 찾아볼 것 
/*******************/
#include <stdio.h>
#define MAX 110

int r, c, n;	// 동굴의 세로, 가로, 막대 던진 횟수 
int rod[MAX];	// 던진 높이 
int dx[] = {1, 0, -1, 0};	// right, down, left, up
int dy[] = {0, 1, 0, -1};
int visited[MAX][MAX];	// 묶어 놓은 그룹 
char map[MAX][MAX];

void input_Data(void) {
	scanf("%d %d", &r, &c);
	
	for(int j = 1; j <= r; j++) {
		scanf(" %s", &map[j][1]);
	}
	
	scanf("%d", &n);
	
	for(int i = 0; i < n; i++) {
		scanf("%d", &rod[i]);
	}
}

void throw_Rod(int h, int turn) {
	// h 높이에 turn(0: L->R / 1: R->L) 방향으로 던질 때 
	
	// L -> R
	if(!turn) {
		for(int w = 1; w <= c; w++) {
			// 빈칸일 때 
			if(map[h][w] == '.') continue;
			
			map[h][w] = '.';
			break;
		}
	}
	// R -> L
	else {
		for(int w = c; w > 0; w--) {
			// 빈칸일 때 
			if(map[h][w] == '.') continue;
			
			map[h][w] = '.';
			break;
		}
	}
}

void dfs(int x, int y, int color) {
	// (x, y)에 도착해서 color로 visited를 칠하는 함수
	
	visited[y][x] = color;
	
	for(int i = 0; i < 4; i++) {
		int mx = x + dx[i];
		int my = y + dy[i];
		
		// 범위 확인 
		if(mx <= 0 || mx > c || my <= 0 || my > r) continue;
		// 빈칸일 때 or 이미 들렀을 때 
		if(map[my][mx] == '.' || visited[my][mx] == color) continue;
		
		dfs(mx, my, color);
	} 
}

int grouping(int color) {
	// 첫 시작을 color로 해서 바닥에 붙어있는 미네랄 클러스터 표시 
	
	int originalColor = color;	// 맨 처음 색깔 
	
	for(int i = 1; i <= c; i++) {
		// 빈 곳일 때 
		if(map[r][i] == '.') continue;
		// 이미 들렀을 때 
		if(visited[r][i] >= originalColor) continue;
		
		dfs(i, r, color++);
	}
	
	return color;
}

void clean_Map(int start) {
	// visited[j][i] == start 인 것부터 그룹임
	
	int moveHeight = r;	// 움직일 수 있는 최소 높이
	
	// 최소 높이 갱신 
	for(int j = r; j >= 1; j--) {
		for(int i = 1; i <= c; i++) {
			// 빈칸일 때 or 바닥에 붙어있는 클러스터 소속일 때 
			if(map[j][i] == '.' || visited[j][i] >= start) continue;
			
			int k;
			for(k = j + 1; k <= r; k++) {
				// 바닥에 붙어있는 클러스터 소속이 아닌 미네랄일 때 
				if(map[k][i] == 'x' && visited[k][i] >= start) break;
			}
			
			// 최소값 갱신 
			if(moveHeight > k - j - 1) moveHeight = k - j - 1;
		}
	}
	
	// 옮기는 함수 
	for(int j = r; j >= 1; j--) {
		for(int i = 1; i <= c; i++) {
			// 빈칸일 때 or 바닥에 붙어있는 클러스터 소속일 때 
			if(map[j][i] == '.' || visited[j][i] >= start) continue;
			
			map[j + moveHeight][i] = map[j][i];
			map[j][i] = '.';
		}
	}
}

void print_Map(void) {
	for(int j = 1; j <= r; j++) {
		printf("%s\n", &map[j][1]);
	}
	printf("\n");
}

void sol(void) {
	int color = 1;	// 칠할 색깔 
	
	for(int i = 0; i < n; i++) {
		throw_Rod(r - rod[i] + 1, i & 1);	// 막대 던지기 
		
		int prevColor = color;	// 맨 처음 색칠하는 색깔 
		color = grouping(color);
		
		clean_Map(prevColor);	// 중력받아 떨어지는 미네랄들 
	}
	
	print_Map();
}


int main(void) {
	input_Data();
	sol();
	
	return 0;
}
