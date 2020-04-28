/**********************/
// BOJ 1405 미친 로봇
// 핵심: DFS 
/**********************/
#include <stdio.h>
#define MAX 40

int n;	// 이동 횟수 
int dx[] = {1, -1, 0, 0};	// 동서남북 
int dy[] = {0, 0, 1, -1};
char visited[MAX][MAX];	// 중복 방문 방지 
double prob[5];	// 동서남북
double ans;	// 단순 이동 확률 

void input_Data(void) {
	scanf("%d", &n);
	
	for(int i = 0, t; i < 4; i++) {
		scanf("%d", &t);
		prob[i] = (double)t / 100;
	}
}

void dfs(int x, int y, int cnt, double prevProb) {
	// 직전에 들렀던 곳 x, y임 
	// 직전에 cnt만큼 로봇이 움직였음, 직전의 확률이 prevProb 
	
	// 다 움직였음 
	if(cnt >= n) {
		ans += prevProb;	// 확률 덧셈 
		return;
	}
	
	for(int i = 0; i < 4; i++) {
		int mx = x + dx[i];
		int my = y + dy[i];
		
		// 갈 확률 제로 or 이미 들렀던 곳임 
		if(prob[i] == 0.0 || visited[my][mx]) continue;
		
		visited[my][mx] = 1;
		dfs(mx, my, cnt + 1, prevProb * prob[i]);
		visited[my][mx] = 0;
	}
}


int main(void) {
	input_Data();
	visited[n][n] = 1;	// 시작지점 방문 체크 
	dfs(n, n, 0, 1.0);
	
	printf("%.9lf\n", ans);
	
	return 0;
}
