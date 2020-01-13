#include <iostream>

using namespace std;

int input;	// input 
int arr[8001];	// arr[i] = i가 나온 횟수 


int main(void) {
	cin.tie(0);
	ios::sync_with_stdio(0);
	
	int n;	// input 개수 
	cin >> n;
	
	double sum = 0;	// input의 총 합 
	int maxi = -4001, mini = 4001;	// 최대값, 최소값 
	
	for(int i = 0; i < n; i++) {
		cin >> input;
		sum += input;
		arr[input + 4000]++;	// 횟수 증가 
		
		// 최대, 최소 갱신 
		if(maxi < input) maxi = input;
		if(mini > input) mini = input;
	}
	
	double avg = sum / n;	// 산술 평균 
	
	/* 반올림하는 부분 */
	// 양수일 때 -> 0.5 더해보고 소수점 버림 (0.5 이상이었으면 이미 1이 올라갔을 것) 
	if(avg >= 0) cout << (int)(avg + 0.5) << "\n";
	// 음수일 때 -> 0.5 빼보고 이하 동문 
	else cout << (int)(avg - 0.5) << "\n";
	
	int tmp = 0;	// 숫자의 등장 횟수 누적 합 
	for(int i = 0; i <= 8000; i++) {
		tmp += arr[i];
		
		// 중앙값을 포함하는가? 
		if(tmp > n / 2) {
			cout << i - 4000 << "\n";
			break;
		}
	}
	
	int idx = -1, cur = 0, flag = 0;	// 최빈값, 최빈값의 등장 횟수, 몇 번째 발견? 
	
	for(int i = 0; i <= 8000; i++) {
		// 최빈값 갱신 
		if(cur < arr[i]) {
			cur = arr[i];
			idx = i;
			flag = 0;
		}
		// 등장 횟수는 같은데 2번째 발견한 수일 때 
		else if(cur == arr[i] && flag == 0) {
			idx = i;
			flag = 1;
		}
	}
	
	cout << idx - 4000 << "\n";
	cout << maxi - mini << "\n";
	
	return 0;
}
