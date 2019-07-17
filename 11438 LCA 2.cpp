#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>
#define MAX 18	// ceil(log2(100000)) + 1

using namespace std;

int parent[100000][MAX];	// parent[i][k]: i의 2^k번째 부모
int dep[100000];	// 노드가 위치한 곳의 깊이
vector<int> adj[100000];	// 인접한 애들 모임


void dfsTree(int cur) {
	// vector front에 있는 노드 불러오기
	for (int next : adj[cur]) {
		// 아직 노드 배치를 안 했을 경우
		if (dep[next] == -1) {
			parent[next][0] = cur;	// 현재 있는 노드가 가져온 놈의 아버지
			dep[next] = dep[cur] + 1;	// 가져온 놈의 깊이는 아버지 + 1
			dfsTree(next);
		}
	}
}


int main(void) {
	int N;	// 노드의 개수

	scanf("%d", &N);

	// (N - 1)개의 줄 입력 받음
	for (int i = 0; i < N - 1; i++) {
		int a, b;	// 정점 2개

		scanf("%d %d", &a, &b);
		// 배열로 사용할거라 하나씩 뺌
		a--;
		b--;
		// 인접 리스트에 서로 넣기
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	// parent, dep 배열 초기화
	memset(parent, -1, sizeof(parent));	// #include <cstring>
	fill(dep, dep + N, -1);	// fill(arr, arr+n, NUM) : arr[0]에서 n번째까지 NUM 값으로 초기화
	dep[0] = 0;	// 첫 노드의 깊이는 무조건 0

	// dfs로 tree 만들어줌
	dfsTree(0);

	// parent 배열 채우기
	for (int j = 0; j < MAX - 1; j++) {
		for (int i = 1; i < N; i++) {	// 0번째는 아버지 없음
			// 아버지가 이미 존재한다면
			if (parent[i][j] != -1) {
				parent[i][j + 1] = parent[parent[i][j]][j]; // 나의 할아버지는 아버지의 아버지다.
			}
		}
	}

	int M;	// 질문 개수
	scanf("%d", &M);

	for (int i = 0; i < M; i++) {
		int n1, n2;	// 알고 싶은 노드 2개
		scanf("%d %d", &n1, &n2);
		n1--; n2--;	// 마찬가지로 배열 index로 쓰고 싶어서

		if (dep[n1] < dep[n2]) swap(n1, n2);	// 난 n1이 더 깊으면 좋겠더라..

		int diff = dep[n1] - dep[n2];	// n1, n2 깊이 사이의 차이

		// n1의 깊이가 n2와 같아지도록 끌어올림
		for (int j = 0; diff != 0; j++) {
			if (diff % 2 == 1) n1 = parent[n1][j];
			diff /= 2;
		}

		int now = dep[n2];	// n2의 깊이

		if (n1 != n2) {
			// 2^17, 2^16, ... , 2, 1 순으로 조상 살펴보기
			for (int j = now - 1; j >= 0; j--) {
				// 조상이 다를 때만 n1, n2 update
				if (parent[n1][j] != parent[n2][j] && parent[n1][j] != -1) {
					n1 = parent[n1][j];
					n2 = parent[n2][j];
				}
			}

			n1 = parent[n1][0];	// 마지막으로 저장한 것이 n1, n2는 달라도 아버지는 같을 때이므로 한 칸 올려줌
		}

		printf("%d\n", n1 + 1);	// 결과 출력
	}

	return 0;
}
