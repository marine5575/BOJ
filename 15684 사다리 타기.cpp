/************************/
// BOJ 15684 사다리 타기
// 핵심: BFS
//		 => 먼저 답을 찾으면 바로 끝내기 
/************************/
#include <stdio.h>

int n, m, h;	// 세로선, 가로선, 가로선을 놓을 수 있는 위치 개수 
int ans = 4, flag, ladder_Cnt;	// 정답, 이미 찾았는지 표시, break 걸 조건 
int ladder[32][12];	// 사다리 

void cal_Result(void) {
	int isOk = 1;	// 1: i번 세로선 결과 i번 / 0: 원하는 값 아님 
	
	for(int i = 1; i <= n; i++) {
		int x = i;	// 현재 x 
		
		for(int j = 1; j <= h; j++) {
			// 오른쪽으로 연결된 가로선 
			if(ladder[j][x]) x++;
			// 왼쪽으로 연결된 가로선 
			else if(x > 1 && ladder[j][x - 1]) x--;
		}
		
		// 원하는 값이 아님 => 탈출 
		if(i != x) {
			isOk = 0;
			break;
		}
	}
	
	// 원하는 값이었음 => 답 찾았다! 
	if(isOk) flag = 1;
	
	return;
}


void find_Ans(int idx, int cnt) {
	// 이미 답 찾았음 
	if(flag) return;
	
	// 계산할 때임 
	if(cnt == ladder_Cnt) {
		cal_Result();
		return;
	}
	
	for(int j = idx; j <= h; j++) {
		for(int i = 1; i < n; i++) {
			// 사다리는 연속할 수 없음 
			if(ladder[j][i - 1] || ladder[j][i] || ladder[j][i + 1]) continue;
			
			ladder[j][i] = 1;	// 방문 체크 
			find_Ans(j, cnt + 1);	// 다음거 방문 
			ladder[j][i] = 0;	// 방문 해제 
		}
	}
}


int main(void) {
	scanf("%d %d %d", &n, &m, &h);
	
	for(int i = 0, x, y; i < m; i++) {
		scanf("%d %d", &y, &x);
		
		ladder[y][x] = 1;
	}
	
	for(int i = 0; i <= 3; i++) {
		ladder_Cnt = i;
		
		find_Ans(1, 0);
		
		// 이미 답 찾음 
		if(flag) {
			printf("%d\n", i);
			return 0;
		}
	}
	
	printf("-1\n");
	
	return 0;
} 
