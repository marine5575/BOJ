/*
내 사랑 펜윅트리로 풀어보았다.
생각보다 느렸단 점이 신기했다. 
*/
#include <cstdio>
#define MAX 1000000

using namespace std;

typedef long long ll;

ll tree[MAX + 1], arr[MAX + 1];	// 펜윅 트리, 원래 값 
int n;	// 값 개수 

void update(int i, ll num) {
	// 끝까지 갱신 
	while(i <= n) {
		tree[i] += num;	// 차이를 더함 
		i += (i & -i);	// 위로 올라감 
	}
}

ll query(int i) {
	ll sum = 0;	// 합 
	
	while(i > 0) {
		sum += tree[i];	// 합을 더함 
		i -= (i & -i);
	}
	
	return sum;
}


int main(void) {
	int ch, get;	// 변경 횟수, 합 구하는 횟수 
	scanf("%d %d %d", &n, &ch, &get);
	
	for(int i = 1; i <= n; i++) {
		scanf("%lld", &arr[i]);
		update(i, arr[i]);	// 트리 만들기 
	}
	
	ch += get;	// 전체 횟수 
	
	while(ch--) {
		int select;	// 명령 
		scanf("%d", &select);
		
		// 갱신인가? 
		if(select == 1) {
			int i;	// 바꿀 번호 
			ll num;	// 바꿀 값 
			scanf("%d %lld", &i, &num);
			update(i, num - arr[i]);	// 차이를 갱신 
			arr[i] = num;	// 값 갱신 
		}
		// 구간 합을 구해야 하는가? 
		else {
			int i, j;	// 시작, 끝 
			scanf("%d %d", &i, &j);
			printf("%lld\n", query(j) - query(i - 1));
		}
	}
	
	return 0;
} 
