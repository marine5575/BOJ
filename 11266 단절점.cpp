#include <iostream>
#include <vector>
#include <algorithm>	// min 함수
#include <cstdio>

using namespace std;

int isCut[10001];	// 단절점인가?
int visited[10001];	// 방문 순서
vector<int> adj[10001];	// 인접 노드
int num = -1;	// 순서

int dfs(int now, int isRoot) {
	visited[now] = ++num;	// 순서 갱신
	int child;	// 연결 트리 개수
	int ret = visited[now];	// 최솟값

	// dfs이므로 끝까지 들어갔다가 나와야 됨
	for (int i = 0; i < adj[now].size(); i++) {
		int next = adj[now][i];	// 다음 노드

		// 이미 방문 했을 경우
		if (visited[next] != -1) {
			ret = min(ret, visited[next]);
			continue;
		}

		child++;
		int post = dfs(next, 0);	// 다음에 진행하는 트리에서의 최솟값

		// root가 아니고, 다음 트리 최솟값이 내 순서보다 크거나 같으면 단절점
		if (!isRoot && post >= visited[now]) {
			isCut[now] = 1;
		}

		ret = min(ret, post);	// 이전 것과 내 순서 중 더 작은거
	}

	// root로 자식 트리가 2개 이상이면 단절점
	if (isRoot && child > 1) {
		isCut[now] = 1;
	}

	return ret;
}


int main(void) {
	int V, E;	// 노드, 간선 개수

	scanf("%d %d", &V, &E);

	for (int i = 0; i < E; i++) {
		int from, to;	// 연결 노드 1, 2

		scanf("%d %d", &from, &to);

		from--; to--;	// 0부터 시작했음 좋겠어

		if (from == to) adj[from].push_back(to);	// 같으면 한번만 넣자
		else {
			adj[from].push_back(to);
			adj[to].push_back(from);
		}
	}

	fill(visited, visited + V, -1);	// 방문 배열 초기화

	for (int i = 0; i < V; i++) {
		if (visited[i] == -1) dfs(i, 1);	// 안 가본 곳이면 dfs 돌으렴
	}

	int cnt = 0;	// 총 cut 개수

	for (int i = 0; i < V; i++) {
		if (isCut[i] == 1) cnt++;
	}

	printf("%d\n", cnt);

	for (int i = 0; i < V; i++) {
		if (isCut[i] == 1) {
			printf("%d ", i + 1);
		}
	}

	return 0;
}
