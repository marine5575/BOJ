/***************************/
// 항상 변수의 범위를 check! 
/***************************/
#include <iostream>
#define MAX 1000001

using namespace std;

int arr[MAX];	// 응시자 수 


int main(void) {
	cin.tie(0);
	ios::sync_with_stdio(0);
	
	int n, master, assist;	// 시험장 수, 총 감독이 커버 가능한 수, 부감독이 커버 가능한 수 
	long long ans = 0;	// 필요한 감독 수
	
	cin >> n;
	
	for(int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	
	cin >> master >> assist;
	
	for(int i = 0; i < n; i++) {
		// 총감독은 무조건 한 명은 배치되어있어야 됨 
		if(arr[i] < master) arr[i] = 0;
		else arr[i] -= master;
		
		// 부감독 배치 
		ans += (arr[i] / assist);
		// 완전히 딱 떨어질 땐 통과 
		if(!(arr[i] % assist)) continue;
		ans++;
	}
	
	ans += n;	// 총 감독 수도 더함 
	
	cout << ans << "\n";
	
	return 0;
} 
