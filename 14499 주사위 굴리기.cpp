/*****************************/
// 문제들의 x, y는
// 나와 항상 >>반대<< 라는 것을
// 항상 유념하도록 하자...^^ 
/*****************************/

#include <iostream>

using namespace std;

int n, m, dicex, dicey;	// 세로, 가로폭, 주사위 위치의 (x, y) 좌표 
int map[21][21], dice[7];	// map, 주사위 
// right, left, up, down 
int dx[5] = {0, 1, -1, 0, 0};
int dy[5] = {0, 0, 0, -1, 1};

// swap 함수 
void swap(int *x, int *y) {
	int tmp = *y;
	*y = *x;
	*x = tmp;
	
	return;
}

// 주사위 굴리기 
void rolling(int dir) {
	switch(dir) {
		// right
		case 1: {
			swap(&dice[1], &dice[4]);
			swap(&dice[4], &dice[6]);
			swap(&dice[6], &dice[3]);
			break;
		}
		// left
		case 2: {
			swap(&dice[1], &dice[3]);
			swap(&dice[3], &dice[6]);
			swap(&dice[6], &dice[4]);
			break;
		}
		// up
		case 3: {
			swap(&dice[1], &dice[5]);
			swap(&dice[5], &dice[6]);
			swap(&dice[6], &dice[2]);
			break;
		}
		// down
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
	
	int cnt;	// 명령 개수 
	
	// 항상 x, y 반대로 생각!!!!! 
	cin >> n >> m >> dicey >> dicex >> cnt;
	
	for(int j = 0; j < n; j++) {
		for(int i = 0; i < m; i++) {
			cin >> map[j][i];
		}
	}
	
	// 시작 지점에 숫자가 써있나? 
	if(map[dicey][dicex]) {
		dice[6] = map[dicey][dicex];
		map[dicey][dicex] = 0;
	}
	
	while(cnt--) {
		int dir;	// 방향 정보 
		cin >> dir;
		
		// 굴려야하는 주사위의 (x, y) 좌표 
		int nx = dicex + dx[dir], ny = dicey + dy[dir];
		
		// map을 벗어났는가? 
		if(nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
		
		rolling(dir);	// 주사위 굴리기
		dicex = nx; dicey = ny;	// 새롭게 주사위 위치 갱신 
		
		// 윗면 출력 
		cout << dice[1] << "\n";
		
		// 그 자리가 0인가? 
		if(!map[ny][nx]) map[ny][nx] = dice[6];
		else {
			dice[6] = map[ny][nx];
			map[ny][nx] = 0;
		}
	}
	
	return 0;
}
