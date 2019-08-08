/*
계단 오르는 것과 비슷한데, 약간 다르다.
통과하는 경우가 있다는 것이 가장 큰 key point이다. 
*/
#include <cstdio>
#include <algorithm>

using namespace std;

int dp[10001];	// dp[i] = A : i까지 도달했을 때의 최대 합 A
int wine[10001];	// wine[i] = A : i의 값 A 


int main(void) {
	int n;	// 잔 수 
	scanf("%d", &n);
	
	for(int i = 1; i <= n; i++) scanf("%d", wine + i);
	
	// 초기화 
	dp[1] = wine[1];
	dp[2] = wine[1] + wine[2];
	
	// 3번째 잔부터 끝까지 봄 
	for(int i = 3; i <= n; i++) {
		// 통과하는 경우, 1잔 연속 마시는 경우, 2잔 연속 마시는 경우 비교 후 최대 값 
		dp[i] = max(dp[i - 1], max(dp[i - 2] + wine[i], dp[i - 3] + wine[i - 1] + wine[i]));
	}
	
	printf("%d\n", dp[n]);
	
	return 0;
}
