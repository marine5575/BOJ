/************************/
// BOJ 9466 텀 프로젝트
// 핵심: DFS, BFS & 이미 살펴본 루트는 다시 보지 않도록 
/************************/

// 1. DFS (3MB, 800ms) 
// 		=> 방문 배열, 검사 완료 배열을 따로 만들어 한 번 살펴본
// 			 루트는 재방문할 수 없게 만듬 
// 출처; https://jaimemin.tistory.com/674
#if 0

#include <stdio.h>
#include <string.h>
#define MAX ((int)1e5 + 2)

int tc, n, team;	// 테스트 케이스 개수, 학생 수, 팀에 속한 학생 수 
int select[MAX];	// 학생들이 고른 학생 번호 
char done[MAX], visited[MAX];	// 검사 완료, 방문 배열 

void input_Data(void) {
	scanf("%d", &n);
	
	for(int i = 1; i <= n; i++) {
		scanf("%d", &select[i]);
	}
}

void dfs(int x) {
	// x를 방문하고 연결된 노드를 방문하는 함수
	
	visited[x] = 1;	// 방문 체크 
	
	int next = select[x];	// 다음 살펴볼 곳 
	
	// 아직 방문 안함 => 방문하러감 
	if(!visited[next]) dfs(next);
	// 방문 했음 & 아직 검사 안함 => 이 루트 안에서 사이클 발생 
	else if(!done[next]) {
		team++;	// 자기 자신 
		
		// 연결되어 있는 노드 세기 
		for(int i = next; i != x; i = select[i]) {
			team++;
		}
	}
	
	done[x] = 1;	// 검사 체크 
}

int sol(void) {
	team = 0;	// 초기화 
	
	for(int i = 1; i <= n; i++) {
		// 아직 방문 안함 
		if(visited[i]) continue;
		
		dfs(i);
	}
	
	return n - team;
}


int main(void) {
	scanf("%d", &tc);
	
	while(tc--) {
		memset(done, 0, sizeof(done));
		memset(visited, 0, sizeof(visited));
		
		input_Data();
		printf("%d\n", sol());
	}
	
	return 0;
}
#endif

// 2. DFS (1.6MB, 800ms) => 사이클 시작점 전까지는 사이클이 아닌 것들
// 													한마디로 굴렁쇠에 막대 붙여도 막대는 막대
#if 0

#include <stdio.h>
#include <string.h>
#define MAX ((int)1e5 + 2)

int tc, n, notTeam;	// 테스트 케이스 개수, 학생 수, 팀에 속하지 못한 수 
int select[MAX];	// 원하는 학생 번호 
char visited[MAX];	// 방문 여부 

void input_Data(void) {
	scanf("%d", &n);
	
	for(int i = 1; i <= n; i++) {
		scanf("%d", &select[i]);
	}
}

int sol(void) {
	notTeam = 0;	// 초기화 
	
	for(int i = 1; i <= n; i++) {
		// 이미 방문했다면 통과 
		if(visited[i]) continue;
		
		int start = i;	// 사이클 시작 지점 
		
		// 사이클 발견할 때까지 
		while(!visited[start]) {
			visited[start] = 1;
			start = select[start];
		}
		
		int notCycle = i;	// 사이클 아닌 지점 
		
		while(start != notCycle) {
			notTeam++;
			notCycle = select[notCycle];
		}
	}
	
	return notTeam;
}


int main(void) {
	scanf("%d", &tc);
	
	while(tc--) {
		memset(visited, 0, sizeof(visited));
		
		input_Data();
		printf("%d\n", sol());
	}
	
	return 0;
}
#endif

// 3. BFS (2MB, 760ms)
// 		=> 막대에 연결된 막대만 세는 코드
#if 0

#include <stdio.h>
#include <string.h>
#include <queue>
#define MAX ((int)1e5 + 2)

using namespace std;

int tc, n, notTeam;	// 테스트 케이스 개수, 학생 수, 팀에 속하지 못한 수 
int out[MAX], in[MAX];	// 원하는 학생 번호, 지목받은 횟수 
queue<int> q;	// 지목 받지 못한 학생을 담고 있음 

void input_Data(void) {
	scanf("%d", &n);
	
	for(int i = 1; i <= n; i++) {
		scanf("%d", &out[i]);
		in[out[i]]++;
	}
}

void init(void) {
	notTeam = 0;	// 초기화 
	
	for(int i = 1; i <= n; i++) {
		// 난 지목받았는데ㅎ; 
		if(in[i]) continue;
		
		q.push(i);
	}
}

int sol(void) {
	init();
	
	while(!q.empty()) {
		int cur = q.front(); q.pop();	// 현재 위치 
		notTeam++;	// 나는 절대 사이클 이룰리가 없음 
		
		int next = out[cur];
		
		// 막대인가? (굴렁쇠 아님)
		if(--in[next] <= 0) q.push(next);
	}
	
	return notTeam;
}


int main(void) {
	scanf("%d", &tc);
	
	while(tc--) {
		memset(in, 0, sizeof(in));
		
		input_Data();
		
		printf("%d\n", sol());
	}
	
	return 0;
}
#endif
