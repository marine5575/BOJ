#include <cstdio>
#include <vector>
#include <algorithm>
#define INF 987654321

using namespace std;
typedef pair<int, int> pii;

int dp[501][501];
pii matrix[501];	// matrix[i] = (r, c)

/*
matrixMul(left, right) : left부터 right까지의 연산 최솟값
*/
int matrixMul(int l, int r) {
	// 만약 자기 자신일 경우
	if (l == r) return 0;

	// 주소값 불러옴
	int &ans = dp[l][r];

	if (ans != 0) return ans;

	ans = INF;	// 최소값 찾아야되므로

	// pivot을 left부터 right까지 하나씩 구간 나눠봄
	for (int i = l; i < r; i++) {
		// 더 작은 값 갱신
		ans = min(ans, matrixMul(l, i) + matrixMul(i + 1, r) + matrix[l].first * matrix[i].second * matrix[r].second);
	}

	return ans;
}


int main(void) {
	int  n;	// 행렬 수

	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		scanf("%d %d", &matrix[i].first, &matrix[i].second);
	}

	printf("%d\n", matrixMul(0, n - 1));

	return 0;
}
