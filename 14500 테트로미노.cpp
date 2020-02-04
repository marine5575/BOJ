/**********************/
// BOJ 14500
// 핵심: DFS와 그외의 경우
// ㅓ, ㅗ, ㅜ, ㅏ만 DFS로 풀 수 없었음
// 깊게 들어가서 찾을 수 있는 미로라면
// DFS 쓰는 것을 고려해보자 
/**********************/
#include <iostream>

using namespace std;

int map[501][501], visited[501][501];	// map, 방문한 곳 
int dx[4] = {0, 0, -1, 1};	// up, down, left, right
int dy[4] = {-1, 1, 0, 0};	// up, down, left, right
int n, m, maxi = -1;	// width, height, 최대값 

int dfs(int x, int y, int cnt) {
	// 4번 다 돌았는가?	<- 0번부터 시작 
	if(cnt == 3) {
		return map[y][x];
	}
	 
	int sum = 0;	// dfs에서의 최대값 
	
	// 동서남북 들림 
	for(int i = 0; i < 4; i++) {
		int nx = x + dx[i], ny = y + dy[i];	// 들릴 (x, y) 좌표 
		
		// 범위 안에 들어와있는가? 
		if(nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
		
		// 들린 적이 없는가? 
		if(!visited[ny][nx]) {
			// 방문 체크 
			visited[ny][nx] = 1;
			
			int cur = map[y][x] + dfs(nx, ny, cnt + 1);	// 지금까지의 합 
			
			// 최대값 갱신 
			if(sum < cur) sum = cur;
			// 방문 해제 
			visited[ny][nx] = 0;
		}
	}
	
	return sum;
}

int fuck(int x, int y) {
	int tmp, sum = 0;	// 임시 저장, 예외의 최대값 
	
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
	
	for(int j = 0; j < n; j++) {
		for(int i = 0; i < m; i++) {
				// 방문 체크 
				visited[j][i] = 1;
				int tmpDFS = dfs(i, j, 0), tmpFuck = fuck(i, j);	// dfs의 최대값, fuck의 최대값 
				// 방문 해제 
				visited[j][i] = 0;
				
				// 최대값 갱신 
				if(maxi < tmpDFS) maxi = tmpDFS;
				if(maxi < tmpFuck) maxi = tmpFuck;
		}
	}
	
	cout << maxi << "\n";
	
	return 0;
}
