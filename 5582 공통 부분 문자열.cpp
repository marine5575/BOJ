#include <cstdio>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int dp[4001][4001];	// dp[i][j] : a를 i번째까지 살펴보고, b를 j번째까지 살펴봤을 때 수열의 최대 길이


int main(void) {
	string s1, s2;	// 문자열 a, b
	cin >> s1 >> s2;

	// 모든 문자에 대해서 실행
	for (int i = 1; i <= s1.size(); i++) {
		for (int j = 1; j <= s2.size(); j++) {
			// 주위의 값들이 같은가? 현재 문자들이 같은가?
			if (dp[i - 1][j] == dp[i][j - 1] && s1[i - 1] == s2[j - 1]) {
				int flag = 0;	// 0: 이번 문자까지가 최장 수열, 1: 다른게 최장 수열

				// 내 바로 전 것들 살펴보기
				for (int k = 1; k <= dp[i - 1][j]; k++) {
					// 범위 내에 다른 값이 존재하는가?
					if (s1[i - k - 1] != s2[j - k - 1]) {
						flag = 1;
						break;
					}
				}

				// 이번 문자로 수열의 길이가 갱신되지 않을 때
				if (flag == 1) {
					dp[i][j] = dp[i - 1][j];
				}
				// 갱신될 때
				else dp[i][j] = dp[i - 1][j - 1] + 1;
			}
			else {
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
			}
		}
	}

	printf("%d\n", dp[s1.size()][s2.size()]);

	return 0;
}
