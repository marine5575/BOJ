/*
가장 전형적인 DP 문제.
대표적이기도 하다 
*/
#include <cstdio>
#include <algorithm>

using namespace std;

typedef struct bag {
	int w, v;
} b;

b arr[101];	// arr[i] = (w, v) 
int dp[101][100001];	// dp[i][j] = A : i번째까지 살펴보았을 때, 무게 j를 가진 최대 가치 합 A


int main(void) {
	int n, k;	// 물품 수, 최대 무게 
	scanf("%d %d", &n, &k);
	
	for(int i = 1; i <= n; i++) {
		scanf("%d %d", &arr[i].w, &arr[i].v);
	}
	
	// 모든 물품에 대해서 
	for(int i = 1; i <= n; i++) {
		// 모든 무게에 대해서 
		for(int j = 1; j <= k; j++) {
			/*
			이번 차례에 
			1. i번째를 넣지 않을 때
			2. i번째를 넣을 때 
			*/
			dp[i][j] = dp[i - 1][j];	// i번째 넣지 않았다고 가정 
			
			// 존재할 수 있는 무게인가?
			// 최댓값 저장 
			if(j - arr[i].w >= 0) dp[i][j] = max(dp[i][j], dp[i - 1][j - arr[i].w] + arr[i].v);
		}
	}
	
	printf("%d\n", dp[n][k]);
	
	return 0;
}
