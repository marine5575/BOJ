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
			
			// 빨간 공이 구멍에 빠졌을 때 => success
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
					rx += dx[i]; ry += dy[i];	// up, down, left, right
					
					// 벽과 겹칠 경우 
					if(map[ry][rx] == -1) {
						rx -= dx[i]; ry -= dy[i];
						break;
					}
					// 구멍에 빠졌을 경우 
					else if(map[ry][rx] == 1) break;
				}
				
				// 파란 공 굴리기 
				while(1) {
					bx += dx[i]; by += dy[i];	// up, down, left, right
					
					// 벽과 겹칠 경우 
					if(map[by][bx] == -1) {
						bx -= dx[i]; by -= dy[i];
						break;
					}
					// 구멍에 빠졌을 경우
					else if(map[by][bx] == 1) break;
				}
				
				// 파란 공에 구멍에 빠짐 => game over 
				if(map[by][bx] == 1) continue;
				
				// 빨간 공과 파란 공이 겹침 
				if(rx == bx && ry == by) {
					// 누가 더 멀리서 왔나? (빨간 공 기준) 
					switch(i) {
						// up
						case 0: {
							// 빨간 공이 더 멀리서 왔나? 
							cur.ry > cur.by ? ry++ : by++;
							break;
						}
						// down
						case 1: {
							cur.ry < cur.by? ry-- : by--;
							break;
						}
						// left
						case 2: {
							cur.rx > cur.bx ? rx++ : bx++;
							break;
						}
						// right
						case 3: {
							cur.rx < cur.bx ? rx-- : bx--;
							break;
						}
					}
				}
				
				// 온 적이 없는가? 
				if(!visited[rx][ry][bx][by]) {
					ball next = {rx, ry, bx, by};	// 다음 위치 
					q.push(next);
					visited[rx][ry][bx][by] = 1;	// 방문 체크 
				}
			}
		}
		
		// 10번 안에 찾진 못했움.. 
		if(cnt == 10) {
			ans = -1;
			return;
		}
		cnt++; 
	}
	
	ans = -1;	// 찾지도 못하고 queue가 끝남 
	return;
}


int main(void) {
	cin.tie(0);
	ios::sync_with_stdio(0);
	
	int n, m;	// 세로, 가로 
	char input;
	cin >> n >> m;
	
	for(int j = 0; j < n; j++) {
		for(int i = 0; i < m; i++) {
			cin >> input;
			
			switch(input) {
				// 벽 
				case '#':	{
					map[j][i] = -1;
					break;
				}
				// 길 
				case '.': {
					map[j][i] = 0;
					break;
				}
				// 빨간 공 
				case 'R': {
					irx = i; iry = j;
					break;
				}
				// 파란 공 
				case 'B': {
					ibx = i; iby = j;
					break;
				}
				// 구멍 
				case 'O': {
					hx = i; hy = j;
					map[j][i] = 1;
					break;
				}
			}
		}
	}
	
	// queue 초기화 
	ball init = {irx, iry, ibx, iby};
	q.push(init);
	visited[irx][iry][ibx][iby] = 1;
	bfs();
	
	cout << ans << "\n";
	
	return 0;
}
