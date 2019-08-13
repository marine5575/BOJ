/*
fenwick보다 segment tree 방법이 더 빠르다.
참고로 속도를 내고 싶다면 stdio 보다는 iostream을 추천 
*/
#include <iostream>
#define MAX 2050000

using namespace std;

typedef long long ll;

int start, n, ch, get;	// 원래값의 시작 지점, 전체 input 길이, 변경 횟수, 합을 구하는 횟수 
ll tree[MAX + 1];	// seg tree

void update(int i, ll num) {
	// 'i번째'이므로 -1을 해줌
	ll tmp = start + i - 1;	// 들어있는 곳 
	tree[tmp] = num;
	
	// 더이상 조상님이 없을 때까지 
	while(tmp > 1) {
		tmp >>= 1;	// 조상 찾기
		// 조상 갱신 
		tree[tmp] = tree[tmp << 1] + tree[(tmp << 1) + 1];
	}
}

ll query(int i, int j) {
	i += start - 1;	// 시작 지점 
	j += start - 1;	// 끝나는 지점 
	
	ll sum = 0;	// 합 
	
	// 시작은 끝보다 작음 
	while(i <= j) {
		// '시작'이 오른쪽에 위치하는가? 
		if(i % 2 == 1) {
			sum += tree[i];
			i++;
		}
		// '끝'이 왼쪽에 위치하는가? 
		if(j % 2 == 0) {
			sum += tree[j];
			j--;
		}
		// 위로 올라감 
		i >>= 1; j >>= 1;
	}
	
	return sum;
}

void makeTree() {
	ll tmp = start + n - 1;	// 맨 끝 idx 
	tmp >>= 1;	// 그의 조상 
	
	// 끝까지 갱신 
	while(tmp > 0) {
		tree[tmp] = tree[tmp << 1] + tree[(tmp << 1) + 1];
		tmp--;
	}
}


int main(void) {
	cin.tie(0);
	ios::sync_with_stdio(0);
	
//	scanf("%d %d %d", &n, &ch, &get);
	cin >> n >> ch >> get;
	
	ch += get; 
	
	// 시작 지점 찾기 
	for(start = 1; start < n; start <<= 1);
	
	for(int i = 0; i < n; i++) {
		ll x;
//		scanf("%lld", &x);
		cin >> x;
		tree[start + i] = x;	// 말단 채우기 
	}
	
	makeTree();	// 트리 만듬 
	
	int select, i;	// 명령어, (바꿀 번호 or 시작 번호)
	ll j;	// (바꿀 값 or 종료 번호) 
	
	while(ch--) {
//		scanf("%d %d %lld", &select, &i, &j);
		cin >> select >> i >> j;
		
		// 업데이트인가? 
		if(select == 1) update(i, j);
//		else printf("%lld\n", query(i, j));
		// 합을 구해야 하는가? 
		else cout << query(i, j) << "\n";
	}
	
	return 0;
}
