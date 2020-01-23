#include <iostream>

using namespace std;

int map[501][501], visited[501][501];
int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};
int n, m, maxi = -1;

int dfs(int x, int y, int cnt) {
	if(cnt == 4) {
		return map[y][x];
	}
	 
	int sum = 0;
	
	for(int i = 0; i < 4; i++) {
		int nx = x + dx[i], ny = y + dy[i];
		
		if(nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
		
		if(!visited[ny][nx]) {
			visited[ny][nx] = 1;
			
			int cur = map[y][x] + dfs(nx, ny, cnt + 1);
			
			if(sum < cur) sum = cur;
			visited[ny][nx] = 0;
		}
	}
}

int fuck(int x, int y) {
	int tmp, sum = 0;
	
	// ㅗ
	if(x >= 1 && y >= 1 && x < m - 1  && y < n) {
		tmp = map[y][x] + map[y - 1][x] + map[y][x - 1] + map[y][x + 1];
		
		if(sum < tmp) sum = tmp;
	}
	
	// ㅓ
	if(x >= 1 && y >= 1 && y < n - 1 && x < m) {
		tmp = map[y][x] + map[y][x - 1] + map[y - 1][x] + map[y + 1][x];
		
		if(sum < tmp) sum = tmp;
	}
	
	// ㅜ
	if(x >= 1 && y >= 0 && x < m - 1 && y < n - 1) {
		tmp = map[y][x] + map[y][x - 1] + map[y][x + 1] + map[y + 1][x];
		
		if(sum < tmp) sum = tmp;
	}
	
	// ㅏ
	if(y >= 1 && x >= 0 && x < m - 1 && y < n - 1) {
		tmp = map[y][x] + map[y][x + 1] + map[y - 1][x] + map[y + 1][x];
		
		if(sum < tmp) sum = tmp;
	}
	
	return sum;
}


int main(void) {
	cin.tie(0);
	ios::sync_with_stdio(0);
	
	cin >> n >> m;
	
	for(int j = 0; j < n; j++) {
		for(int i = 0; i < m; i++) {
			cin >> map[j][i];
		}
	}
	
	
	
	return 0;
}
