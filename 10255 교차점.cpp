#include <cstdio>
#include <algorithm>

using namespace std;
typedef long long ll;
typedef struct point {
	ll x, y;	// x, y 좌표
	 
	// 뺄셈 
	point operator-(point a) {
		return{ x - a.x, y - a.y };
	}
	// 비교 
	bool operator<(const point a) const {
		bool t = x < a.x;
		if (x == a.x) t = y < a.y;
		return t;
	}
	// 같은지 비교 
	bool operator==(const point a) const {
		return x == a.x && y == a.y;
	}
} pt;


// 반시계: 양수, 시계: 음수, 일직선: 0 
int ccw(point a, point b, point c) {
	ll tmp = a.x * b.y + b.x * c.y + c.x * a.y - (b.x * a.y + c.x * b.y + a.x * c.y);

	if (tmp > 0) return 1;
	else if (tmp == 0) return 0;
	else return -1;
}

// 교차하는가? 
int isCross(point l1, point l2, point a, point b) {
	int L1_2 = ccw(l1, l2, a) * ccw(l1, l2, b);	// 선분을 이어놓고 직사각형 꼭짓점에 대해 판별 
	int L2_1 = ccw(a, b, l1) * ccw(a, b, l2);	// 직사각형 변에 대한 선분의 점들 판별 

	// 서로 평행한가? 
	if (L1_2 == 0 && L2_1 == 0) {
		// 더 작은 값을 l1, a에 저장 
		if (l2 < l1) swap(l1, l2);
		if (b < a) swap(a, b);
		
		// 직사각형 변의 완전 바깥에 존재하는가? 
		if ((l1 < a && l2 < a) || (a < l1 && b < l1)) return 0;
	}
	
	// 교차하면 1, 아니면 0 
	return L1_2 <= 0 && L2_1 <= 0;
}

// 선분에 하나만 교차하는지 판별 
int isCross_line(point l1, point l2, point a, point b) {
	int L1_2 = ccw(l1, l2, a) * ccw(l1, l2, b);
	int L2_1 = ccw(a, b, l1) * ccw(a, b, l2);
	
	// 선분 기준으로 꼭짓점은 나뉘지만, 직사각형의 변 기준으로 선분은 나뉘지 않음 
	return L1_2 < 0 && L2_1 <= 0;
}

// 꼭짓점으로 교차하는지 판별 
int isCross_pt(point l1, point l2, point a, point b) {
	int L1_2 = ccw(l1, l2, a) * ccw(l1, l2, b);
	int L2_1 = ccw(a, b, l1) * ccw(a, b, l2);
	
	// 선분 기준으로도 직사각형의 변 기준으로도 일직선 상에 있는 점 존재 
	return L1_2 == 0 && L2_1 <= 0;
}

// 겹치는가? 
int isOverlap(point l1, point l2, point a, point b) {
	// 교차하지 않는가? 
	if (!isCross(l1, l2, a, b)) return 0;
	// 두 선이 서로 평행하지 않은가? 
	if (ccw(l1, l2, a) != 0 || ccw(l1, l2, b) != 0) return 0;

	// 더 작은 값을 l1, a에 남김 
	if (l2 < l1) swap(l1, l2);
	if (b < a) swap(a, b);
	// 끝쪽만 닿는가? 
	if (l2 == a || l1 == b) return 0;
	
	// 나머지는 모두 겹치는 경우 
	return 1;
}


int main(void) {
	int t, i;	// 테스트 케이스, 나중에 돌릴 인자 
	scanf("%d", &t);

	while (t--) {
		pt l1, l2;	// 선분의 양 끝 점 
		pt rec[5];	// 직사각형 좌표 넣을 곳 
		scanf("%lld %lld %lld %lld", &rec[0].x, &rec[0].y, &rec[2].x, &rec[2].y);
		scanf("%lld %lld %lld %lld", &l1.x, &l1.y, &l2.x, &l2.y);
		rec[1] = { rec[0].x, rec[2].y };	// 왼쪽 위 
		rec[3] = { rec[2].x, rec[0].y };	// 오른쪽 아래 
		rec[4] = rec[0];	// 왼쪽 아래 

		// 더 작은 값을 l1으로 만듬 
		if (l2 < l1) swap(l1, l2);

		// 0. 교점이 없는 경우
		 
		for (i = 0; i < 4; i++) {
			// 교차하는가? 
			if (isCross(l1, l2, rec[i], rec[i + 1])) {
				break;
			}
		}
		// 교차하지 않는 경우 
		if (i == 4) {
			printf("0\n");
			continue;
		}

		// 1. 아예 겹치는 경우
		 
		for (i = 0; i < 4; i++) {
			// 겹치는가? 
			if (isOverlap(l1, l2, rec[i], rec[i + 1])) {
				break;
			}
		}
		// 겹치는 경우 
		if (i != 4) {
			printf("4\n");
			continue;
		}

		// 교차하는 경우
		// 2. 선분에 점 하나 교차하는 경우
		// 3. 선분 양 끝점 중 하나와 교차하는 경우
		 
		int cnt = 0, cnt2 = 0;	// 선분 교차 수, 꼭짓점 교차 수 
		for (i = 0; i < 4; i++) {
			// 선분 교차하는가? 
			if (isCross_line(l1, l2, rec[i], rec[i+1])) cnt++;
			// 점 교차하는가? 
			if (isCross_pt(l1, l2, rec[i], rec[i + 1])) cnt2++;
		}

		printf("%d\n", cnt + cnt2 / 2);	// 점을 셀 때 선분당 한 번 세었으므로 2로 나누어야 됨 
	}

	return 0;
}
