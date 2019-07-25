#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
typedef pair<int, int> pii;


// 반시계: 1, 시계: -1, 일직선: 0
int ccw(pii a, pii b, pii c) {
	long long tmp = (a.first * b.second + b.first * c.second + c.first * a.second) - (b.first * a.second + c.first * b.second + a.first * c.second);

	if (tmp > 0) return 1;
	else if (tmp == 0) return 0;
	else return -1;
}

int isCross(pii a, pii b, pii l1, pii l2) {
	// 교차 시 ccw * ccw < 0
	// 그러나 이 경우는 한 점만 스쳐도 교차로 치기 때문에 경우를 나눠야 됨
	int L1_2 = ccw(a, b, l1) * ccw(a, b, l2);
	int L2_1 = ccw(l1, l2, a) * ccw(l1, l2, b);

	// 아예 교차하지 않는 경우
	if (L1_2 > 0 || L2_1 > 0) return 0;
	// a가 b보다 왼쪽에 있고, 선분들이 아예 오른쪽이나 왼쪽에 존재할 때
	if (a < b && ((l1 < a && l2 < a) || (b < l1 && b < l2))) return 0;
	// b가 a보다 왼쪽에 있고, 선분들이 아예 오른쪽이나 왼쪽에 존재할 때
	if (a > b && ((a < l1 && a < l2) || (l1 < b && l2 < b))) return 0;

	// 교차하는 경우
	return 1;
}

int isIn(pii a, pii b, pii l1, pii l2) {
	// l1 <= a <= b <= l2
	// 안쪽에 존재하는 경우
	if (l1.first <= a.first && a.first <= l2.first && l1.first <= b.first && b.first <= l2.first && l2.second <= a.second && a.second <= l1.second && l2.second <= b.second && b.second <= l1.second)
		return 1;
	return 0;
}


int main(void) {
	int t;	// 테스트 케이스
	scanf("%d", &t);

	while (t--) {
		int xs, ys, xe, ye, xl, yb, xr, yt;	// 임의의 선분 (xs, ys), (xe, ye)와 직사각형의 극단 좌표
		scanf("%d %d %d %d %d %d %d %d", &xs, &ys, &xe, &ye, &xl, &yb, &xr, &yt);

		// 선분을 이루는 점 2개
		pii l1 = { xs, ys }, l2 = { xe, ye };

		// xl에는 작은 x값, yb에는 작은 y값을 줌
		if (xl > xr) swap(xl, xr);
		if (yb > yt) swap(yb, yt);

		// 직사각형 좌표들
		pii a = { xl, yt }, b = { xr, yb };
		pii c = { xl, yb }, d = { xr, yt };
		
		// 교차하거나 안쪽에 존재하는가?
		if (isCross(l1, l2, a, c) || isCross(l1, l2, c, b) || isCross(l1, l2, b, d) || isCross(l1, l2, d, a) || isIn(l1, l2, a, b))
			printf("T\n");
		else printf("F\n");
	}

	return 0;
}
