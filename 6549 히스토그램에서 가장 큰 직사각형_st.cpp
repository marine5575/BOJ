/*
stack을 활용하여 품
O(n)만에 해결 가능하다! 
*/
#include <iostream>
#include <stack>

using namespace std;
typedef long long ll;

int n, tmp;	// input 수,  임시 
int arr[100001];	// input
stack<int> s;	// 현재 보고 있는 것보다 높이가 크거나 같은 것들 집합 


int main(void) {
	cin.tie(0);
	ios::sync_with_stdio(0);
	
	while(1) {
		cin >> n;
		if(n == 0) break;
		
		for(int i = 0; i < n; i++) {
			cin >> arr[i];
		}
		
		s.push(-1);	// 조기 종료 방지 
		s.push(0);	// 초기화 
		ll area = 0;	// 넓이 
		
		// 모든 원소에 대해 
		for(int i = 1; i < n; i++) {
			// stack이 비었는가? && 현재 것이 더 낮은가? 
			while(s.top() != -1 && arr[s.top()] > arr[i]) {
				tmp = s.top(); s.pop();	// 현재보다 높은 높이를 가지는 index 
				ll tmpA = (ll)arr[tmp] * (i - s.top() - 1);	// tmp보다 높은 높이를 가지는 index 담까지는 내가 최소
				// 최댓값 갱신 
				if(area < tmpA) area = tmpA;
			}
			s.push(i);	// 넣기 
		}
		
		// stack이 빌 때까지 
		while(s.top() != -1) {
			tmp = s.top(); s.pop();
			ll tmpA = (ll)arr[tmp] * (n - 1 - s.top());	// 현재 높이 * 나보다 높은 것 담까지 너비
			// 최댓값 갱신 
			if(area < tmpA) area = tmpA;
		}
		
		cout << area << "\n";
	}
	
	return 0;
}
