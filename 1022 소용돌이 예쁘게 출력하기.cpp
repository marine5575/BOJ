/*************************************/
// BOJ 1022 소용돌이 예쁘게 출력하기
// 핵심: 시뮬레이션 & 공간 계산 
/*************************************/
#include <stdio.h>

int r1, c1, r2, c2;	// 좌상단 좌표(c1, r1), 우하단 좌표(c2, r2) 
int map[50][5];
int dx[] = {1, 0, -1, 0};	// right, up, left, down
int dy[] = {0, -1, 0, 1};

void input_Data(void) {
	scanf("%d %d %d %d", &r1, &c1, &r2, &c2);
}

int cal_Len(int num) {
	// 가장 긴 숫자의 자리수 계산 
	
	int cnt = 0;	// 총 자리수 
	
	while(num > 0) {
		num /= 10;
		cnt++;
	}
	
	return cnt;
}

void sol(void) {
	int x = -c1, y = -r1;	// 1의 시작 위치 
	int num = 1, dir = 0;	// 배열에 들어갈 숫자, 방향 
	int cnt = 0, dirCnt = 1;	// dirCnt 만큼 세는 것, 한 방향으로 몇번가야 되는지 표시 
	int flag = 0;	// 배열 채운 숫자의 개수 
	
	while(1) {
		// 배열에 숫자를 모두 채움 
		if(flag == (c2 - c1 + 1) * (r2 - r1 + 1)) break;
		
		// 범위 안에 해당되면 지도에 기록 
		if(0 <= x && x <= (c2 - c1) && 0 <= y && y <= (r2 - r1)) {
			map[y][x] = num;
			flag++;
		}
		
		num++; cnt++;
		
		x += dx[dir];
		y += dy[dir];
		
		// 방향 바꿀 때가 됨 
		if(cnt >= dirCnt) {
			cnt = 0;
			dir = (dir + 1) % 4;
			
			// 더 갈 때가 됨 
			if(!(dir & 1)) dirCnt++;
		}
	}
	
	int len = cal_Len(num);	// 가장 긴 숫자의 자리수 
	
	for(int j = 0; j <= (r2 - r1); j++) {
		for(int i = 0; i <= (c2 - c1); i++) {
			printf("%*d ", len, map[j][i]);
		}
		printf("\n");
	}
}


int main(void) {
	input_Data();
	sol();
	
	return 0;
}
