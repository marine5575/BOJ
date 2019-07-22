#include <cstdio>

using namespace std;

int arr[101];	// 받을 배열
// Case[i][j] : i번째 인자까지 이용하여 j라는 값을 만들 수 있는 경우의 수
long long Case[101][101];	// 경우의 수가 클지도 모르므로


int main(void) {
	int n;	// 숫자 개수

	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		scanf("%d", arr + i);
	}

	Case[0][arr[0]] = 1;	// 초기화: 0번째에 첫번째 숫자를 만들 수 있는 경우의 수는 1가지이다

	// 맨마지막 n-1번째는 결과값 도출에 사용
	for (int i = 1; i < n - 1; i++) {
		// 일일이 찾아보기
		for (int j = 0; j <= 20; j++) {
			// (i - 1)번째 인자까지 사용하여 j를 만들 수 있는 경우만 통과
			if (Case[i - 1][j] == 0) continue;

			// 상근이는 0 ~ 20까지밖에 숫자를 모름
			if (j + arr[i] < 21) Case[i][j + arr[i]] += Case[i - 1][j];
			if (j - arr[i] >= 0) Case[i][j - arr[i]] += Case[i - 1][j];
		}
	}

	printf("%lld\n", (long long)Case[n - 2][arr[n - 1]]);


	return 0;
}
