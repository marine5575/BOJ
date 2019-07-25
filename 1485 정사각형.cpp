#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>	// sqrt

using namespace std;
typedef struct point {
	int x, y;	// x, y 좌표

	// point끼리 빼주기
	point operator- (point a) {
		return{ x - a.x, y - a.y };
	}
	// point끼리 비교
	bool operator<(const point a) const
	{
		bool t = x < a.x;
		if (x == a.x) t = y > a.y;
		return t;
	}
} Point;


// 서로 직각인가?
int isOrth(Point a, Point b) {
	int tmp = a.x * b.x + a.y * b.y;	// 내적 값
	return tmp == 0 ? 1 : 0;
}

// 선분의 길이 구하기
double getLen(Point a, Point b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) *(a.y - b.y));
}


int main(void) {
	int t;	// 테스트 케이스 개수
	scanf("%d", &t);

	while (t--) {
		Point arr[4];	// 사각형의 꼭지점 4개
		scanf("%d %d", &arr[0].x, &arr[0].y);
		scanf("%d %d", &arr[1].x, &arr[1].y);
		scanf("%d %d", &arr[2].x, &arr[2].y);
		scanf("%d %d", &arr[3].x, &arr[3].y);

		// 오름차순으로 정렬
		sort(arr, arr + 4);

		// 변들의 길이
		double a = getLen(arr[0], arr[1]), b = getLen(arr[0], arr[2]), c = getLen(arr[1], arr[3]), d = getLen(arr[2], arr[3]);

		// 모두 길이가 같은가?
		if (a == b && b == c && c == d) {
			// 모두 직각을 이루는가?
			if (isOrth(arr[0] - arr[1], arr[0] - arr[2]) && isOrth(arr[1] - arr[0], arr[1] - arr[3]) && isOrth(arr[3] - arr[1], arr[3] - arr[2]) && isOrth(arr[2] - arr[3], arr[2] - arr[0])) {
				printf("1\n");
				continue;
			}
		}

		printf("0\n");
	}

	return 0;
}
