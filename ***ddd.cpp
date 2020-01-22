#include <iostream>

using namespace std;

int n, m, dicex, dicey;
int map[21][21], dice[7];
int dx[5] = {0, 1, -1, 0, 0};
int dy[5] = {0, 0, 0, -1, 1};

void swap(int *x, int *y) {
	int tmp = *y;
	*y = *x;
	*x = tmp;
	
	return;
}

void rolling(int dir) {
	switch(dir) {
		case 1: {
			swap(&dice[1], &dice[4]);
			swap(&dice[4], &dice[6]);
			swap(&dice[6], &dice[3]);
			break;
		}
		case 2: {
			swap(&dice[1], &dice[3]);
			swap(&dice[3], &dice[6]);
			swap(&dice[6], &dice[4]);
			break;
		}
		case 3: {
			swap(&dice[1], &dice[5]);
			swap(&dice[5], &dice[6]);
			swap(&dice[6], &dice[2]);
			break;
		}
		case 4: {
			swap(&dice[1], &dice[2]);
			swap(&dice[2], &dice[6]);
			swap(&dice[6], &dice[5]);
			break;
		}
	}
}


int main(void) {
	cin.tie(0);
	ios::sync_with_stdio(0);
	
	int cnt;
	
	cin >> n >> m >> dicex >> dicey >> cnt;
	
	for(int j = 0; j < n; j++) {
		for(int i = 0; i < m; i++) {
			cin >> map[j][i];
		}
	}
	
	if(map[dicey][dicex]) {
		dice[6] = map[dicey][dicex];
		map[dicey][dicex] = 0;
	}
	
	while(cnt--) {
		int dir;
		cin >> dir;
		
		rolling(dir);
		
		int nx = dicex + dx[dir], ny = dicey + dy[dir];
		
		if(nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
		
		dicex = nx; dicey = ny;
		
		cout << dice[1] << "\n";
		
		if(!map[ny][nx]) map[ny][nx] = dice[6];
		else {
			dice[6] = map[ny][nx];
			map[ny][nx] = 0;
		}
	}
	
	return 0;
}
