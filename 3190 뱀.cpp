#include <iostream>
#include <queue>
#define MAX 101

using namespace std;

typedef struct changeTime {
	int t;	// t초가 끝난 직후 
	char turn;	// turn = D or L : (오른쪽 or 왼쪽)으로 90도 회전 
} cT;
typedef struct point {
	int x, y;	// (x, y) 좌표 
} pt;

int n, hx, hy;	// map의 크기, 머리의 (x, y)좌표 
int cnt = 0;	// 흘러간 시간
int map[MAX][MAX];	// map
int dx[4] = {0, 0, -1, 1};	// up, down, left, right
int dy[4] = {-1, 1, 0, 0};	// 이하 동문 
queue<cT> cDir;	// 바꿀 방향들 
queue<pt> snake;	// 뱀 

// 방향 바꾸기 
int changeDir(int dir, char turn) {
	// 왼쪽으로 90도 회전 
	if(turn == 'L') {
		switch(dir) {
			// up -> left
			case 0: return 2;
			// down -> right
			case 1: return 3;
			// left -> down
			case 2: return 1;
			// right -> up
			case 3: return 0;
		}
	}
	// 오른쪽으로 90도 회전 
	else {
		switch(dir) {
			// up -> right
			case 0: return 3;
			// down -> left
			case 1: return 2;
			// left -> up
			case 2: return 0;
			// right -> down
			case 3: return 1;
		}
	}
}


int main(void) {
	cin.tie(0);
	ios::sync_with_stdio(0);
	
	int apple, nDir;	// 사과의 개수, 방향 전환 횟수 
	char c;	// 방향전환 방향 
	
	cin >> n >> apple;
	
	// 초기화 
	map[0][0] = 1;
	pt head = {0, 0};
	snake.push(head);
	
	// 사과 놓기 
	for(int i = 0, y, x; i < apple; i++) {
		cin >> y >> x;
		
		map[y - 1][x - 1] = 2;
	}
	
	cin >> nDir;
	
	// 방향 전환들 저장 
	for(int i = 0, x; i < nDir; i++) {
		cin >> x >> c;
		
		cT tmp = {x, c};
		cDir.push(tmp);
	}
	
	int dir = 3;	// 방향
	// 다음 방향 
	cT next = cDir.front(); cDir.pop();
	
	while(1) {
		// 방향 전환 시간이 지났나? 
		if(next.t == cnt) {
			dir = changeDir(dir, next.turn);	// 방향 바꿈 
			
			// 바꿀 방향 남아있나? 
			if(!cDir.empty()) {
				next = cDir.front();
				cDir.pop();
			}
		}
		
		int curx = hx + dx[dir], cury = hy + dy[dir];	// 현재 (x, y) 
		
		// 벽에 부딪혔는가? 
		if(curx < 0 || curx >= n || cury < 0 || cury >= n) break;
		// 몸통에 부딪혔는가? 
		if(map[cury][curx] == 1) break;
		
		// 일단 갈 수 있으니 머리 저장 
		head = {curx, cury};
		snake.push(head);
		
		// 사과가 있을 때 -> 머리만 늘림 
		if(map[cury][curx] == 2) {
			hx = curx;
			hy = cury;
			map[hy][hx] = 1;	// 머리 표시 
		}
		// 그냥 길일 때 -> 꼬리 말고 머리 늘리고 
		else {
			// 꼬리 꺼냄 
			pt tmp = snake.front(); snake.pop();
			int tx = tmp.x, ty = tmp.y;
			
			map[ty][tx] = 0;	// 꼬리 말기 
			hx = curx; hy = cury;	// 머리 갱신 
			map[hy][hx] = 1;
		}
		
		cnt++;	// 1초 지남 
	}
	
	cout << cnt + 1 << "\n";
	
	return 0;
} 
