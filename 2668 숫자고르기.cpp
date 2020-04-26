/************************/
// BOJ 2668 숫자 고르기
// 핵심: DFS + 사이클 
/************************/

// 1. DFS 방법 응용(done 배열 이용) 
#if 0

#include <stdio.h>
#define MAX 101

int n, team;	// 입력되는 숫자 개수, cycle을 이루는 숫자 개수 
int arr[MAX], ans[MAX];	// input, ans[i] = 1: i는 사이클을 이루는 숫자 
char visited[MAX], done[MAX];	// 방문 체크, 탐색 완료 체크 

void input_Data(void) {
	scanf("%d", &n);
	
	for(int i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
	}
}

void dfs(int x) {
	// x번을 방문한 후에 탐색 
	
	visited[x] = 1;
	int next = arr[x];	// 연결된 곳 
	
	// 아직 방문 안했으면 방문 
	if(!visited[next]) dfs(next);
	// 방문 이미 함 & 아직 탐색 완료는 안 함 => cycle 발생 
	else if(!done[next]) {
		team++;
		ans[x] = 1;
		
		for(int i = next; i != x; i = arr[i]) {
			team++;
			ans[i] = 1;
		}
	}
	
	done[x] = 1;	// 탐색 완료 표시 
}

void sol(void) {
	for(int i = 1; i <= n; i++) {
		// 이미 방문한 적이 있음 
		if(visited[i]) continue;
		
		dfs(i);
	}
	
	printf("%d\n", team);
	
	for(int i = 1; i <= n; i++) {
		if(ans[i]) printf("%d\n", i);
	}
}


int main(void) {
	input_Data();
	sol();
	
	return 0;
}
#endif

// 2. 굴렁쇠에 붙은 막대를 빼는 방법
#if 0

#include <stdio.h>
#define MAX 101

int n, notTeam;	// 들어오는 수 개수, 사이클을 이루지 못하는 것들 개수 
int arr[MAX];
char visited[MAX], ans[MAX];

void input_Data(void) {
	scanf("%d", &n);
	
	for(int i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
	}
}

void sol(void) {
	for(int i = 1; i <= n; i++) {
		// 이미 살펴본 곳은 볼 필요 없음 
		if(visited[i]) continue;
		
		int start = i;	// 살펴볼 곳 
		
		// 안 살펴본 곳들만 보기 
		while(!visited[start]) {
			visited[start] = ans[start] = 1;
			start = arr[start];
		}
		
		int notCycle = i;	// 사이클을 이루지 못하는 곳 
		
		// 사이클을 이루는 곳들을 아직 만나지 않음 
		while(notCycle != start) {
			ans[notCycle] = 0;	// 빼기 
			notTeam++;
			notCycle = arr[notCycle];
		}
	}
	
	printf("%d\n", n - notTeam);
	
	for(int i = 1; i <= n; i++) {
		if(ans[i]) printf("%d\n", i);
	}
}


int main(void) {
	input_Data();
	sol();
	
	return 0;
}
#endif
