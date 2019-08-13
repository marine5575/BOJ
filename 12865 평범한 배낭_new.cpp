/*
불필요하게 공간을 많이 쓰기 때문에
들어올 때마다 갱신하는 방식으로 바꿈 
*/
#include <cstdio>

int dp[100001];	// dp[i] = A : i의 무게를 가지는 최대 가치 합 A 


int main(void) {
	int n, k, w, v;	// 물품 수, 최대 무게, 물품 무게, 물품 가치 
	scanf("%d %d", &n, &k);
	
	while(n--) {
		scanf("%d %d", &w, &v);
		
		// w부터 살펴보지 않는 이유는 혼선이 생길 수 있기 때문 
		// 최대 무게부터 하나씩 살펴봄 
		for(int i = k; i >= w; i--) {
			// i까지 채울 때 이 물품을 넣을 것인가? 
			if(dp[i - w] + v > dp[i]) dp[i] = dp[i - w] + v;
		}
	}
	
	printf("%d\n", dp[k]);
	
	return 0;
}
