#include <cstdio>
#include <algorithm>

using namespace std;
typedef long long ll;
typedef struct point {
	ll x, y;

	point operator-(point a) {
		return{ x - a.x, y - a.y };
	}
	bool operator<(const point a) const {
		bool t = x < a.x;
		if (x == a.x) t = y < a.y;
		return t;
	}
	bool operator==(const point a) const {
		return x == a.x && y == a.y;
	}
} pt;

int cnt = 0;

int ccw(point a, point b) {
	ll tmp = a.x * b.y - b.x * a.y;

	if (tmp > 0) return 1;
	else if (tmp == 0) return 0;
	else return -1;
}

int isCross(point l1, point l2, point a, point b) {
	int L1_2 = ccw(l1 - l2, l1 - a) * ccw(l1 - l2, l1 - b);
	int L2_1 = ccw(a - b, a - l1) * ccw(a - b, a - l2);

	if (L1_2 == 0 && L2_1 == 0) {
		if (l2 < l1) swap(l1, l2);
		if (b < a) swap(a, b);

		if ((a < l1 && b < l1) || (l2 < a && l2 < b)) return 0;
	}

	return L1_2 <= 0 && L2_1 <= 0;
}

int isCross_line(point l1, point l2, point a, point b) {
	int L1_2 = ccw(l1 - l2, l1 - a) * ccw(l1 - l2, l1 - b);
	int L2_1 = ccw(a - b, a - l1) * ccw(a - b, a - l2);
	
	return L1_2 < 0 && L2_1 <= 0;
}

int isCross_pt(point l1, point l2, point a, point b) {
	int L1_2 = ccw(l1 - l2, l1 - a) * ccw(l1 - l2, l1 - b);
	int L2_1 = ccw(a - b, a - l1) * ccw(a - b, a - l2);

	return L1_2 == 0 && L2_1 <= 0;
}

int isOverlap(point l1, point l2, point a, point b) {
	if (!isCross(l1, l2, a, b)) return 0;
	if (ccw(l1 - l2, l1 - a) != 0 || ccw(l1 - l2, l1 - b)) return 0;

	if (l2 < l1) swap(l1, l2);
	if (b < a) swap(a, b);
	if (l2 == a || l1 == b) return 0;
	return 1;
}


int main(void) {
	int t, i;
	scanf("%d", &t);

	while (t--) {
		cnt = 0;
		pt l1, l2;
		pt rec[5];
		scanf("%d %d %d %d", &rec[0].x, &rec[0].y, &rec[2].x, &rec[2].y);
		scanf("%d %d %d %d", &l1.x, &l1.y, &l2.x, &l2.y);
		rec[1] = { rec[0].x, rec[2].y };
		rec[3] = { rec[2].x, rec[0].y };
		rec[4] = rec[0];

		if (l2 < l1) swap(l1, l2);

		for (i = 0; i < 4; i++) {
			if (isCross(l1, l2, rec[i], rec[i + 1])) {
				break;
			}
		}
		if (i == 4) {
			printf("0\n");
			continue;
		}

		for (i = 0; i < 4; i++) {
			if (isOverlap(l1, l2, rec[i], rec[i + 1])) {
				break;
			}
		}
		if (i != 4) {
			printf("4\n");
			continue;
		}

		int cnt = 0, cnt2 = 0;
		for (i = 0; i < 4; i++) {
			if (isCross_line(l1, l2, rec[i], rec[i+1])) cnt++;
			if (isCross_pt(l1, l2, rec[i], rec[i + 1])) cnt2++;
		}

		printf("%d\n", cnt + cnt2 / 2);
	}

	return 0;
}
