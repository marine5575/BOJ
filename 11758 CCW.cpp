#include <cstdio>

using namespace std;


int main(void) {
	int x1, y1, x2, y2, x3, y3;	// 좌표들 (x1, y1), (x2, y2), (x3, y3)

	scanf("%d %d", &x1, &y1);
	scanf("%d %d", &x2, &y2);
	scanf("%d %d", &x3, &y3);

	// 외적 구하기
	// 반시계 : +, 시계 : -, 일직선: 0
	int ccw = (x1*y2 + x2*y3 + x3*y1) - (x2*y1 + x3*y2 + x1*y3);

	if (ccw > 0) printf("1\n");
	else if (ccw == 0) printf("0\n");
	else printf("-1\n");

	return 0;
}
