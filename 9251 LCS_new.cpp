/*
dp 배열을 1차원으로 두고도 풀 수 있다. 
*/
#include <iostream>
#include <string>

using namespace std;

int dp[1001];	// dp[i] = A : s2의 i번째가 꽁무니일 때 LCS의 최대 길이 


int main(void) {
	cin.tie(0);
	ios::sync_with_stdio(0);
	
	int cur;	// 현재까지의 수열 길이 
	string s1, s2;
	cin >> s1 >> s2;
	
	// s1의 모든 원소에 대해 
	for(int i = 0; i < s1.size(); i++) {
		cur = 0;	// 초기화 
		
		// s2의 모든 원소에 대해 
		for(int j = 0; j < s2.size(); j++) {
			// 수열 길이 갱신 
			if(dp[j] > cur) {
				cur = dp[j];
				continue;
			}
			
			// s1, s2의 원소가 같을 때
			// 현재 수열 길이 + 1 
			if(s1[i] == s2[j]) dp[j] = cur + 1;
		}
	}
	
	cur = 0;	// 초기화 
	
	// 최댓값 찾기 
	for(int i = 0; i < s2.size(); i++) {
		if(cur < dp[i]) cur = dp[i];
	}
	
	cout << cur << "\n";
	
	return 0;
} 
