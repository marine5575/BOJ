#include <cstdio>
#include <set>
#include <algorithm>

using namespace std;

int n, k;	// 가진 카드 개수, 뽑는 개수
set<int> ans;	// 정답 집합 (원소는 모두 유일)
int visited[11], arr[11];	// 방문 알림, 카드 저장고

void find(int cnt, int num) {
	// k장을 다 사용했나?
	if (cnt == k) ans.insert(num);
	else {
		// 모든 카드에 대해 살펴봄
		for (int i = 0; i < n; i++) {
			// 방문 하지 않았는가?
			if (visited[i] == 0) {
				visited[i] = 1;	// 방문 체크

				int mul = num * 10;	// 두 자리수까지 있으므로 미리 곱해놓음

				// 이미 2자리수라면 한번더 자리수를 늘려줌
				if (arr[i] > 9) mul *= 10;

				find(cnt + 1, mul + arr[i]);
				visited[i] = 0;	// 방문 해제
			}
		}
	}
}


int main(void) {
	scanf("%d %d", &n, &k);

	for (int i = 0; i < n; i++) {
		scanf("%d", arr + i);
	}

	find(0, 0);

	printf("%d\n", ans.size());	// set은 원소 각각이 유일함

	return 0;
}
