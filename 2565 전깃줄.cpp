/*
끊는 것으로 접근하는 것보다
겹치지 않게 가장 길게 이어질 수 있는 길이를 찾는 것이 핵심 
*/
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;


pair<int, int> pole[501];	// 이어진 전봇대 
int dp[501];	// dp[i] = A : LIS에서 i번째 위치한 수 A 


int main(void) {
	int n, idx = 0;	// 전깃줄 개수, LIS 길이 - 1 
	scanf("%d", &n);
	
	for(int i = 0; i < n; i++) scanf("%d %d", &pole[i].first, &pole[i].second);
	
	// 일단 정렬 
	sort(pole, pole + n);
	 
	dp[0] = pole[0].second;	// 초기화 
	
	// 1번째부터 끝까지 살펴봄 
	for(int i = 1; i < n; i++) {
		// LIS를 이어갈 수 있나? 
		if(dp[idx] < pole[i].second) dp[++idx] = pole[i].second;
		// 갱신해야되는가? 
		else {
			// 해당 값과 가장 비슷한 것의 index 
			int tmp = lower_bound(dp, dp + idx, pole[i].second) - dp;
			dp[tmp] = pole[i].second;	// 갱신 
		}
	}
	
	// 끊어야 되는 것의 개수 
	printf("%d\n", n - idx - 1);

	return 0;
}
