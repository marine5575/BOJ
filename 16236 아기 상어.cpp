#include <stdio.h>
#include <queue>
#include <vector>
#define INF 987654321
#define MAX 21

using namespace std;

typedef struct st {
	int x, y;
} pt;

int n;	// map 크기
int sharkSize = 2, change, ans;	// 상어 크기, 현재 크기에서 물고기 먹은 횟수, 지금까지 지난 시간 
int map[MAX][MAX];
int dx[] = {1, 0, -1, 0};	// right, down, left, up
int dy[] = {0, 1, 0, -1};
pt shark;	// 상어의 현재 위치 

int bfs(void) {
	// shark 위치에서부터 처음으로 먹을 수 있는 물고기까지 BFS하는 함수
	// 먹을 물고기가 있으면 거리 반환, 없으면 0 반환 
	
	int visited[MAX][MAX] = {0, };
	int where = INF;	// 먹이를 찾은 시간 
	queue<pt> q;
	vector<pt> fish;	// 먹이 후보들 
	q.push(shark);
	visited[shark.y][shark.x] = 1;
	
	while(!q.empty()) {
		pt cur = q.front();	// 현재 위치 
		q.pop();
		int cnt = visited[cur.y][cur.x];	// 현재 위치까지 걸린 시간 
		
		// 먹이들 이미 찾았으면 탈출 
		if(where < cnt) break;
		
		for(int i = 0; i < 4; i++) {
			int mx = cur.x + dx[i];
			int my = cur.y + dy[i];
			
			// 범위 확인 
			if(mx < 0 || mx >= n || my < 0 || my >= n) continue;
			// 상어 크기보다 크거나 이미 들렀으면 통과 
			if(map[my][mx] > sharkSize || visited[my][mx]) continue;
			pt tmp = {mx, my};
			q.push(tmp);
			visited[my][mx] = cnt + 1;
			
			// 먹이를 찾음 => 후보에 넣음 
			if(map[my][mx] && map[my][mx] < sharkSize) {
				fish.push_back(tmp);
				where = cnt;
			}
		}
	}
	
	// 암것도 없었음 
	if(fish.size() == 0) return 0;
	
	int fishX = n, fishY = n;	// 최종 먹이 후보 좌표 
	for(int i = 0; i < fish.size(); i++) {
		// 위에 있는 것으로 갱신 
		if(fishY > fish[i].y) {
			fishX = fish[i].x;
			fishY = fish[i].y;
		}
		// 왼쪽에 있는 것으로 갱신 
		else if(fishY == fish[i].y && fishX > fish[i].x) {
			fishX = fish[i].x;
			fishY = fish[i].y;
		}
	}
	
	// 상어 위치 갱신 
	shark.x = fishX; shark.y = fishY;
	map[fishY][fishX] = 0;
	change++;
	
	// 상어 크기 키워야 하는가? 
	if(change == sharkSize) {
		sharkSize++;
		change = 0;
	}
	
	// 시간 누적 
	ans += visited[fishY][fishX] - 1;
	
	return 1;
}


int main(void) {
	scanf("%d", &n);
	
	for(int j = 0; j < n; j++) {
		for(int i = 0; i < n; i++) {
			scanf("%d", &map[j][i]);
			
			if(map[j][i] == 9) {
				shark.x = i;
				shark.y = j;
				map[j][i] = 0;
			}
		}
	}
	
	while(1) {
		int result = bfs();
		
		if(result == 0) break;
	}
	
	printf("%d\n", ans);
	
	return 0;
}
