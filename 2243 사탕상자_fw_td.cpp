/*
fenwick tree로 푼 일반적 이분탐색 
*/
#include <iostream>
#define MAX 1000000

using namespace std;

int tree[MAX + 1];	// fw tree
int n;	// 변경 횟수 

void update(int i, int diff) {
	while(i <= MAX) {
		tree[i] += diff;
		i += (i & -i);
	}
}

int query(int i) {
	int sum = 0;
	
	while(i) {
		sum += tree[i];
		i -= (i & -i);
	}
	
	return sum;
}

// fw라서 그냥 자주 부르는 것보단 하나씩 비교키로 함 
int find(int num, int s, int e) {
	// 찾았는가? 
	if(s == e) return s;
	
	int mid = (s + e) / 2;	// 중간 값 
	int tmp = query(mid);	// mid까지의 부분합 
	
	// 찾는 값보다 크거나 같은가? 
	if(num <= tmp) return find(num, s, mid);
	// 찾는 값보다 작은가? 
	else return find(num, mid + 1, e);
}


int main(void) {
	cin.tie(0);
	ios::sync_with_stdio(0);
	
	cin >> n;
	int max = 0;	// 최댓값 
	
	while(n--) {
		int select, a;	// (빼기 or 넣기), (사탕 순위 or 넣을 사탕 맛) 
		cin >> select >> a;
		
		// 빼기 
		if(select == 1) {
			int idx = find(a, 1, max);	// 해당 순위의 맛 
			cout << idx << "\n"; 
			update(idx, -1);	// 뺐다는 것 표시 
		}
		else {
			int b;	// 넣을 개수 
			cin >> b;
			update(a, b);	// 갱신
			// 지금 어느 맛까지 넣었는지 갱신 
			if(max < a) max = a;
		}
	}
	
	return 0;
}
