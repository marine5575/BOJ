#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;
typedef long long ll;
typedef struct point {
	int x, y;

	point operator-(point a) {
		return{ x - a.x, y - a.y };
	}

	bool operator<(const point a) const {
		bool t = x < a.x;
		if (x == a.x) t = y < a.y;
		return t;
	}
} pt;

int ccw(pt a, pt b, pt c) {
	ll tmp = (a.x * b.y + b.x*c.y + c.x * a.y) - (a.y * b.x + b.y * c.x + c.y * a.x);

	if (tmp < 0) return 0;
	else return 1;
}

vector<pt> Uconvex, Dconvex;


int main(void) {
	int n;
	scanf("%d", &n);

	vector<pt> arr;

	for (int i = 0, x, y; i < n; i++) {
		scanf("%d %d", &x, &y);
		arr.push_back({ x, y });
	}

	sort(arr.begin(), arr.end());

	int un = 0, dn = 0;

	for (int i = 0; i < n; i++) {
		while (un >= 2 && ccw(Uconvex[un - 2], Uconvex[un - 1], arr[i])) Uconvex.pop_back(), --un;
		Uconvex.push_back(arr[i]);
		un++;
	}

	reverse(arr.begin(), arr.end());

	for (int i = 0; i < n; i++) {
		while (dn >= 2 && ccw(Dconvex[dn - 2], Dconvex[dn - 1], arr[i])) Dconvex.pop_back(), --dn;
		Dconvex.push_back(arr[i]);
		dn++;
	}

	int size = Uconvex.size() + Dconvex.size();

	printf("%d\n", size - 2);

	return 0;
}
