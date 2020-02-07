/*********************/
// BOJ 14502 연구소
// 핵심: BFS + 3개의 벽 세우는 모든 경우의 수 따지기 
/*********************/
#include <iostream>
#include <vector>	// pair
#include <queue>
#include <cstring>	// memcpy

using namespace std;

int n, m, maxi = -1;	// height, width, 최대값 
int map[8][8], copyMap[8][8];	// 입력 받은 초기 map, 실제로 동작할 map; 
int dx[4] = {0, 0, -1, 1};	// up, down, left, right
int dy[4] = {-1, 1, 0, 0};	// up, down, left, right
queue<pair<int, int> > virusPos;	// 초기 virus들의 위치 


void bfs(void) {
	int virusMap[8][8];	// 바이러스 퍼뜨린 map 
	memcpy(virusMap, copyMap, sizeof(copyMap));
	
	queue<pair<int, int> > q = virusPos;	// 움직이지 않은 virus의 위치 
	
	// virus 모두 퍼질 때까지 
	while(!q.empty()) {
		// 움직일 virus 
		pair<int, int> curV = q.front(); q.pop();
		
		// 동서남북 
		for(int i = 0; i < 4; i++) {
			int mx = curV.first + dx[i];
			int my = curV.second + dy[i];
			
			// 범위 벗어나면 벗어남 
			if(mx < 0 || mx >= m || my < 0 || my >= n) continue;
			
			// 갈 수 있는가? 
			if(!virusMap[my][mx]) {
				virusMap[my][mx] = 2;	// virus 놓음 
				
				q.push(make_pair(mx, my)); 
			}
		}
	}
	
	int cnt = 0;	// 안전 영역 크기 
	
	for(int j = 0; j < n; j++) {
		for(int i = 0; i < m; i++) {
			// 비어있는가? 
			if(!virusMap[j][i]) cnt++;
		}
	}
	
	// 최대값 갱신 
	maxi = (maxi < cnt ? cnt : maxi);
}

void createWall(int cnt) {
	// 벽 이미 3개 다 세움 
	if(cnt == 3) {
		bfs();
		return;
	}
	
	for(int j = 0; j < n; j++) {
		for(int i = 0; i < m; i++) {
			// 갈 수 있는가? 
			if(!copyMap[j][i]) {
				// 벽 설치 
				copyMap[j][i] = 1;
				createWall(cnt + 1);
				// 설치 해제 
				copyMap[j][i] = 0;
			}
		}
	}
}


int main(void) {
	cin.tie(0);
	ios::sync_with_stdio(0);
	
	cin >> n >> m;
	
	for(int j = 0; j < n; j++) {
		for(int i = 0; i < m; i++) {
			cin >> map[j][i];
			
			// virus 있을 때 
			if(map[j][i] == 2) {
				virusPos.push(make_pair(i, j));
			}
		}
	}
	
	memcpy(copyMap, map, sizeof(map));
	createWall(0);
	
	cout << maxi << "\n";
	
	return 0;
} 
