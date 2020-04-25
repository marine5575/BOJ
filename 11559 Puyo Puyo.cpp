/***********************/
// BOJ 11559 Puyo Puyo
// 핵심: Flood Fill (DFS)
// 			 => 부서진거 밑으로 옮기는 코드를 잘못짜서 한참 헤맴 
/***********************/
#include <stdio.h>
#include <string.h>

char map[13][8], used[13][8];	// 지도, 사용 표시
int flag, nodeCnt;	// 4개 이상인지, 현재 연결된 노드 개수 
int dx[] = {1, 0, -1, 0};	// right, up, left, down
int dy[] = {0, -1, 0, 1};

void input_Data(void) {
	for(int j = 0; j < 12; j++) {
		scanf(" %s", map[j]);
	}
}

void dfs(int x, int y, char color) {
	// (x, y)와 연결된 곳을 감. 참고로 color가 연결된 곳 
	
	map[y][x] = '.';	// 미리 없앰 
	used[y][x] = color;	// 사용 체크 
	nodeCnt++;
	
	for(int i = 0; i < 4; i++) {
		int mx = x + dx[i];
		int my = y + dy[i];
		
		// 범위 체크 
		if(mx < 0 || mx >= 6 || my < 0 || my >= 12) continue;
		// 연결된 곳이 아님 
		if(map[my][mx] != color) continue;
		
		dfs(mx, my, color);
		
		// 연결된 곳이 4개 이상이었음 
		if(nodeCnt >= 4) flag = 1;
	}
}

void repair_Map(int x, int y, char color) {
	// 연결된 곳이 4개 미만이라 다시 color로 복구하는 함수 
	
	map[y][x] = color;
	used[y][x] = 0;	// 안 왔던 것처럼 슥삭 
	
	for(int i = 0; i < 4; i++) {
		int mx = x + dx[i];
		int my = y + dy[i];
		
		// 범위 확인 
		if(mx < 0 || mx >= 6 || my < 0 || my >= 12) continue;
		// 연결된 곳이 아님 
		if(used[my][mx] != color) continue;
		
		repair_Map(mx, my, color);
	}
}

void clean_Map(void) {
	// 중력 영향으로 떨어지는 뿌요들 처리 
	
	for(int i = 0; i < 6; i++) {
		for(int j = 10; j >= 0; j--) {
			// 그냥 빈칸임 
			if(map[j][i] == '.') continue;
			
			for(int k = 11; k > j; k--) {
				// 뭔가로 차있음 
				if(map[k][i] != '.') continue;
				
				map[k][i] = map[j][i];
				map[j][i] = '.';
				break;
			}
		}
	}
}

int sol(void) {
	int cnt = 0, pop = 0;	// 연쇄 횟수, 이번에 터진 덩어리 개수 
	
	while(1) {
		// 초기화
		pop = 0; 
		memset(used, 0, sizeof(used));
		
		for(int j = 11; j >= 0; j--) {
			for(int i = 0; i < 6; i++) {
				// 비어있음 
				if(map[j][i] == '.') continue;
				
				flag = 0;
				nodeCnt = 0;
				
				dfs(i, j, map[j][i]);
				
				// 4개 이상임 
				if(flag) {
					pop++;
				}
				// 4개 미만 => 복구 
				else repair_Map(i, j, used[j][i]);
			}
		}
		
		// 이번에 터졌음 
		if(pop) {
			clean_Map();
			cnt++;
		}
		// 터진 것 없음 
		else break;
	}
	
	return cnt;
}


int main(void) {
	input_Data();
	printf("%d\n", sol());
	
	return 0;
}
