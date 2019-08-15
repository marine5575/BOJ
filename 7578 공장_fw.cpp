#include <iostream>

using namespace std;
typedef long long ll;

int tree[500001];
int arr[1000001];
int n;
ll cnt = 0;

ll query(int i) {
	ll sum = 0;
	
	while(i) {
		sum += tree[i];
		i -= (i & -i);
	}
	
	return sum;
}

void update(int i) {
	while(i <= n) {
		tree[i] += 1;
		i += (i & -i);
	}
}


int main(void) {
	cin.tie(0);
	ios::sync_with_stdio(0);
	
	cin >> n;
	
	for(int i = 1, x; i <= n; i++) {
		cin >> x;
		arr[x] = i;
	}
	
	for(int i = 1, x; i <= n; i++) {
		cin >> x;
		update(arr[x]);
		cnt += i - query(arr[x]);
	}
	
	cout << cnt << "\n";
	
	return 0;
}
