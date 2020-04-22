/***************/
// BOJ 2573 빙산
// 핵심: BFS 
/***************/

// 1. 내가 처음 푼 방법 => 100ms
#if 0

#include <stdio.h>
#include <string.h>
#include <queue>
#define MAX 301

using namespace std;

typedef struct pt {
	int x, y;
} pt;

int n, m;	// 지도의 세로, 가로 
int dx[] = {1, 0, -1, 0};	// right, down, left, up
int dy[] = {0, 1, 0, -1};
int map[MAX][MAX], copied[MAX][MAX];	// 원래 지도, 변화 기록 
char visited[MAX][MAX];
queue<pt> mount;

void input_Data(void) {
	scanf("%d %d", &n, &m);
	
	for(int j = 0; j < n; j++) {
		for(int i = 0; i < m; i++) {
			scanf("%d", &map[j][i]);
			
			// 빙산이 있을 때 미리 넣어놓기 
			if(map[j][i]) {
				pt tmp = {i, j};
				mount.push(tmp);
			}
		}
	}
}

void bfs(int x, int y) {
	// 서로 연결되어 있는지 확인하는 함수 
	
	queue<pt> q;
	pt init = {x, y};
	q.push(init);
	visited[y][x] = 1;
	
	while(!q.empty()) {
		pt cur = q.front(); q.pop();	// 현재 위치 
		
		for(int i = 0; i < 4; i++) {
			int mx = cur.x + dx[i];
			int my = cur.y + dy[i];
			
			// 범위 확인 
			if(mx < 0 || mx >= m || my < 0 || my >= n) continue;
			// 바다임 or 이미 경험함 
			if(!map[my][mx] || visited[my][mx]) continue;
			
			pt tmp = {mx, my};
			q.push(tmp);
			visited[my][mx] = 1;
		}
	}
}

int isOne(void) {
	// 덩어리가 1개면 1 반환, 2개 이상이면 0 반환 
	
	int cnt = 0;	// 덩어리 개수 
	
	memset(visited, 0, sizeof(visited));
	
	for(int j = 1; j < n - 1; j++) {
		for(int i = 1; i < m - 1; i++) {
			if(!map[j][i] || visited[j][i]) continue; 
			
			bfs(i, j);
			// 덩어리가 2개 이상 
			if((++cnt) > 1) break;
		}
	}
	
	// 덩어리가 2개 이상 
	if(cnt > 1) return 0;
	// 덩어리가 1개 
	else return 1;
}

int fill_Queue(void) {
	// 숫자들 미리 큐에 넣어놓기 => 빙산이 하나라도 있으면 1 반환 
	
	int flag = 0;
	
	for(int j = 1; j < n - 1; j++) {
		for(int i = 1; i < m - 1; i++) {
			if(!map[j][i]) continue;
			
			pt tmp = {i, j};
			mount.push(tmp);
			flag = 1;
		}
	}
	
	return flag;
}

void bfs_Melt(void) {
	memcpy(copied, map, sizeof(map));	// 미리 복사 
	
	while(!mount.empty()) {
		pt cur = mount.front(); mount.pop();
		
		for(int i = 0; i < 4; i++) {
			int mx = cur.x + dx[i];
			int my = cur.y + dy[i];
			
			// 여긴 이미 다 녹음 or 살펴본 곳이 빙하임 
			if(!copied[cur.y][cur.x] || map[my][mx]) continue;
			
			copied[cur.y][cur.x]--;
		}
	}
	memcpy(map, copied, sizeof(copied));	// 돌려놓기 
}

int sol(void) {
	int ans = 0;	// 시간 반환 
	
	while(1) {
		bfs_Melt();
		ans++;
		
		// 덩어리가 2개 이상 
		if(!isOne()) return ans;
		// 빙하가 다 녹음 
		if(!fill_Queue()) break;
	}
	
	return 0;
}


int main(void) {
	input_Data();
	printf("%d\n", sol());
	
	return 0;
}
#endif

// 2. 최적화한 것(초기 빙하를 계속 가지고 있기) => 24ms
#if 0

#include <stdio.h>
#include <string.h>
#include <vector>
#include <queue>
#define MAX 301

using namespace std;

typedef struct pt {
	int x, y;
} pt;

int n, m, melt;	// 지도의 세로, 가로, 각 판의 녹은 빙하 
int dx[] = {1, 0, -1, 0};	// right, down, left, up
int dy[] = {0, 1, 0, -1};
int map[MAX][MAX];
char visited[MAX][MAX];
vector<pt> beginning;	// 처음에 있던 빙하들 
queue<pt> q;

void input_Data(void) {
	scanf("%d %d", &n, &m);
	
	for(int j = 0; j < n; j++) {
		for(int i = 0; i < m; i++) {
			scanf("%d", &map[j][i]);
			
			// 빙하일 때 
			if(map[j][i]) {
				pt tmp = {i, j};
				beginning.push_back(tmp);
			}
		}
	}
}

void find_Remain_Ice(void) {
	// 처음에 빙하가 있던 자리에서 남아있는 빙하 하나를 추출 
	
	for(int i = 0; i < beginning.size(); i++) {
		pt cur = beginning[i];	// 현재 위치 
		
		// 녹은 거임 ㅅㄱ 
		if(map[cur.y][cur.x] <= 0) continue;
	
		q.push(cur);
		visited[cur.y][cur.x] = 1;
		return;
	}
}

int bfs(void) {
	// 빙하 하나에서 출발해서 이어져있는 빙하를 찾는 함수 
		
	memset(visited, 0, sizeof(visited));	// 초기화 
		
	find_Remain_Ice();	// 시작 위치 queue에 저장 
	
	int iceNum = 0;	// 빙하의 개수 
	melt = 0;
	
	while(!q.empty()) {
		pt cur = q.front(); q.pop();
		int cnt = 0;	// 주변 바다의 개수 
		iceNum++;
		
		for(int i = 0; i < 4; i++) {
			int mx = cur.x + dx[i];
			int my = cur.y + dy[i];
			
			// 경험하지 않은 곳 & 바다임 => 이게 이번에 영향줄 것 
			if(!visited[my][mx] && map[my][mx] <= 0) cnt++;
			// 이미 경험함 or 바다임 => 살펴볼 빙하는 아니다 
			if(visited[my][mx] || map[my][mx] <= 0) continue;
			
			pt tmp = {mx, my};
			q.push(tmp);
			visited[my][mx] = 1;
		}
		
		map[cur.y][cur.x] -= cnt;	// 녹임
		// 다 녹았나? 
		if(map[cur.y][cur.x] <= 0) melt++;
	}
	
	return iceNum;
}

int sol(void) {
	// 
	
	int time = 0, totNum = beginning.size();	// 걸린 햇수, 현재 빙하 개수 
	
	while(1) {
		// 한번에 다 둘러보는거 불가능 => 덩어리 2개 이상 
		if(bfs() != totNum) return time;
		
		totNum -= melt;	// 녹은거는 이제 빙하가 아니지 
		time++;
		
		// 이미 다 녹았음... 
		if(!totNum) break;
	}
	
	return 0;
}


int main(void) {
	input_Data();
	printf("%d\n", sol());
	
	return 0;
}
#endif
