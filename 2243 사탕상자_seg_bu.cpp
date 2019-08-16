/*
seg tree의 이분 탐색 ver. BOTTOM UP 
*/
#include <iostream>
#define MAX 1000000

using namespace std;

int tree[2 * MAX + 200000];	// seg tree
int n, start;	// 변경 횟수, 시작 지점 

void update(int i, int num) {
	i += start - 1;
	tree[i] += num;
	i >>= 1;
	
	while(i) {
		tree[i] = tree[i << 1] + tree[i << 1 | 1];
		i >>= 1;
	}
}

int query(int i, int j) {
	i += start - 1;
	j += start - 1;
	
	int sum = 0;
	
	while(i <= j) {
		if(i & 1) sum += tree[i++];
		if(!(j & 1)) sum += tree[j--];
		i >>= 1; j >>= 1;
	}
	
	return sum;
}

int find(int num) {
	int s = 1;	// 여기서부터 찾기 
	
	while(1) {
		tree[s]--;	// 찾아봤음을 표시 
		
		// 말단 노드인가? 
		if(s >= start) break;
		
		// 왼쪽이 찾는 값보다 작은가? 
		if(num > tree[s << 1]) {
			num -= tree[s << 1];	// 찾는 값 갱신 
			s = s << 1 | 1;	// 오른쪽으로 
		}
		else s = s << 1;	// 왼쪽으로 
	}
	
	return s - start + 1;	// 말단은 0 ~ max - 1까지로 표시되어 있으므로 
}


int main(void) {
	cin.tie(0);
	ios::sync_with_stdio(0);
	
	cin >> n;
	// 시작지점 찾기 
	for(start = 1; start < MAX; start <<= 1);
	
	while(n--) {
		int select, a, b;	// 선택, (순위 or 맛), 개수 
		cin >> select >> a;
		
		// 넣기 
		if(select == 2) {
			cin >> b;
			update(a, b);
			continue;
		}
		
		int idx = find(a);	// 찾는 순위의 맛 
		cout << idx << "\n";
	}
	
	return 0;
}
