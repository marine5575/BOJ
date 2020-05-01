/**********************************/
// BOJ 1194 달이 차오른다, 가자.
// 핵심: BFS & 경험 배열
// 			 => visited 배열이 단순한 방문이 아닌 '경험'이라는 것을 이해! 
/**********************************/
#include <stdio.h>
#include <queue>
#define MAX 60

using namespace std;

typedef struct pt {
	int x, y, key;
} pt;

int n, m;	// 미로의 세로, 가로 
int dx[] = {1, 0, -1, 0};	// right, down, left, up
int dy[] = {0, 1, 0, -1};
char map[MAX][MAX];
pt start;	// 민식이의 출발 위치 

void input_Data(void) {
	scanf("%d %d", &n, &m);
	
	int flag = 0;	// 조기 종료 깃발 
	
	for(int j = 0; j < n; j++) {
		scanf("%s", map[j]);
		
		// 이미 민식이 위치 찾음 
		if(flag) continue;
		
		for(int i = 0; i < m; i++) {
			// 민식 아님 
			if(map[j][i] != '0') continue;

			pt tmp = {i, j, 0};
			start = tmp;
			flag = 1;
			break;
		}
	}
}

inline int is_Door(int x, int y) {
	return map[y][x] >= 'A' && map[y][x] <= 'F';
}

inline int is_Match(int x, int y, int key) {
	// 가진 열쇠와 맞는 문일 때 1 반환, 아니면 0 반환
	 
	return (key >> (map[y][x] - 'A')) & 1;
}

int bfs(void) {
	// start부터 1에 닿을 때까지 진행하는 함수
	
	int visited[MAX][MAX][65] = {0, };	// visited[j][i][key] = (i, j)에 key를 가지고 도착했을 때 최소 걸린 시간 
	queue<pt> q;
	q.push(start);
	visited[start.y][start.x][0] = 1;
	
	while(!q.empty()) {
		pt cur = q.front(); q.pop();	// 현재 위치 
		int cnt = visited[cur.y][cur.x][cur.key];	// 현재 위치까지의 최소 거리 
		
		for(int i = 0; i < 4; i++) {
			int mx = cur.x + dx[i];
			int my = cur.y + dy[i];
			
			// 범위 확인 
			if(mx < 0 || mx >= m || my < 0 || my >= n) continue;
			// 벽임 or 이미 경험함 
			if(map[my][mx] == '#' || visited[my][mx][cur.key]) continue;
			// 문임 & 맞는 열쇠가 없음 
			if(is_Door(mx, my) && !is_Match(mx, my, cur.key)) continue;
			
			// 도착함 
			if(map[my][mx] == '1') return cnt;
			
			int newKey = cur.key;	// 새로운 열쇠 
			
			// 열쇠 칸임 
			if(map[my][mx] >= 'a' && map[my][mx] <= 'f') {
				newKey |= (1 << (map[my][mx] - 'a'));
			}
			
			pt tmp = {mx, my, newKey};
			q.push(tmp);
			visited[my][mx][newKey] = cnt + 1;
		}
	}
	
	return -1;	// 실패함 
}


int main(void) {
	input_Data();
	
	printf("%d\n", bfs());
	
	return 0;
}
