/***********************/
// BOJ 14501 퇴사
// 핵심: Dynamic Programming
// 쪼개고 전달!!! 
/***********************/
#include <stdio.h>

int dDay, maxi = -1;	// 퇴사 전까지 일하는 날, 최대 급여
// time[i] = a: (i + 1)날에 받은 상담은 a일 걸림
// pay[i] = a: (i + 1)날에 받은 상담의 가격 a
// dp[i] = a: i번째 날까지 받은 상담의 최대 급여 
int time[16], pay[16], dp[16];

int max(int x, int y) {
	return x > y ? x : y;
}


int main(void) {
	scanf("%d", &dDay);
	
	for(int i = 0; i < dDay; i++) {
		scanf("%d %d", &time[i], &pay[i]);
	}
	
	for(int i = 0; i <= dDay; i++) {
		// i번째 날까지 받는 최대 급여갱신 
		if(i != 0) dp[i] = max(dp[i - 1], dp[i]);
		
		// 오늘치 상담 받았을 때 상담 끝나는 날의 최대 급여 갱신
		dp[i + time[i]] = max(dp[i + time[i]], dp[i] + pay[i]); 
	}
	
	printf("%d\n", dp[dDay]);
	
	return 0;
}
