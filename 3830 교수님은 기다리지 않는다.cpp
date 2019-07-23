#include <cstdio>

using namespace std;

int parent[100001];	// 조상 값
int diff[100001];	// 조상이 나보다 얼마나 큰가?

int find(int i) {
	// 내가 조상이다
	if (parent[i] == i) return i;
	else {
		int p = find(parent[i]);	// 부모의 조상 임시 저장
		diff[i] += diff[parent[i]];	// 부모 값을 계승
		parent[i] = p;	// 조상으로 갱신
	}

	return parent[i];	// 조상 반환
}


int main(void) {
	int n, m;	// 샘플 종류 개수, 실험실에서 한 일의 개수

	while (1) {
		scanf("%d %d", &n, &m);

		if (n == 0 && m == 0) return 0;

		char cmd;	// 어떤 일을 할 것인가
		int from, to, w;	// 비교 대상 a, b와 w (= a - b)

		// 초기화
		for (int i = 1; i <= n; i++) {
			parent[i] = i;
			diff[i] = 0;
		}

		// 한 일 만큼
		for (int i = 0; i < m; i++) {
			scanf("\n");	// 개행 문자 처리
			scanf("%c", &cmd);

			// 비교 업무
			if (cmd == '!') {
				scanf("%d %d %d", &from, &to, &w);

				// 각각의 조상 찾기
				int a = find(from);
				int b = find(to);

				// 조상이 다른가?
				if (a != b) {
					diff[b] = w + diff[from] - diff[to];	// 조상과 현재의 차이 갱신
					parent[b] = a;	// 공통 조상으로 만들기
				}
			}
			// 교수님의 질문
			else if (cmd == '?') {
				scanf("%d %d", &from, &to);

				// 조상 찾기
				int a = find(from);
				int b = find(to);

				if (a != b) printf("UNKNOWN\n");
				// 조상으로부터의 거리의 차
				else printf("%d\n", diff[to] - diff[from]);
			}
		}
	}

	return 0;
}
