#include <cstdio>
#include <vector>

using namespace std;
typedef long long ll;
ll fac[21];	// 팩토리얼 저장
int visited[21];	// 방문
int arr[21];	// 수열 받는 것


int main(void) {
	int n, num;	// input, 소문제 번호

	scanf("%d", &n);
	scanf("%d", &num);
	
	// 모든 팩토리얼 먼저 만들어 놓기
	fac[0] = 1;
	for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i;

	// k번째 수열을 나타내는 n개의 수 출력
	if (num == 1) {
		ll k;	// k번째 수열
		scanf("%lld", &k);

		for (int i = 0; i < n; i++) {
			int at = 1;	// 지금 어딨는지

			for (int j = 1, cnt = 1; j <= n; j++)
			{
				// 이미 방문했다면 세지 x
				if (visited[j]) continue;
				// k가 속한 그룹 찾기
				if (k <= at * fac[n - i]) {
					k -= ((at - 1) * fac[n - i]);	// 속한 그룹에서 몇 번째인지
					printf("%d ", j);
					visited[j] = 1;	// 방문 표시
					break;
				}
				at++;
			}
		}
	}
		else {
			ll k = 1;	// 주어진 수열의 순서

			// 모든 수를 다 살펴봄
			for (int i = 1; i <= n; i++) {
				int at = 0;	// 방문하지 않은 것들 수

				scanf("%d", arr + i);

				for (int j = 1; j < arr[i]; j++) {
					// 방문 하지 않았을 때 증가
					if (visited[j] == 0) at++;
				}

				k += at * fac[n - i];	// 이정도 것들이 앞에 있음
				visited[arr[i]] = 1;	// 방문 표시
			}

			printf("%lld\n", k);
		}

	return 0;
}
