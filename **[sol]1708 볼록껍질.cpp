#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <limits.h>
#include <string.h>
#include <queue>
#include <math.h>
#include <unordered_set>
#include <stdlib.h>

using namespace std;

typedef pair<int, int> pii;
typedef long long lld;
struct pos {
	lld x;
	lld y;

	bool operator<(pos a) {
		if (x != a.x) return x < a.x;
		return y < a.y;
	}
	bool operator>(pos a) {
		if (x != a.x) return x > a.x;
		return y > a.y;
	}
	bool operator<=(pos a) {
		if (x != a.x) return x <= a.x;
		return y <= a.y;
	}
	bool operator>=(pos a) {
		if (x != a.x) return x >= a.x;
		return y >= a.y;
	}

};

lld ccw(pos a, pos b, pos c) {
	return (a.x * b.y + b.x*c.y + c.x * a.y) - (a.y * b.x + b.y * c.x + c.y * a.x);
}

// Monotone Chain
int main() {
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	int n;
	cin >> n;
	vector<pos> v(n);
	for (int i = 0; i < n; i++) {
		cin >> v[i].x >> v[i].y;
	}

	// 1) x축 정렬
	sort(v.begin(), v.end());
	vector<int> up, down;

	// 2) 위 껍질 탐색
	for (int i = 0; i < n; i++) {
		while (up.size() >= 2 && ccw(v[up[up.size() - 2]], v[up[up.size() - 1]], v[i]) >= 0) {
			up.pop_back();
		}
		up.push_back(i);
	}

	// 3) 아래껍질 탐색
	for (int i = n - 1; i >= 0; i--) {
		while (down.size() >= 2 && ccw(v[down[down.size() - 2]], v[down[down.size() - 1]], v[i]) >= 0) {
			down.pop_back();
		}
		down.push_back(i);
	}

	// 4) 병합
	unordered_set<int> s;
	for (int i = 0; i < up.size(); i++) {
		if (s.find(up[i]) == s.end()) s.insert(up[i]);
	}
	for (int i = 0; i < down.size(); i++) {
		if (s.find(down[i]) == s.end()) s.insert(down[i]);
	}

	cout << s.size();
	return 0;
}
