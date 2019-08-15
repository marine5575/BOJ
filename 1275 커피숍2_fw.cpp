/*
fenwick tree로 풀었다.
역시 구간합은 fw이 최고야. 짜릿해 
*/
#include <iostream>

using namespace std;
typedef long long ll;

ll tree[100001];	// fw tree
ll arr[100001];	// 원래 값 저장 
int n, m;	// 수의 개수, 주문 횟수 

void update(int i, ll diff) {
	while(i <= n) {
		tree[i] += diff;
		i += (i & -i);
	}
}

ll query(int i) {
	ll sum = 0;
	
	while(i) {
		sum += tree[i];
		i -= (i & -i);
	}
	
	return sum;
}


int main(void) {
	cin.tie(0);
	ios::sync_with_stdio(0);
	
	cin >> n >> m;
	
	for(int i = 1; i <= n; i++) {
		cin >> arr[i];
		update(i, arr[i]);
	}
	
	int x, y, a;	// x ~ y까지, a번째 수를 
	ll b;	// b로 고쳐주세요 
	
	while(m--) {
		cin >> x >> y >> a >> b;
		
		// x < y인 경우, x > y인 경우, x == y인 경우 
		if(x < y) cout << query(y) - query(x - 1) << "\n";
		else if (x > y) cout << query(x) - query(y - 1) << "\n";
		else cout << arr[x] << "\n";
		
		update(a, b - arr[a]);
		arr[a] = b;
	}
	
	return 0;
}
