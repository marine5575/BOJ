#include <cstdio>
#include <vector>
#include <algorithm>
#define INF 987654321

using namespace std;


int main(void) {
	int n, h;	// 길이, 높이 
	
	scanf("%d %d", &n, &h);
	
	vector<int> b(n/2), t(n/2);	// 석순, 종유석 모음 
	
	for(int i = 0; i < n / 2; i++) {
		scanf("%d", &b[i]);
		scanf("%d", &t[i]);
	}
	
	// 오름차순으로 정렬 
	sort(b.begin(), b.end());
	sort(t.begin(), t.end());
	
	int ans = INF, cnt = 1;	// 최솟값, 존재하는 개수 
	
	// 모든 높이에 따라 점검
	// 해당 높이에 있는 석순과 종유석의 개수 세기 
	for(int i = 1; i <= h; i++) {
		// 해당 높이에 있는 석순의 개수 = 전체 개수 - 그보다 작은 개수 
		int tmp = n/2 - (lower_bound(b.begin(), b.end(), i) - b.begin());	// lower_bound는 iter로 반환하므로
		// 해당 높이에 있는 종유석의 개수 = 전체 개수 - 그보다 높이 있는 개수 
		tmp += n/2 - (upper_bound(t.begin(), t.end(), h - i) - t.begin());	// upper_bound도 같은 이유 
		
		// 최소값 개수 세기 
		if(ans == tmp) cnt++;
		// 최소값으로 갱신 
		else if (ans > tmp) {
			ans = tmp;
			cnt = 1;	// 첫번째 최소값 
		}
	}
	
	printf("%d %d", ans, cnt);
	 
	
	return 0;
}
