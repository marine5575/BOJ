#include <cstdio>
#include <algorithm>
#define MOD 1000000007
#define MAX 10001

using namespace std;
typedef long long ll;

ll dp[2][MAX];	// dp[0 or 1][h] : (과거 or 현재) 상태에 h 높이가 있을 때 경우의 수
int arr[MAX];	// input


int main(void) {
	int n;	// 제단 열 수
	scanf("%d", &n);

	for (int i = 1; i <= n; i++) {
		scanf("%d", arr + i);
	}

	// arr[1] = 0일 때는 시작 지점이란 뜻
	// arr[1] = -1일 때는 0밖에 못 되기 때문에 경우의 수 1
	// arr[1] >= 1일 때는 0 이외의 값이 들어올 수 없어 경우의 수 0
	dp[0][0] = (arr[1] < 1 ? 1 : 0);

	// 시작지점 이외의 노드 따져보기
	for (int i = 2; i <= n; i++) {
		// 초기화
		fill_n(&dp[1][0], MAX, 0);

		// 도둑이 훔쳐간 곳
		if (arr[i] == -1) {
			// 첫번째 것은 항상 갱신
			dp[1][0] = (dp[0][0] + dp[0][1]) % MOD;

			// 두번째 것들은 왼쪽, 자기자신, 오른쪽 살펴보고 결정
			for (int j = 1; j <= MAX / 2; j++) {
				dp[1][j] = (dp[0][j - 1] + dp[0][j] + dp[0][j + 1]) % MOD;
			}
		}
		// 공터일 때
		else if (arr[i] == 0) {
			// 처음에 초기화 해놓았으니 다시 옮겨놓기
			dp[1][0] = (dp[0][0] + dp[0][1]) % MOD;
		}
		// 높이 존재할 때
		else {
			// 지난번 것들의 경우의 수 다 더해보기
			dp[1][arr[i]] = (dp[0][arr[i] - 1] + dp[0][arr[i]] + dp[0][arr[i] + 1]) % MOD;
		}

		// 현재 상태는 좀이따 과거가 될 것임
		swap(dp[0], dp[1]);
	}

	// 맨 마지막에 과거로 만들어버렸으므로
	// 맨 처음에 있는 놈이 모든 경우의 수를 다 가지고 있음
	printf("%lld\n", dp[0][0]);

	return 0;
}
