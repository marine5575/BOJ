/******************/
// BOJ 9019 DSLR
// 핵심: BFS + 경로추적(DFS) 
/******************/
#include <stdio.h>
#include <string.h>
#include <queue>
#define MAX ((int)1e4 + 1)

using namespace std;

typedef struct pt {
	int prev;
	char order;
} pt;

int tc, a, b;	// 테스트 케이스 개수, 원래 값, 원하는 값 
pt path[MAX];	// 경로 

void input_Data(void) {
	scanf("%d %d", &a, &b);
}

inline int operator_L(int num) {
	int first = num / 1000;
	return (num - first * 1000) * 10 + first;
}

inline int operator_R(int num) {
	int rest = num / 10;
	int last = num % 10;
	
	return rest + last * 1000;
}

void bfs(void) {
	// a에서 시작해서 DSLR 규칙을 따라 b가 되는 최소 명령어 나열을 찾는 함수
	
	char visited[MAX] = {0, };
	queue<int> q;
	q.push(a);
	visited[a] = 1;
	
	while(!q.empty()) {
		int cur = q.front(); q.pop();
		
		// 찾았으면 끝냄 
		if(cur == b) return;
		
		int next = (2 * cur) % 10000;	// 'D'
		
		// 안 들렀으면 
		if(!visited[next]) {
			q.push(next);
			visited[next] = 1;
			path[next].prev = cur;
			path[next].order = 'D';
			
			// 찾았으면 끝냄 
			if(next == b) return;
		}
		
		next = cur - 1 < 0 ? 9999 : cur - 1;	// 'S'
		// 안 들렀으면 
		if(!visited[next]) {
			q.push(next);
			visited[next] = 1;
			path[next].prev = cur;
			path[next].order = 'S';
			
			// 찾았으면 끝냄 
			if(next == b) return;
		}
		
		next = operator_L(cur);	// 'L'
		// 안 들렀으면 
		if(!visited[next]) {
			q.push(next);
			visited[next] = 1;
			path[next].prev = cur;
			path[next].order = 'L';
			
			// 찾았으면 끝냄 
			if(next == b) return;
		}
		
		next = operator_R(cur);	// 'R'
		// 안 들렀으면 
		if(!visited[next]) {
			q.push(next);
			visited[next] = 1;
			path[next].prev = cur;
			path[next].order = 'R';
			
			// 찾았으면 끝냄 
			if(next == b) return;
		}
	}
}

void dfs(int x) {
	// x를 들러 출력하는 함수
	
	// 맨 처음 값으로 돌아왔음 
	if(x == a) return;
	
	dfs(path[x].prev);
	
	printf("%c", path[x].order); 
}


int main(void) {
	scanf("%d", &tc);
	
	while(tc--) {
		memset(path, 0, sizeof(path));	// 초기화 
		input_Data();
		bfs();
		dfs(b);	// 경로 출력 
		printf("\n");
	}
	
	return 0;
}
