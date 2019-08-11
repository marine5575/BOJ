/*
전형적인 DP 문제.
다시 복습이 필요한 생각보다 어려운 문제 
*/
#include <cstdio>
#include <algorithm>
#define INF 987654321

using namespace std;

int dp[501][501];	// dp[i][j] = A : i ~ j번째까지의 최소 파일 크기 A
int sum[501];	// sum[i] = A : i번째까지의 파일 크기 합 A 


int main(void) {
	int cs;	// 테스트 케이스 수 
	scanf("%d", &cs);
	
	while(cs--) {
		int n;	// 파일 개수 
		scanf("%d", &n);
		
		for(int i = 1, x; i <= n; i++) {
			scanf("%d", &x);
			sum[i] = sum[i - 1] + x;	// 파일 합 
		}
		
		// i에서 떨어진 거리 
		for(int x = 1; x < n; x++) {
			// 출발지 
			for(int i = 1; i + x <= n; i++) {
				int j = i + x;	// 목적지 
				dp[i][j] = INF;	// 최소값 
				
				// 중간값을 고려하여 최솟값 저장
				// 맨 마지막에 무조건 i ~ j의 전체 합 더해야 됨 
				for(int k = i; k < j; k++) {
					dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + sum[j] - sum[i - 1]);
				}
			}
		}
		
		printf("%d\n", dp[1][n]);
	}
	
	return 0;
}
