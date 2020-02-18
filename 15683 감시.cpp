/****************/
// BOJ 15683 감시
// 핵심:  dfs (방문 체크, 방문 해제) 
/****************/

#include <stdio.h>
#include <string.h>

typedef struct pos {
	int x, y;
} pos;

typedef struct cctv {
	int idx;
	pos arr[65];
} cctv;

int n, m;	// height, width
int mini = 65;	// 사각지대 최소값 
int map[8][8];
int dx[] = {0, 1, 0, -1};	// up, right, down, left
int dy[] = {-1, 0, 1, 0};
cctv cctv_Pos[6];

void run_CCTV(int num, int at) {
	int cnt = 0;	// 사각지대 
	int tmp[8][8];	// 처음 들어왔을 때의 map
	
	memcpy(tmp, map, sizeof(map));
	
	// 모든 번호 확인 
	for(int i = num; i < 6; i++) {
		// 없으면 통과 
		if(cctv_Pos[i].idx == 0) continue;
		// i가 들어온 값이 아니면 j는 0부터 시작해야됨 
		if(i != num) at = -1;
		
		int idx = cctv_Pos[i].idx;	// map에 있는 type의 개수 
		 
		for(int j = at + 1; j < idx; j++) {
			int x = cctv_Pos[i].arr[j].x;	// 현재 x좌표 
			int y = cctv_Pos[i].arr[j].y;	// 현재 y좌표 
			
			switch(i) {
				// 일방향 
				case 1: {
					// 사방으로 봐야 됨 
					for(int k = 0; k < 4; k++) {
						int mx = x, my = y;	// 갈 (x, y) 좌표 
						
						// 막힐 때까지 쭉 감 
						while(1) {
							mx += dx[k];
							my += dy[k];
							
							if(mx < 0 || mx >= m || my < 0 || my >= n || map[my][mx] == 6) break;
							
							// 방문 체크 
							if(map[my][mx] <= 0) map[my][mx]--;
						}
						
						// 일단 가긴 했음 
						if(mx != x + dx[k] || my != y + dy[k]) {
							run_CCTV(i, j);
							memcpy(map, tmp, sizeof(tmp));	// 방문 해제 
						}
					}
					
					break;
				}
				// 양쪽 
				case 2: {
					// 2번만 돌려도 ok 
					for(int k = 0; k < 2; k++) {
						// 양쪽으로 
						for(int l = 0; l <= 2; l += 2) {
							int mx = x, my = y;
							
							while(1) {
								mx += dx[(k + l) % 4];
								my += dy[(k + l) % 4];
								
								if(mx < 0 || mx >= m || my < 0 || my >= n || map[my][mx] == 6) break;
								
								// 방문체크 
								if(map[my][mx] <= 0) map[my][mx]--;
							}
						}
						
						run_CCTV(i, j);
						memcpy(map, tmp, sizeof(tmp));	// 방문 해제 
					}
					break;
				}
				// L자
				case 3: {
					// 4번 돌려야 됨 
					for(int k = 0; k < 4; k++) {
						// L자로 
						for(int l = 0; l < 2; l++) {
							int mx = x, my = y;
							
							while(1) {
								mx += dx[(k + l) % 4];
								my += dy[(k + l) % 4];
								
								if(mx < 0 || mx >= m || my < 0 || my >= n || map[my][mx] == 6) break;
								
								// 방문체크 
								if(map[my][mx] <= 0) map[my][mx]--;
							}
						}
						
						run_CCTV(i, j);
						memcpy(map, tmp, sizeof(tmp));	// 방문 해제 
					}
					
					break;
				}
				// ㅗ모양 
				case 4: {
					// 4번 돌려야 됨 
					for(int k = 0; k < 4; k++) {
						// ㅗ 
						for(int l = 0; l < 3; l++) {
							int mx = x, my = y;
							
							while(1) {
								mx += dx[(k + l) % 4];
								my += dy[(k + l) % 4];
								
								if(mx < 0 || mx >= m || my < 0 || my >= n || map[my][mx] == 6) break;
								
								// 방문 체크 
								if(map[my][mx] <= 0) map[my][mx]--;
							}
						}
						
						run_CCTV(i, j);
						memcpy(map, tmp, sizeof(tmp));	// 방문 해제 
					}
					
					break;
				}
				// 십자 모양 
				case 5: {
					// 십자 모양 
					for(int k = 0; k < 4; k++) {
						int mx = x, my = y;
						
						while(1) {
							mx += dx[k];
							my += dy[k];
							
							if(mx < 0 || mx >= m || my < 0 || my >= n || map[my][mx] == 6) break;
							
							// 방문 체크 
							if(map[my][mx] <= 0) map[my][mx]--;
						}
					}
					
					run_CCTV(i, j);
					memcpy(map, tmp, sizeof(tmp));	// 방문 해제 
					
					break;
				}
			}
		}
	}
	
	// 사각 지대 확인 
	for(int j = 0; j < n; j++) {
		for(int i = 0; i < m; i++) {
			if(!map[j][i]) cnt++;
		}
	}
	
	// 갱신 
	mini = mini > cnt ? cnt : mini;
}


int main(void) {
	scanf("%d %d", &n, &m);
	
	for(int j = 0; j < n; j++) {
		for(int i = 0; i < m; i++) {
			scanf("%d", &map[j][i]);
			
			if(map[j][i] >= 1 && map[j][i] <= 5) {
				int idx = cctv_Pos[map[j][i]].idx;
				
				cctv_Pos[map[j][i]].arr[idx].x = i;
				cctv_Pos[map[j][i]].arr[idx].y = j;
				cctv_Pos[map[j][i]].idx++;
			}
		}
	}

	run_CCTV(1, -1);
	printf("%d\n", mini);
	
	return 0;
}
