#include <cstdio>
#include <vector>

using namespace std;
typedef pair<int, int> pii;

pii point[10001];	// 입력 좌표 값
int n;	// 좌표 개수
double sum = 0;	// 면적의 합

void area() {
	double px = 0, py = 0;	// 외부 혹은 내부의 한 점

	// (px, py), (x1, y1), (x2, y2)가 이루는 삼각형의 넓이
	// 반시계 방향이면 양수, 시계 방향이면 양수가 나옴
	for (int i = 0; i < n; i++) {
		double x1 = point[i].first, y1 = point[i].second;
		double x2 = point[i + 1].first, y2 = point[i + 1].second;
		double A = ((px*y1 + x1*y2 + x2*py) - (x1*py + x2*y1 + px *y2));
		sum += A;
	}
}


int main(void) {
	scanf("%d", &n);

	for (int i = 0, x, y; i < n; i++) {
		scanf("%d %d", &x, &y);
		point[i] = { x, y };
	}

	// 마지막에는 시작점도 포함해야 됨
	point[n] = point[0];

	area();

	sum = abs(sum);	// 모두 시계 방향이면 음수 면적이 나올 수 있음

	printf("%.1lf\n", sum / 2);
	
	return 0;
}
