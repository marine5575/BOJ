#include <cstdio>
#include <vector>

using namespace std;

int arr[100001];	// 처음 input


struct fenwick {
	vector<int> tree;	// tree

	fenwick(int n) :tree(n + 1) {};	// 생성자

	void update(int i, int num) {
		// 1부터 시작함
		while (i < tree.size()) {
			tree[i] += num;	// 갱신

			i += (i & -i);	// 1, 2, 4.. 순으로 올라감
		}
	}

	int query(int i) {
		int sum = 0;	// 결과 값

		while (i > 0) {
			sum += tree[i];	// 갱신
			i -= (i & -i);	// 마지막 1들을 뺌
		}

		return sum;
	}
};


int main(void) {
	int n, m, start, end;	// 수의 개수, 범위 개수, 시작, 끝

	scanf("%d %d", &n, &m);

	fenwick fw(n);	// 구조체 생성

	for (int i = 1; i <= n; i++) {
		scanf("%d", arr + i);
		fw.update(i, arr[i]);	// 미리 갱신
	}

	for (int k = 0; k < m; k++) {
		scanf("%d %d", &start, &end);
		printf("%d\n", fw.query(end) - fw.query(start - 1));	// 시작 지점 이전 것까지 빼야 됨
	}

	return 0;
}
