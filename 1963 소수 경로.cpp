/*************************/
// BOJ 1963 소수 경로
// 핵심: BFS + 에라토스테네스의 체
/*************************/
#include <stdio.h>
#include <queue>
#define MAX 10000

using namespace std;

int tc, from, to;	// 테스트 케이스 개수, 처음 소수, 원하는 소수
char primes[MAX + 1];	// primes[i] = (0 or 1) : i가 (소수 or 소수가 아님)

void input_Data(void) {
	scanf("%d %d", &from, &to);
}

void find_Primes(void) {
	// 에라토스테네스의 체

	primes[1] = 1;

	for (int i = 2; i <= (MAX / 2); i++) {
		if (primes[i]) continue;

		for (int j = 2; i * j < MAX; j++) {
			primes[i * j] = 1;
		}
	}
}

int bfs(void) {
	// from에서 시작해서 to로 변하게 하는 함수

	int visited[MAX + 1] = { 0, };	// visited[i] = i까지 오는데 걸리는 횟수
	queue<int> q;
	q.push(from);
	visited[from] = 1;

	while (!q.empty()) {
		int cur = q.front(); q.pop();	// 현재 위치
		int cnt = visited[cur];	// 여기까지 오는데 걸린 횟수

		// 도착함
		if (cur == to) return cnt - 1;

		// 천의 자리
		for (int i = 1; i <= 9; i++) {
			int digit = cur / 1000;	// 천의 자리수
			// 현재 위치랑 동일
			if (digit == i) continue;

			int next = cur + (i - digit) * 1000;	// 바꿀 숫자
			// 소수가 아님 or 이미 들림
			if (primes[next] || visited[next]) continue;
			// 원하는 값임
			if (next == to) return cnt;

			q.push(next);
			visited[next] = cnt + 1;
		}

		// 백의 자리수
		for (int i = 0; i <= 9; i++) {
			int digit = (cur / 100) % 10;	// 현재 자리수
			// 현재 있는 자리수와 같음
			if (digit == i) continue;

			int next = cur + (i - digit) * 100;	// 바꿀 숫자
			// 소수가 아님 or 이미 들림
			if (primes[next] || visited[next]) continue;
			// 원하는 값임
			if (next == to) return cnt;

			q.push(next);
			visited[next] = cnt + 1;
		}

		// 십의 자리수
		for (int i = 0; i <= 9; i++) {
			int digit = (cur / 10) % 10;	// 현재 자리수
			// 현재 있는 자리수와 같음
			if (digit == i) continue;

			int next = cur + (i - digit) * 10;	// 바꿀 숫자
			// 소수가 아님 or 이미 들림
			if (primes[next] || visited[next]) continue;
			// 원하는 값임
			if (next == to) return cnt;

			q.push(next);
			visited[next] = cnt + 1;
		}

		// 일의 자리수
		for (int i = 0; i <= 9; i++) {
			int digit = cur % 10;		// 현재 자리수
			// 현재 있은 자리수와 같음
			if (digit == i) continue;

			int next = cur + (i - digit);	// 바꿀 숫자
			// 소수가 아님 or 이미 들림
			if (primes[next] || visited[next]) continue;
			// 원하는 값임
			if (next == to) return cnt;

			q.push(next);
			visited[next] = cnt + 1;
		}
	}

	return -1;	// 실패함
}


int main(void) {
	scanf("%d", &tc);

	find_Primes();	// 소수를 미리 찾아놓기

	while (tc--) {
		input_Data();
		int ans = bfs();	// 정답

		// 가능할 때
		if (ans != -1) printf("%d\n", ans);
		// 불가능
		else printf("Impossible\n");
	}

	return 0;
}
