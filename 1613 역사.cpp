/*****************/
// BOJ 1613 역사
// 핵심: DFS/BFS 순회 + F-W(모든 노드에서 출발) 
/*****************/
#include <stdio.h>
#include <vector>
#define MAX 402

using namespace std;

int n, k, s;	// 사건 개수, 사건 전후의 개수, 전후 관계를 알고 싶은 사건 쌍의 개수 
int visited[MAX];
char connect[MAX][MAX];	// connect[i][j] = i번 -> j번이면 -1, j번 -> i번이면 1 
vector<int> map[MAX];	// map[i] = {i번 다음에 일어난 사건들}

void input_Data(void) {
	scanf("%d %d", &n, &k);
	
	for(int i = 0, a, b; i < k; i++) {
		scanf("%d %d", &a, &b);
		
		map[a].push_back(b);
	}
}

void dfs(int x, int origin, int color) {
	// 이번에 x를 들리는 것이고, origin에서 시작되었으며
	// 방문 체크할 때 color로 칠함 
	
	visited[x] = color;
	
	for(int i = 0; i < map[x].size(); i++) {
		int num = map[x][i];	// 이번에 살펴볼 사건 번호 
		
		// 이미 방문함 or 이전 노드에서 사건 상관 관계 이미 봄 
		if(visited[num] == color || connect[origin][num]) continue;
		
		connect[origin][num] = -1;	// origin -> num 
		connect[num][origin] = 1;	// num -> origin
		
		dfs(num, origin, color);
	}
}

void sol(void) {
	// 모든 노드에서 출발해봄 
	for(int i = 1; i <= n; i++) {
		dfs(i, i, i);
	}
	
	scanf("%d", &s);
	
	for(int i = 0, from, to; i < s; i++) {
		scanf("%d %d", &from, &to);
		printf("%d\n", connect[from][to]);
	}
}


int main(void) {
	input_Data();
	sol();
	
	return 0;
} 
