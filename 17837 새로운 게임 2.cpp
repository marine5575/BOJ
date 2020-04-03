/********************/
// BOJ 17837 새로운 게임 2
// 핵심: 문제 파악 
/********************/
#include <stdio.h>
#include <stdlib.h>
#define MAX 	13
#define P_MAX 11

typedef struct p {
	int x, y, dir;
} p;
typedef struct plc {
	int color;
	int bunch[P_MAX];	// 올려져 있는 말 (bunch[0]: 바닥에 있는 말) 
	int size;	// 올려진 말의 개수 
} plc;

int n, k, playCnt;	// 체스판 크기, 말의 개수, 진행된 턴 
plc map[MAX][MAX];
p pawn[P_MAX];	// 말의 정보 
int dx[] = {1, -1, 0, 0};	// right, left, up, down
int dy[] = {0, 0, -1, 1};

int changeDir(int dir);
void white(int idx, int mx, int my);
void red(int idx, int mx, int my);
void blue(int i);
void play(void);


int main(void) {
	scanf("%d %d", &n, &k);
	for(int j = 0; j < n; j++) {
		for(int i = 0; i < n; i++) {
			scanf("%d", &map[j][i].color);
		}
	}
	for(int i = 0, x, y, d; i < k; i++) {
		scanf("%d %d %d", &y, &x, &d);
		x--; y--; d--;
		p tmp = {x, y, d};
		pawn[i] = tmp;
		map[y][x].bunch[map[y][x].size++] = i + 1;
	}
	
	for(playCnt = 1; playCnt <= 1000; playCnt++) {
		play();
	}
	printf("-1\n");
	
	return 0;
}


/********** FUNCTIONS ***********/

int changeDir(int dir) {
	// dir의 반대로 바꿔주는 함수
	
	switch(dir) {
		case 0: return 1;
		case 1: return 0;
		case 2: return 3;
		case 3: return 2;
	}
}

void white(int idx, int mx, int my) {
	// pawn[idx]가 흰색칸에 왔을 때 올려놓음
	
	int x = pawn[idx].x, y = pawn[idx].y;	// 현재 위치 
	int at = -1, sz = map[y][x].size;	// pawn[idx]가 있는 곳, 현재 위치에 있는 말 개수 
	
	// pawn[idx] 위에 있는 것들도 데려감 
	for(int i = 0; i < sz; i++) {
		// pawn[idx] 찾음 
		if(map[y][x].bunch[i] == idx + 1) at = i;
		// 아직 못 찾음 
		if(at == -1) continue;
		
		int tmpIdx = map[y][x].bunch[i] - 1;
		map[my][mx].bunch[map[my][mx].size++] = tmpIdx + 1;
		map[y][x].bunch[i] = 0;
		map[y][x].size--;
		pawn[tmpIdx].x = mx; pawn[tmpIdx].y = my;
	}
	
	// 종료 조건 체크 
	if(map[my][mx].size >= 4) {
		printf("%d\n", playCnt);
		exit(0);
	}
}

void red(int idx, int mx, int my) {
	// pawn[idx]가 빨강에 왔을 때 뒤집어서 올려놓음
	
	int x = pawn[idx].x, y = pawn[idx].y;	// 현재 위치 
	int sz = map[y][x].size, i;	// 현재 위치에 있는 말들 개수 
	
	// pawn[idx] 위에 있는 애들도 뒤집어서 올려놓음 
	for(i = sz - 1; i >= 0; i--) {
		// pawn[idx] 찾음 => 이제 끝 
		if(map[y][x].bunch[i] == idx + 1) break;
		
		int tmpIdx = map[y][x].bunch[i] - 1;
		map[my][mx].bunch[map[my][mx].size++] = tmpIdx + 1;
		map[y][x].bunch[i] = 0;
		map[y][x].size--;
		pawn[tmpIdx].x = mx; pawn[tmpIdx].y = my;
	}
	// pawn[idx]도 올려놓기 
	map[my][mx].bunch[map[my][mx].size++] = map[y][x].bunch[i];
	map[y][x].bunch[i] = 0;
	map[y][x].size--;
	pawn[idx].x = mx; pawn[idx].y = my;
	
	// 종료 조건 체크 
	if(map[my][mx].size >= 4) {
		printf("%d\n", playCnt);
		exit(0);
	}
}

void blue(int i) {
	// pawn[i]가 파란칸에 왔을 때 방향을 바꿔봄 
	
	pawn[i].dir = changeDir(pawn[i].dir);
	
	int mx = pawn[i].x + dx[pawn[i].dir];
	int my = pawn[i].y + dy[pawn[i].dir];
	
	// blue 조건 충족 => 이제 더이상 움직일 수 x 
	if(mx < 0 || mx >= n || my < 0 || my >= n || map[my][mx].color == 2) return;
	
	// white
	if(map[my][mx].color == 0) white(i, mx, my);
	// red
	else red(i, mx, my);
}

void play(void) {
	// 모든 말을 움직이는 함수
	
	for(int i = 0; i < k; i++) {
		int x = pawn[i].x, y = pawn[i].y, dir = pawn[i].dir;
		int mx = x + dx[dir];
		int my = y + dy[dir];
		
		// blue 조건 충족 
		if(mx < 0 || mx >= n || my < 0 || my >= n || map[my][mx].color == 2) {
			blue(i);
		}
		// white 
		else if(map[my][mx].color == 0) white(i, mx, my);
		// red
		else red(i, mx, my);
	}
}
