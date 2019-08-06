#include <cstdio>

int dp[16][16];	// dp[a][b] = i : a층 b호에 i명이 산다 

int main(void) {
	int cs;	// 테스트 케이스 개수 
	scanf("%d", &cs);
	
	while(cs--) {
		int fl, i;	// 목표 층, 호수 
		scanf("%d %d", &fl, &i);
		
		// 초기화: 0층 j호에는 j명 산다 
		for(int j = 1; j <= i; j++) dp[0][j] = j;
		
		// 모든 층에 대해 
		for(int j = 1; j <= fl; j++) {
			dp[j][1] = 1;	// 각 층의 1호실에는 1명만 살아감 
			
			// 2호부터 모든 호수에 대해 
			for(int k = 2; k <= i; k++) {
				// 옆집과 밑 층 같은 호수 사람 합친 만큼이 현재 사람 수 
				dp[j][k] = dp[j][k - 1] + dp[j - 1][k];
			}
		}
		
		printf("%d\n", dp[fl][i]);
	}
	
	return 0;
}
