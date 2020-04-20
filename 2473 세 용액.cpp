/***********************/
// BOJ 2473 세 용액
// 핵심: 최적화 
/***********************/

#include <stdio.h>
#include <algorithm>
#define MAX ((int)5e3)
#define INF ((long long)3e9 + 1)

using namespace std;

typedef long long ll;

int n;	// 전체 용액 개수 
ll charVal = INF;	// 특성값 
ll arr[MAX], ans[4];	// 용액 거치대, 정답 

ll Abs(ll a) {
	return a < 0 ? -a : a;
}

void Input_Data(void) {
	scanf("%d", &n);
	
	for(int i = 0; i < n; i++) {
		scanf("%lld", &arr[i]);
	}
}

void find(void) {
	// 하나의 용액을 기준으로
	// 세 개의 용액의 특성값이 0에 가장 가까운 용액을 찾는 함수 
	
	// 기준 용액들 
	for(int i = 0; i < n; i++) {
		// 기준 용액이 가운데 혹은 끝인 것은 앞에서 이미 찾아봤을 것 
		int s = i + 1, e = n - 1;	// 뒤의 블록에서 찾는 시작, 끝 index 
		
		// 불변식 
		while(s < e) {
			ll sum = arr[i] + arr[s] + arr[e];	// 이번 특성값 
			
			// 최소값 갱신 
			if(charVal > Abs(sum)) {
				charVal = Abs(sum);
				ans[0] = arr[i];
				ans[1] = arr[s];
				ans[2] = arr[e];
			}
			
			// 음수 => 더 커져야 
			if(sum < 0) s++;
			// 양수 => 더 작아져야 
			else if(sum > 0) e--;
			// 더는 볼 필요 없음. 찾았음 
			else return;
		}
	}
}


int main(void) {
	Input_Data();
	sort(arr, arr + n);
	
	find();
	printf("%lld %lld %lld\n", ans[0], ans[1], ans[2]);
	
	return 0;
} 
