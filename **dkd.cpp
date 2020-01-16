#include <iostream>
#include <cmath>
#include <queue>

using namespace std;

typedef struct ball {
	int rx, ry, bx, by;
}ball;

int map[11][11], visited[11][11][11][11];
int dx[4] = {0, 0, -1, 1}, dy[4] = {-1, 1, 0, 0};
int irx, iry, ibx, iby, hx, hy;
int cnt = 0, ans = 0;

queue<ball> q;

void bfs(void) {
	while(!q.empty()) {
		int qLen = q.size();
		
		while(qLen--) {
			ball cur = q.front(); q.pop();
			
			for(int i = 0; i < 4; i++) {
				int rx = cur.rx, ry = cur.ry;
				int bx = cur.bx, by = cur.by;
				
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
					q.push({rx, ry, bx, by});
					
				}
			}
		}
	}
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
	
	q.push({irx, iry, ibx, iby});
	
	
	
	return 0;
}
