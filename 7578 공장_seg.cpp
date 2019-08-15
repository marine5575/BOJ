/*
seg tree 방식으로 풀어보았음 
*/
#include <iostream>

using namespace std;
typedef long long ll;

int arr[1000001];	// arr[x] = i : x 값은 (i + 1) 번째에 위치 
ll tree[1050001];	// seg tree
int start, n;	// 시작 지점, 기계 수 
ll cnt = 0;	// 꼬인 횟수 

ll query(int i, int j) {
	i += start;	// 시작 
	j += start;	// 끝 
	
	ll ans = 0;	// 합 저장 
	
	// 시작은 끝보다 작거나 같음 
	while(i <= j) {
		// '시작'이 오른쪽에 있는가? 
		if(i % 2 == 1) {
			ans += tree[i++];	// 저장 후, 오른쪽으로 밀기 
		}
		// '끝'이 왼쪽에 있는가? 
		if(j % 2 == 0) {
			ans += tree[j--];	// 저장 후, 왼쪽으로 밀기 
		}
		i >>= 1; j >>= 1;	// 조상으로~ 
	}
	
	return ans;
}

void update(int i) {
	i += start;	// 원래 위치 
	tree[i] = 1;	// 갱신 
	i >>= 1;	// 조상 
	
	// 더이상 조상이 없을 때까지 
	while(i) {
		tree[i] += 1;	// 갱신 
		i >>= 1;	// 조상 
	}
}


int main(void) {
	cin.tie(0);
	ios::sync_with_stdio(0);
	
	cin >> n;
	
	// 시작 지점 찾기 
	for(start = 1; start < n; start <<= 1);
	for(int i = 0, x; i < n; i++) {
		cin >> x;
		arr[x] = i;
	}
	
	for(int i = 0, x; i < n; i++) {
		cin >> x;
		cnt += query(arr[x] + 1, n - 1);	// 나보다 높은 숫자를 가진 것들의 수 
		update(arr[x]);	// 나도 연결되었음을 알림 
	}
	
	cout << cnt << "\n";
	
	return 0;
}
