/*
처음에 top-down 형식으로 생각했을 때는 시간초과가 난 문제이다.
재귀 호출을 너무 많이 하는 형식이었기 때문이라고 생각하고 있다. 
*/

#include <cstdio>

int dp[1000001];	// dp[i] = A : i가 1이 될 때까지 걸린 최소 횟수 A 


int main(void) {
	int n;	// 구하고 싶은 숫자 
	scanf("%d", &n);
	
	for(int i = 2; i <= n; i++) {
		dp[i] = dp[i - 1] + 1;	// 모든 숫자에서 1을 빼는 것은 가능
		// i가 2의 배수인가? 
		if(i % 2 == 0) dp[i] = dp[i] > dp[i / 2] + 1 ? dp[i / 2] + 1 : dp[i];
		// i가 3의 배수인가? 
		if(i % 3 == 0) dp[i] = dp[i] > dp[i / 3] + 1 ? dp[i / 3] + 1 : dp[i];
	}
	
	printf("%d\n", dp[n]);
}
