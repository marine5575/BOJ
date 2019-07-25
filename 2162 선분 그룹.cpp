#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
typedef pair<int, int> pii;

pair<pii, pii> line[3001];	// 선분을 이루고 있는 (x1, y1), (x2, y2)
int parent[3001];	// 조상님들
int num[3001];	// 해당 조상님에 몇 명 속해 있는지 저장

int find(int i) {
	if (parent[i] == i) return i;	// 내가 조상님이다

	// 조상님 찾아서 갱신
	return parent[i] = find(parent[i]);
}

void uni(int a, int b) {
	int aRoot = find(a);	// a의 조상님
	int bRoot = find(b);	// b의 조상님

	// 조상님끼리 비교해서 더 작은 조상님으로 통일
	if (aRoot < bRoot) parent[bRoot] = aRoot;
	else parent[aRoot] = bRoot;
}

int ccw(pii a, pii b, pii c) {
	// 반시계 : 양수
	// 시계 : 음수
	// 일직선: 0
	long long tmp = (a.first * b.second + b.first  * c.second + c.first * a.second) - (b.first * a.second + c.first * b.second + a.first * c.second);

	if (tmp > 0) return 1;
	else if (tmp == 0) return 0;
	else return -1;
}

int search(int a, int b) {
	pii p1 = line[a].first, p2 = line[a].second;	// 선분 a의 꼭짓점들
	pii p3 = line[b].first, p4 = line[b].second;	// 선분 b의 꼭짓점들

	// 선분 1가 2의 꼭짓점들을 나눠놓았는지 봄
	int L1_2 = ccw(p1, p2, p3) * ccw(p1, p2, p4);
	// 선분 2가 1의 꼭짓점들을 나눠놓았는지 봄
	int L2_1 = ccw(p3, p4, p1) * ccw(p3, p4, p2);

	// 두 선분의 꼭짓점 중 하나가 다른 선분에 포함되는 점이 있거나
	// 평행한 것
	if (L1_2 == 0 && L2_1 == 0) {
		// p1, p3를 더 작은 걸로 놓고 싶음
		if (p1 > p2) swap(p1, p2);
		if (p3 > p4) swap(p3, p4);

		// 평행하지 않으면 1, 평행하면 0
		return p1 <= p4 && p3 <= p2;
	}

	// 교차하면 1, 아니면 0
	return L1_2 <= 0 && L2_1 <= 0;
}



int main(void) {
	int n;	// 선분 개수
	scanf("%d", &n);

	for (int i = 0, x1, y1, x2, y2; i < n; i++) {
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		line[i] = { { x1, y1 },{ x2, y2 } };

		parent[i] = i;
		num[i] = 0;
	}

	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			// 교차하는가?
			if (search(i, j)) {
				// 조상님 갱신
				uni(i, j);
			}
		}
	}

	int maxi = 0, cnt = 0;	// 대왕 조상님의 가족 수, 조상님 수

	for (int i = 0; i < n; i++) {
		// 내가 조상님인가?
		if (parent[i] == i) cnt++;

		int a = find(i);	// i의 조상님
		num[a]++;

		// 최대값 갱신
		if (num[a] > maxi) maxi = num[a];
	}

	printf("%d\n%d\n", cnt, maxi);

	return 0;
}
