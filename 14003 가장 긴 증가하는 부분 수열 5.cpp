#include <cstdio>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

int arr[1000001];	// 원래 수열
int dp[1000001];	// dp[i] : i번째까지 왔을 때 가장 긴 수열의 꽁무니
int idx = 0, n;	// 구하는 수열 크기, 원래 수열의 길이
pair<int, int> ans[1000001];	// 답 저장
stack<int> s;	// back tracking에 이용


void longSeq() {
	dp[idx] = arr[0];	// 첫번째는 무조건 arr[0]
	ans[0] = { 0, arr[0] };	// 답의 0번도 그러함

	// 0번은 초기화 시켰으니 1번부터 봄
	for (int i = 1; i < n; i++) {
		// 현재 꽁무니가 다음 것보다 더 작을 때
		if (dp[idx] < arr[i]) {
			dp[++idx] = arr[i];	// 그대로 이어감
			ans[i] = { idx, arr[i] };
		}
		// 현재 꽁무니가 다음 것보다 더 클 때
		else {
			// arr[i]와 값이 비슷하면서 가장 작은 index를 가진 것 반환
			int tmp = lower_bound(dp, dp + idx, arr[i]) - dp;
			dp[tmp] = arr[i];	// 갱신
			ans[i] = { tmp, arr[i] };	// 바꿔줌
		}
	}
}


int main(void) {
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		scanf("%d", arr + i);
	}

	// 가장 긴 수열의 크기 계산
	longSeq();

	printf("%d\n", idx + 1);

	// 답의 뒤에서부터 찾아봄
	for (int i = n - 1; i >= 0; i--) {
		// 가장 긴 수열의 길이를 가지고 있는가?
		if (ans[i].first == idx) {
			// 수열을 뒤에서부터 완성
			s.push(ans[i].second);
			idx--;
		}
	}

	while (!s.empty()) {
		printf("%d ", s.top());
		s.pop();	// stack이니 빼냄
	}

	printf("\n");

	return 0;
}
