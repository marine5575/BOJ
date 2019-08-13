/*
일반적인 dfs로 찾으면 시간 초과가 날 것이 보이는 문제
따라서 dfs + dp 로 풀어야 됨 
*/
#include <cstdio>

// 왼, 오, 아래, 위 
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

int map[501][501];	// 지도 
int dp[501][501];	// dp[i][j] = A : (j, i)를 A번 지나감 

int m, n;	// 세로, 가로 

int dfs(int x, int y) {
	int &ref = dp[y][x];	// (x, y)를 지나간 횟수
	// 도착 지점에 다다랐을 때 
	if(x == n - 1 && y == m - 1) return ref = 1;
	// 이미 다녀갔을 때 
	if(ref != -1) return ref; 
	
	int cnt = 0;	// 다녀간 횟수 세기 
	
	// 갈 수 있는 곳 찾아보기 
	for(int i = 0; i < 4; i++) {
		int mx = x + dx[i];	// x 후보 
		int my = y + dy[i];	// y 후보 
		
		// 범위 안에 들어가지 않는가? 
		if(mx < 0 || mx >= n || my < 0 || my >= m) continue;
		
		// 내려가는 형세인가? 
		if(map[y][x] > map[my][mx]) {
			cnt += dfs(mx, my);
		}
	}
	
	// 갱신 후 출력 
	return ref = cnt;
}


int main(void) {
	scanf("%d %d", &m, &n);
	
	for(int i = 0; i < m; i++) {
		for(int j = 0; j < n; j++) {
			scanf("%d", &map[i][j]);
			dp[i][j] = -1;	// 아직 다녀가지 않음을 표시 
		}
	}
	
	printf("%d\n", dfs(0, 0));
	
	return 0;
}
