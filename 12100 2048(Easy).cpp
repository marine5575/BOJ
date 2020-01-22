#include <iostream>
#include <queue>

using namespace std;

int n, maxi = -1;	// map의 크기, 최대값 
int map[21][21];	// map

// 이동하는 함수 
void shift(int dir) {
	queue<int> q;
	
	switch(dir) {
		// up
		case 0: {
			// x좌표 
			for(int i = 0; i < n; i++) {
				// y좌표 
				for(int j = 0; j < n; j++) {
					// 값이 들어있는가? 
					if(map[j][i]) q.push(map[j][i]);
					map[j][i] = 0;
				}
				
				int idx = 0;	// 위로 올라가므로 가장 위에서부터 시작 
				
				while(!q.empty()) {
					// 현재 값 
					int cur = q.front(); q.pop();
					
					// 비어있다면 값 놓기 
					if(!map[idx][i]) map[idx][i] = cur;
					// 나랑 같은 값인가? 
					else if(map[idx][i] == cur) {
						map[idx][i] *= 2;	// 합치기 
						idx++;	// 다시 함쳐지지 않으므로 
					}
					// 아예 다른 값 
					else {
						idx++;
						map[idx][i] = cur;
					}
				}
			}
			
			break;
		}
		// down
		case 1: {
			// x좌표 
			for(int i = 0; i < n; i++) {
				// y좌표 
				for(int j = n - 1; j >= 0; j--) {
					// 밑부터 값을 가지고 있는 것을 집어넣음 
					if(map[j][i]) q.push(map[j][i]);
					map[j][i] = 0; 
				}
				
				int idx = n - 1;	// 놓여야 하는 위치 
			
				while(!q.empty()) {
					// 내려올 값 
					int cur = q.front(); q.pop(); 
					
					// 비어있으면 걍 놓음 
					if(!map[idx][i]) map[idx][i] = cur;
					// 같은 값인가? 
					else if(map[idx][i] == cur) {
						map[idx][i] *= 2;
						idx--;	// 다시 합쳐지지 않음 
					}
					// 다른 값인가? 
					else {
						idx--;
						map[idx][i] = cur;
					}
				}
			}
			
			break;
		}
		// left
		case 2: {
			// y좌표 
			for(int j = 0; j < n; j++) {
				// x좌표 
				for(int i = 0; i < n; i++) {
					if(map[j][i]) q.push(map[j][i]);
					map[j][i] = 0;
				}
				
				int idx = 0;	// 놓여져야 하는 위치 
				
				while(!q.empty()) {
					int cur = q.front(); q.pop();
					
					// 비어있으면 걍 놓기 
					if(!map[j][idx]) map[j][idx] = cur;
					// 같은 값인가? 
					else if(map[j][idx] == cur) {
						map[j][idx] *= 2;
						idx++;	// 다시 합쳐지진 않음 
					}
					// 다른 값인가? 
					else {
						idx++;
						map[j][idx] = cur;
					}
				}
			}
			
			break;
		}
		// right
		case 3: {
			// y좌표 
			for(int j = 0; j < n; j++) {
				// x좌표 
				for(int i = n - 1; i >= 0; i--) {
					if(map[j][i]) q.push(map[j][i]);
					map[j][i] = 0;
				}
				
				int idx = n - 1;	// 놓여져야 하는 위치 
				
				while(!q.empty()) {
					int cur = q.front(); q.pop();
					
					// 비어있으면 걍 놓기 
					if(!map[j][idx]) map[j][idx] = cur;
					// 같은 값인가? 
					else if(map[j][idx] == cur) {
						map[j][idx] *= 2;
						idx--;	// 다시 합쳐지지 않음 
					}
					// 다른 값인가? 
					else {
						idx--;
						map[j][idx] = cur;
					}
				}
			}
			
			break;
		}
	}
}

void dfs(int cnt) {
	// 5번 움직임 => 최댓값 확인 
	if(cnt == 5) {
		for(int j = 0; j < n; j++) {
			for(int i = 0; i < n; i++) {
				if(maxi < map[j][i]) maxi = map[j][i];
			}
		}
		
		return;
	}
	
	int copy[21][21] = {0};	// 배열 backup 
	
	for(int j = 0; j < n; j++) {
		for(int i = 0; i < n; i++) {
			copy[j][i] = map[j][i];
		}
	}
	
	// up, down, left, right
	for(int k = 0; k < 4; k++) {
		shift(k);	// 움직이고 
		dfs(cnt + 1);	// 다음 움직임으로 
		
		// 방문 해제 
		for(int j = 0; j < n; j++) {
			for(int i = 0; i < n; i++) {
				map[j][i] = copy[j][i];
			}
		}
	}
}


int main(void) {
	cin.tie(0);
	ios::sync_with_stdio(0);
	
	cin >> n;
	
	for(int j = 0; j < n; j++) {
		for(int i = 0; i < n; i++) {
			cin >> map[j][i];
		}
	}
	
	dfs(0);
	
	cout << maxi << "\n";
	
	return 0;
} 
