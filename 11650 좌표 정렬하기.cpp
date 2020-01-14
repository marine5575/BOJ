#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// 좌표 구조체 
typedef struct pt {
	int x, y;
} pt;
	
// 구조체 비교 연산자 재정의 
bool operator< (const pt &p1, const pt &p2) {
	if(p1.x < p2.x) return true;
	else if(p1.x == p2.x && p1.y < p2.y) return true;
	else return false;
}

pt points[100001];	// input 좌표 

int main(void) {
	cin.tie(0);
	ios::sync_with_stdio(0);
	
	int n;
	cin >> n;
	
	for(int i = 0; i < n; i++) {
		cin >> points[i].x >> points[i].y;
	}
	
	sort(points, points + n);	// 정렬하면 재정의된 비교 연산자를 이용하여 정렬됨 
	
	for(int i = 0; i < n; i++) {
		cout << points[i].x << " " << points[i].y << "\n";
	}
	
	return 0;
}
