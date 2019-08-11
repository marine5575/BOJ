#include <cstdio>

long long dp[100001];	// dp[i] = A : i번째까지의 최대 연속 합 A 


int main(void) {
	int n;	// 수열 개수 
	long long max = -1001;	// 최대값 
	scanf("%d", &n);
	
	// 수열 원소 하나하나 입력 받기 
	for(int i = 0, x; i < n; i++) {
		scanf("%d", &x);
		
		// 첫번째 원소는 그냥 넣기 
		if(i == 0) dp[0] = x;
		// 두번째 원소부터 
		else {
			// 이전 최대 합이 양수일 때 
			if(dp[i - 1] >= 0) dp[i] = dp[i - 1] + x;
			// 이전 최대 합이 음수일 때 
			else {
				dp[i] = x;
			}
		} 
		
		// 최댓값 갱신 
		if(max < dp[i]) max = dp[i];
	}
	
	printf("%lld\n", max);
	
	return 0;
}
