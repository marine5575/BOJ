/*
대표적 DP 문제일 듯? 
*/
#include <cstdio>

int dp[10001];	// dp[i] = A : 가치 합이 i원일 때의 경우의 수 A 


int main(void) {
	int n, k, v;	// 동전 종류 수, 최대 가치 합, 동전 값 
	scanf("%d %d", &n, &k);
	
	dp[0] = 1;	// 초기화 
	
	while(n--) {
		scanf("%d", &v);
		
		// 앞의 경우의 수는 뒤의 경우의 수에 영향을 주므로 앞부터 살펴봄
		// v부터 가치합 살펴봄 
		for(int i = v; i <= k; i++) {
			dp[i] += dp[i - v];	// 이전 경우의 수와 현재 경우의 수를 합침 
		}
	}
	
	printf("%d\n", dp[k]);
	
	return 0;
} 
