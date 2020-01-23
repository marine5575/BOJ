#include <iostream>

using namespace std;

int map[501][501], visited[501][501];
int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};
int maxi = -1;

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
			sum += dfs(nx, ny, cnt + 1);
			
			if(maxi < sum) maxi = sum;
			visited[ny][nx] = 0;
		}
	}
}


int main(void) {
	cin.tie(0);
	ios::sync_with_stdio(0);
	
	int n, m;
	cin >> n >> m;
	
	for(int j = 0; j < n; j++) {
		for(int i = 0; i < m; i++) {
			cin >> map[j][i];
		}
	}
	
	
	
	return 0;
}
