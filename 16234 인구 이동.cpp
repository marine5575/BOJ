/*********************/
// BOJ 16234 인구 이동
// 핵심: BFS & queue 활용
// 			 => 처음에 본 이후에는 변동 생겼던 부분들만 보면 됨!! 
/*********************/
#include <stdio.h>
#include <vector>
#include <queue>
#define MAX 51

using namespace std;

typedef struct st {
	int x, y;
} pt;

int n, l, r;	// map 크기, 경계 최소값, 경계 최대값 
int moveCnt;	// 인구 이동 횟수 
int map[MAX][MAX], visited[MAX][MAX];
int dx[] = {1, 0, -1, 0};	// right, down, left, up
int dy[] = {0, 1, 0, -1};
queue<pt> q;

int abs(int a) {
	return a < 0 ? -a : a;
}

int check(pt cur, int mx, int my) {
	// 인접한 것과 현재의 값 차이가 L 이상 R 이하면 1 반환
	// 아니면 0 반환
	
	int num = abs(map[cur.y][cur.x] - map[my][mx]);
	
	if(num >= l && num <= r) return 1;
	else return 0;
}

int bfs(int startX, int startY) {
	// (startX, startY)부터 l 이상 r 이하일 경우에만 BFS를 진행하고 
	// 다 끝난 이후에는 국경 열린 곳에 인구를 나눠주는 함수
	// 인구 이동을 한 번이라도 했다면 1 반환, 이동하지 않았다면 0 반환 
	// 단, visited에 방문 노드가 기록되어 있음
	
	int idx = 0, sum = 0;	// vector 써야하는 위치, 국경 연결된 나라의 합 
	vector<pt> vec;
	pt init = {startX, startY};
	vec.push_back(init);
	visited[startY][startX] = moveCnt;
	
	while(idx < vec.size()) {
		pt cur = vec[idx++];	// 현재 위치 
		sum += map[cur.y][cur.x];
		
		for(int i = 0; i < 4; i++) {
			int mx = cur.x + dx[i];
			int my = cur.y + dy[i];
			
			// 범위 체크 & 방문 여부 확인 
			if(mx < 0 || mx >= n || my < 0 || my >= n || visited[my][mx] == moveCnt) continue;
			// 국경 연결 가능 체크 
			if(!check(cur, mx, my)) continue;
			
			pt tmp = {mx, my};
			vec.push_back(tmp);
			visited[my][mx] = moveCnt;
		}
	}
	
	// 다른 나라와 전혀 연결되어 있지 x 
	if(vec.size() == 1) return 0;
	
	for(int i = 0; i < vec.size(); i++) {
		int x = vec[i].x, y = vec[i].y;
		map[y][x] = sum / vec.size();
		q.push(vec[i]);
	}
	
	return 1;
}

int population_move(void) {
	// 변동이 있었던 좌표들부터 BFS를 시작할 수 있도록 하는 함수 
	// 한 번도 인구이동이 일어나면 1 반환, 아니면 0 반환 
	
	int flag = 0, sz = q.size();	// 인구 이동 여부(0: 이동 x), 현재 살펴봐야 되는 수 
	moveCnt++;	// 일단 이동했다고 침 
	
	for(int i = 0; i < sz; i++) {
		pt cur = q.front();	// 현재 위치 
		q.pop();
		
		// 방문 여부 확인 
		if(visited[cur.y][cur.x] == moveCnt) continue;
		
		flag += bfs(cur.x, cur.y);
	}
	
	if(flag) return 1;
	else return 0;
}


int main(void) {
	scanf("%d %d %d", &n, &l, &r);
	
	for(int j = 0; j < n; j++) {
		for(int i = 0; i < n; i++) {
			scanf("%d", &map[j][i]);
			
			pt tmp = {i, j};
			q.push(tmp);
		}
	}
	
	while(1) {
		int flag = population_move();
		
		// 한번도 안 움직임 
		if(!flag) break;
	}
	
	printf("%d\n", moveCnt - 1);
	
	return 0;
}
