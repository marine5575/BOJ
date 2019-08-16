/*
seg tree를 이용한 일반적인 이분탐색 ver. TOP DOWN
*/
#include <iostream>
#define MAX 1000000

using namespace std;

int tree[2 * MAX + 1];	// seg tree
int n;	// 변경 횟수 

void update(int i, int num) {
	i += MAX - 1;	// 시작 세팅 
	tree[i] += num;
	i >>= 1;	// 그의 조상 
	
	while(i) {
		tree[i] = tree[i << 1] + tree[i << 1 | 1];
		i >>= 1;
	}
}

int query(int i, int j) {
	i += MAX - 1;	// 시작 
	j += MAX - 1;	// 끝 
	
	int sum = 0;	// 합 
	
	// 시작은 끝보다 작거나 같다 
	while(i <= j) {
		if(i & 1) sum += tree[i++];
		if(!(j & 1)) sum += tree[j--];
		i >>= 1; j >>= 1;
	}
	
	return sum;
}

int find(int num, int s, int e) {
	if(s == e) return s;	// 발견하면 위치 return 
	
	int mid = (s + e) / 2;	// 중간 값 
	int tmp = query(s, mid);
	
	// 찾는 값이 앞의 반보다 크다? 
	if(num > tmp) {
		// 뒤를 찾는다 
		return find(num - tmp, mid + 1, e);
	}
	// 앞을 찾는다 
	else return find(num, s, mid);
}


int main(void) {
	cin.tie(0);
	ios::sync_with_stdio(0);
	
	cin >> n;
	
	while(n--) {
		int select, a, b;	// (빼기 or 넣기), (꺼낼 사탕 순위 or 넣을 사탕 맛), 넣을 개수 
		cin >> select >> a;
		
		// 넣을 때 
		if(select == 2) {
			cin >> b;
			update(a, b);	// 이만큼 추가할 것 
			continue;
		}
		
		int idx = find(a, 1, MAX);	// 찾는 순위는 이 맛임 
		cout << idx << "\n";
		update(idx, -1);	// 꺼냈음을 표시 
	}
	
	return 0;
}
