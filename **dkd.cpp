#include <iostream>
#include <cmath>	// abs
#include <queue>

using namespace std;

typedef struct ball {
	int rx, ry, bx, by;	// 빨간 공의 (x, y), 파란 공의 (x, y) 
}ball;

int map[11][11];	// map[j][i] = -1 or 0 or 1 : (i, j) 위치는 벽 or 길 or 구멍
int visited[11][11][11][11];	//	visited[rx][ry][bx][by] : 방문 여부 
int dx[4] = {0, 0, -1, 1}, dy[4] = {-1, 1, 0, 0};	// up, down, left, right 
int irx, iry, ibx, iby, hx, hy;	// 처음 (rx, ry), (bx, by), 구멍의 위치 (hx, hy) 
int cnt = 0, ans = 0;	// bfs 깊이, 정답 

queue<ball> q;	// bfs의 핵심 

void bfs(void) {
	// queue가 빌 때까지 
	while(!q.empty()) {
		int qLen = q.size();	// 원래 가지고 있던 이번 depth 소속 개수 
		
		// 갯수만큼 반복 
		while(qLen--) {
			// 현재 공들의 위치 & queue에서 빼기 
			ball cur = q.front(); q.pop();
			
			// 구멍에 빠졌을 때 
			if(cur.rx == hx && cur.ry == hy) {
				ans = cnt;
				return;
			}
			
			// 동서남북 다 가보기 
			for(int i = 0; i < 4; i++) {
				int rx = cur.rx, ry = cur.ry;
				int bx = cur.bx, by = cur.by;
				
				// 빨간 공 굴리기 
				while(1) {
					rx += dx[i]; ry += dy[i];
					
					if(map[ry][rx] == -1) {
						rx -= dx[i]; ry -= dy[i];
						break;
					}
					else if(map[ry][rx] == 1) break;
				}
				
				while(1) {
					bx += dx[i]; by += dy[i];
					
					if(map[by][bx] == -1) {
						bx -= dx[i]; by -= dy[i];
						break;
					}
					else if(map[by][bx] == 1) break;
				}
				
				if(map[by][bx] == 1) continue;
				
				if(rx == bx && ry == by) {
					switch(i) {
						case 0: {
							cur.ry > cur.by ? ry++ : by++;
							break;
						}
						case 1: {
							cur.ry < cur.by? ry-- : by--;
							break;
						}
						case 2: {
							cur.rx > cur.bx ? rx++ : bx++;
							break;
						}
						case 3: {
							cur.rx < cur.bx ? rx-- : bx--;
							break;
						}
					}
				}
				
				if(!visited[rx][ry][bx][by]) {
					ball next = {rx, ry, bx, by};
					q.push(next);
					visited[rx][ry][bx][by] = 1;
				}
			}
		}
		
		if(cnt == 10) {
			ans = -1;
			return;
		}
		cnt++;
	}
	
	ans = -1;
	return;
}


int main(void) {
	cin.tie(0);
	ios::sync_with_stdio(0);
	
	int n, m;
	char input;
	cin >> n >> m;
	
	for(int j = 0; j < n; j++) {
		for(int i = 0; i < m; i++) {
			cin >> input;
			
			switch(input) {
				case '#':	{
					map[j][i] = -1;
					break;
				}
				case '.': {
					map[j][i] = 0;
					break;
				}
				case 'R': {
					irx = i; iry = j;
					break;
				}
				case 'B': {
					ibx = i; iby = j;
					break;
				}
				case 'O': {
					hx = i; hy = j;
					map[j][i] = 1;
					break;
				}
			}
		}
	}
	
	ball init = {irx, iry, ibx, iby};
	q.push(init);
	visited[irx][iry][ibx][iby] = 1;
	bfs();
	
	cout << ans << "\n";
	
	return 0;
}
