/***************************/
// BOJ 1967 트리의 지름
// 핵심: BFS + 트리
//			 => 트리는 이전에 갔던 곳만 체크하면 됨.
//					또한, 루트에서 거리가 가장 먼 곳에서 찾아보는 것이 정답
/***************************/
#include <stdio.h>
#include <vector>
#include <queue>
#define MAX ((int)1e4 + 1)

using namespace std;

typedef struct pt {
	int idx, w;
} pt;

int n, Max;	// 노드의 개수, 트리의 지름
vector<pt> graph[MAX];

void input_Data(void) {
	scanf("%d", &n);

	for (int i = 0, from, to, w; i < n - 1; i++) {
		scanf("%d %d %d", &from, &to, &w);

		pt tmp = { to, w };
		graph[from].push_back(tmp);

		tmp.idx = from;
		graph[to].push_back(tmp);
	}
}

int bfs(int start) {
	// start에서 시작해서 가장 먼 거리를 찾는 함수

	int idx = -1;	// 가장 먼 거리에 있는 노드 번호
	char visited[MAX] = { 0, };
	queue<pt> q;
	pt init = { start, 0 };
	q.push(init);
	visited[start] = 1;

	while (!q.empty()) {
		pt cur = q.front(); q.pop();	// 현재 위치

		for (int i = 0; i < graph[cur.idx].size(); i++) {
			pt next = graph[cur.idx][i];	// 다음 위치

			// 이미 다녀감
			if (visited[next.idx]) continue;

			pt tmp = { next.idx, cur.w + next.w };
			q.push(tmp);
			visited[next.idx] = 1;

			// 최대값 갱신
			if (Max < cur.w + next.w) {
				Max = cur.w + next.w;
				idx = next.idx;
			}
		}
	}

	return idx;
}

int sol(void) {
	int far = bfs(1);	// 루트에서 가장 먼 거리에 있는 노드를 찾음
	int tmp = bfs(far);	// 그 노드에서 가장 먼 거리에 있는 노드 찾기

	return Max;
}


int main(void) {
	input_Data();

	printf("%d\n", sol());

	return 0;
}
