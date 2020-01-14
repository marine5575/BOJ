#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string arr[20001];	// 문자열 배열 

// 비교 연산자 재정의 
bool comp(const string &s1, const string &s2) {
	if(s1.size() < s2.size()) return true;
	else if(s1.size() == s2.size() && s1 < s2) return true;
	else return false;
}

int main(void) {
	cin.tie(0);
	ios::sync_with_stdio(0);
	
	int n;
	cin >> n;
	
	for(int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	
	sort(arr, arr + n, comp);	// 재정의한 연산자로 정렬 
	
	// 첫번째껀 무조건 출력이지 
	cout << arr[0] << "\n";
	
	for(int i = 1; i < n; i++) {
		// 중복되는 단어는 통과 
		if(arr[i] == arr[i - 1]) continue;
		
		cout << arr[i] << "\n";
	}
	
	return 0;
}
