/*
DIVIDE AND CONQUER
이 문제는 큰 곱은 작은 것들의 곱으로 쪼갤 수 있다는 것이 핵심 
*/
#include <cstdio>
#include <algorithm>
#define INF 987654321

using namespace std;

typedef struct pair {
	int l, r;
} pr;

int dp[501][501];	// dp[i][j] = A : i ~ j번째까지의 최소 곱 A 
pr arr[501];	// input 저장 

int cal(int s, int e) {
	// 자기 자신일 경우 0 
	if(s == e) return 0;

	int &ref = dp[s][e];	// dp의 값도 바꿀 것이므로 call by ref
	// 들어있는 값이 초기 값이 아니라면 이미 최소값 
	if(ref != 0) return ref;
	
	int mini = INF;	// 곱의 최소값 
	
	// 중간에 있는 것들 살펴보기 
	for(int k = s; k < e; k++) {
		// s ~ k의 최솟값 + (k + 1) ~ e의 최솟값 + 현재 곱셈값 
		mini = min(mini, cal(s, k) + cal(k + 1, e) + arr[s].l * arr[k].r * arr[e].r);
	}
	
	// 갱신 후 return 
	return ref = mini;
}


int main(void) {
	int n;	// 행렬의 개수 
	scanf("%d", &n);
	
	for(int i = 0; i < n; i++) {
		scanf("%d %d", &arr[i].l, &arr[i].r);
	}
	
	printf("%d\n", cal(0, n - 1));
	
	return 0;
}
