/*
그냥 나머지 연산 걍 하자ㅎㅎ
곱셈에서 뺄 생각 하덜덜 말어 
*/
#include <iostream>
#define DIV 1000000007

using namespace std;
typedef long long ll;

ll tree[2050001];	// seg tree
int n, ch, get;	// 수의 개수, 변경 횟수, 곱셈 구하는 횟수 

void update(int i, ll num) {
	i += n - 1;	// i번째를 가져왔으므로 
	tree[i] = num;
	i >>= 1;
	
	// 바뀐 대로 다시 업데이트 
	while(i) {
		tree[i] = (tree[i << 1] * tree[i << 1 | 1]) % DIV;
		i >>= 1;
	}
}

ll query(int i, int j) {
	i += n - 1;
	j += n - 1;
	
	ll sum = 1;
	
	while(i <= j) {
		// '시작'이 오른쪽에 있는가? 
		if(i & 1) {
			sum = (sum * tree[i++]) % DIV;
		}
		// '끝'이 왼쪽에 있는가? 
		if(!(j & 1)) {
			sum = (sum * tree[j--]) % DIV;
		}
		i >>= 1; j >>= 1;
	}
	
	return sum;
}

void makeTree() {
	int i = n - 1;
	
	while(i > 0) {
		tree[i] = (tree[i << 1] * tree[i << 1 | 1]) % DIV;
		i--;
	}
}


int main(void) {
	cin.tie(0);
	ios::sync_with_stdio(0);
	
	cin >> n >> ch >> get;
	ch += get;
	
	tree[0] = 1;
	
	for(int i = 0; i < n; i++) {
		cin >> tree[i + n];
	}
	
	makeTree();
	
	while(ch--) {
		int select, x, y;
		cin >> select >> x >> y;
		
		if(select == 1) {
			update(x, (ll)y);
		}
		else {
			cout << query(x, y) << "\n";
		}
	}
	
	return 0;
}
