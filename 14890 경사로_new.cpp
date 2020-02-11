/*********************/
// BOJ 14890 경사로
// << 최적화 >>
// 핵심: 1. flag 하나만으로 내려가는 것과 올라가는 것 다룸 
//		 2. 90도 회전 시켜서 2중 루프로 행, 열 모두 검사 
/*********************/
#include <stdio.h>

int n, len, ans;	// 지도 크기, 경사로 길이, 정답 
int map[201][101];


int main(void) {
	scanf("%d %d", &n, &len);
	
	for(int j = 0; j < n; j++) {
		for(int i = 0; i < n; i++) {
			scanf("%d", &map[j][i]);
		}
	}
	
	// 뒤쪽에 90도 회전시켜서 저장 
	for(int j = 0; j < n; j++) {
		for(int i = 0; i < n; i++) {
			map[n + i][n - 1 - j] = map[j][i];
		}
	}
	
	int i;	// 나중에 검사해야 됨 
	
	for(int j = 0; j < 2 * n; j++) {
		int flag = 1;	// potential
		
		for(i = 1; i < n; i++) {
			// 아직 같은 높이 
			if(map[j][i] == map[j][i - 1]) flag++;
			// 한 칸 위 & 충분한 potential 가지고 있음 => 올라감 
			else if(map[j][i] == map[j][i - 1] + 1 && flag >= len) {
				flag = 1;
			}
			// 한 칸 아래 & 충분한 potential 가지고 있음 => 내려감 
			else if(map[j][i] == map[j][i - 1] - 1 && flag >= 0) {
				flag = -len + 1;
			}
			// 그 외 
			else break;
		}
		
		// 끝까지 마침 & 경사로 놓는데에도 문제 없음 => 길 + 1 
		if(i == n && flag >= 0) ans++;
	}
	
	printf("%d\n", ans);
	
	return 0;
}
