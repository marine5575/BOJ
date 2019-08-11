/*
O(n^3)을 O(n^2)로 만들어주는 
>> Kruth's Optimization << 적용
조건:
1. dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]) 형식일 것
2. c[a][c] + c[b][d] <= c[a][d] + c[b][c] (a <= b <= c <= d) 일 것 -> 사각부등식 만족
3. c[b][c] <= c[a][d] (a <= b <= c <= d) 일 것 -> 단조성

idx[i][j] = dp[i][j]가 최소가 되도록 가르는 k
이면 i <= k <= j인 k가 속하는 범위를
idx[i][j - 1] <= k <= idx[i + 1][j]로 줄일 수 있음 
*/
#include <cstdio>
#define INF 987654321

int dp[501][501];	// dp[i][j] = A : i ~ j번째까지의 최소 합 A 
int idx[501][501];	// idx[i][j] = A : dp[i][j]가 최소가 되게 하는 A. (i <= A <= j) 
int sum[501];	// sum[i] = A : i번째까지의 크기 합 A 


int main(void) {
	int cs;	// 테스트 케이스 
	scanf("%d", &cs);
	
	while(cs--) {
		int n;	// 파일 개수 
		scanf("%d", &n);
		
		for(int i = 1; i <= n; i++) {
			scanf("%d", sum + i);
			sum[i] += sum[i - 1];
			idx[i][i] = i;	// 일단 자기자신 저장 
		}
		
		// i에서 떨어진 거리 
		for(int x = 1; x < n; x++) {
			// i + x가 n이 되기 전까지 살펴봄 
			for(int i = 1; i + x <= n; i++) {
				int j = i + x;	// 종착점 
				dp[i][j] = INF;	// 일단 최소값 만들려는 초기화 
				
				// 중간값 
				for(int k = idx[i][j - 1]; k <= idx[i + 1][j]; k++) {
					int value = dp[i][k] + dp[k + 1][j];	// 임시값 
					
					// 최솟값 갱신 
					if(value < dp[i][j]) {
						dp[i][j] = value;
						idx[i][j] = k;
					}
				}
				// 맨 마지막에 전체 합 더함
				dp[i][j] += sum[j] - sum[i - 1];
			}
		}
		
		printf("%d\n", dp[1][n]);
	}
	
	return 0;
}
