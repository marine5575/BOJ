#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

vector<int> arr;	// input
int n;	// input 개수
int dp[5][5][100001];	// dp[left][right][i] : 왼발 위치, 오른발 위치, 이번이 몇번째 움직임? 일 때 최소 힘

int check(int from, int to) {
	// 시작점에서 출발
	if (from == 0) return 2;
	// 같은 위치로 돌아옴
	else if (from == to) return 1;
	// 반대편에 위치
	else if (abs(from - to) == 2) return 4;
	// 인접한 곳에 위치
	else return 3;
}

int find(int left, int right, int i) {
	// 마지막 차례임
	if (i == n) return 0;
	// 예전에 갱신한 최솟값
	if (dp[left][right][i] != -1) return dp[left][right][i];

	// 왼발이 먼저 움직일 때
	int l = find(arr[i], right, i + 1) + check(left, arr[i]);
	// 오른발이 먼저 움직일 때
	int r = find(left, arr[i], i + 1) + check(right, arr[i]);

	// 최소값 갱신
	return dp[left][right][i] = min(l, r);
}


int main(void) {
	while (1) {
		int input;	// 입력값
		scanf("%d", &input);

		if (input == 0) break;

		arr.push_back(input);
	}

	n = arr.size();

	memset(dp, -1, sizeof(dp));	// 초기화

	// 양발 모으고 시작
	printf("%d\n", find(0, 0, 0));

	return 0;
}
