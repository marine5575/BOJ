/**********************/
// BOJ 5014 스타트링크
// 핵심: BFS or 단순 구현
// 			 => 항상 범위 체크 먼저하고 배열 살피기(runtime error 방지) 
/**********************/

// 1. BFS로 푼 것 => 8ms
#if 0

#include <stdio.h>
#include <queue>
#define MAX ((int)1e6 + 1)

using namespace std;

int f, s, g, u, d;	// 최고층, 시작층, 도착층, u칸 올라감, d칸 내려감 
int visited[MAX];	// visited[i] = i번에 왔을 떄 버튼을 최소로 누른 횟수 

void input_Data(void) {
	scanf("%d %d %d %d %d", &f, &s, &g, &u, &d);
}

int bfs(void) {
	// s층부터 g층까지 bfs로 버튼을 최소한 눌러 도착하게 하는 함수
	
	// 2. 시작 위치 담기 
	queue<int> q;
	q.push(s);
	visited[s] = 1;
	
	// 3. 반복문 
	while(!q.empty()) {
		int cur = q.front(); q.pop();	// 현재 위치 
	
		
		// 도착했음
		if(cur == g) return visited[cur] - 1; 
		
		int up = cur + u;	// 올라갔다고 가정했을 떄 
		int down = cur - d;	// 내려갔다고 가정했을 떄 
		
		// 경험한적 없음 & 최고층보다 아래거나 같음 
		if(up <= f && !visited[up]) {
			q.push(up);
			visited[up] = visited[cur] + 1;
		}
		// 경험한적 없음 & 최하층보다 위거나 같음 
		if(down > 0 && !visited[down]) {
			q.push(down);
			visited[down] = visited[cur] + 1;
		}
	}
	
	// 4. 실패할 경우 
	return -1;
}


int main(void) {
	input_Data();
	
	// 올라갈 수 없는데 위에 있음 
	if(u == 0 && g > s) {
		printf("use the stairs\n");
		return 0;
	}
	// 내려갈 수 없는데 아래에 있음 
	if(d == 0 && g < s) {
		printf("use the stairs\n");
		return 0;
	}
	
	int ans = bfs();
	
	if(ans != -1) printf("%d\n", ans);
	else printf("use the stairs\n");
	
	return 0;
}
#endif

// 2. 단순 구현 => 0ms
#if 0

#include <stdio.h>

int f, s, g, u, d;	// 최고층, 시작층, 도착층, u칸 올라감, d칸 내려감 

void input_Data(void) {
	scanf("%d %d %d %d %d", &f, &s, &g, &u, &d);
}

int sol(void) {
	// 위에 있는데 위로 못간다던가... 아래에 있는데 아래로 못간다던가... 
	if((!u && g > s) || (!d && g < s)) return -1;
	
	// 걍 보이는대로 
	for(int i = 0; s > 0 && s <= f && i <= f; i++) {
		// 찾음 
		if(s == g) return i;
		
		// 어디로도 못 움직임 
		if(s + u > f && s - d <= 0) break;
		// 위에 있고 갈 수 있음 
		if(g > s && s + u <= f) s += u;
		// 위로는 못가는데, 아래에 있고 갈 수 있고 
		else if(s < g || s - d >= 0) s -= d;
	}
	
	return -1;
}
 

int main(void) {
	input_Data();
	
	int ans = sol();
	
	if(ans != -1) printf("%d\n", ans);
	else printf("use the stairs\n");
	
	return 0;
}
#endif 
