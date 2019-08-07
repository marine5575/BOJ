/*
대표적인 DP 문제
처음에 생각을 약간 잘못했다.
DP의 핵심은 >> 점화식, memoization 정의 <<인데
점화식을 잘못 세운 듯 싶다.
DP에서는 과정을 통해 결과를 도출하는 것보다는 결과에서 들여다 보는 것이 더 빈번한 것 같으니 기억해두자. 
*/
#include <cstdio>

int dp[3];	// dp[i] = a : 현재 (R or G or B)를 선택했을 때의 최소 거리 a 
int tmp[3];	// dp[i] = a : 바로 전에 (R or G or B)를 선택했을 때의 최소 거리 a 


int main(void) {
	int n, r, g, b;	// 집 개수, 빨간색, 초록색, 파란색을 칠할 때 드는 비용 
	scanf("%d", &n);
	scanf("%d %d %d", &r, &g, &b);
	
	// 초기화 
	dp[0] = r; dp[1] = g; dp[2] = b;
	
	for(int i = 1; i < n; i++) {
		scanf("%d %d %d", &r, &g, &b);
		
		// 이제는 이전 것이 됨 
		tmp[0] = dp[0]; tmp[1] = dp[1]; tmp[2] = dp[2];
		
		// 전에 선택한 길 중 더 짧은 것을 더함 
		dp[0] = (tmp[1] > tmp[2] ? tmp[2] : tmp[1]) + r;
		dp[1] = (tmp[0] > tmp[2] ? tmp[2] : tmp[0]) + g;
		dp[2] = (tmp[0] > tmp[1] ? tmp[1] : tmp[0]) + b;
	}
	
	// 도착지점이 G, B인 거리 중에 더 짧은 것 
	int minT = dp[1] > dp[2] ? dp[2] : dp[1];
	// R, G, B 중 가장 짧은 거리 
	int ans = dp[0] > minT ? minT : dp[0];
	
	printf("%d\n", ans);
	
	return 0;
}
