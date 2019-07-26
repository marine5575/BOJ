#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
typedef struct point {
	long long x, y;	// 그냥 좌표는 롱롱으로 받자.. 나중에 값 달라진다......

	bool operator<(const point a) const {
		bool t = x < a.x;
		if (x == a.x) t = y < a.y;
		return t;
	}
} pt;

vector<pt> u, d;	// 위쪽 볼록껍질, 아래쪽 볼록껍질

int ccw(pt a, pt b, pt c) {
	long long tmp = a.x * b.y + b.x * c.y + c.x * a.y - (b.x * a.y + c.x * b.y + a.x * c.y);

	// 반시계
	if (tmp > 0) return 1;
	// 일직선
	else if (tmp == 0) return 0;
	// 시계
	else return -1;
}


int main(void) {
	int n;	// 좌표 개수
	scanf("%d", &n);

	vector<pt> arr;	// 주어진 좌표

	for (int i = 0; i < n; i++) {
		long long x, y;	// 미리미리 long long으로..
		scanf("%lld %lld", &x, &y);
		arr.push_back({ x, y });
	}

	// 좌표 오름차순 정렬
	sort(arr.begin(), arr.end());

	// 위쪽 볼록껍질 구하기
	for (int i = 0; i < n; i++) {
		// 반시계 방향이면 오목한 곳
		while (u.size() >= 2 && ccw(u[u.size() - 2], u[u.size() - 1], arr[i]) >= 0) {
			u.pop_back();
		}
		u.push_back(arr[i]);
	}

	// 아래쪽 볼록껍질 구하기
	for (int i = n - 1; i >= 0; i--) {
		// 반시계 방향이면 오목한 곳
		while (d.size() >= 2 && ccw(d[d.size() - 2], d[d.size() - 1], arr[i]) >= 0) {
			d.pop_back();
		}
		d.push_back(arr[i]);
	}

	// 양끝은 겹치므로 2 빼줌
	printf("%d\n", u.size() + d.size() - 2);

	return 0;
}
