#include <iostream>
#include <vector>
#include <string>
#include <cstdio>

using namespace std;

int num[1000001];	// 체망
vector<int> prime;	// k 미만 소수 모음
string s;	// input 암호. 10^100까지 담을 수 있음
int k;	// input 숫자


int main(void) {
	cin >> s >> k;	// 이거로 받으면 자동으로 string은 char의 배열로 됨

	// 에라토스테네스의 체망
	for (int i = 2; i < k; i++) {
		if (num[i] == 0) {
			prime.push_back(i);

			for (int j = 2; i*j < k; j++) {
				if (num[i *j] == 1) continue;

				num[i*j] = 1;
			}
		}
	}

	// 소수 갯수만큼만 시도
	for (int j = 0; j < prime.size(); j++) {
		int tmp = 0;	// 중간 저장 공간

		// 101자리 암호는 소수로 나누는 연산이 사실상 어려움
		// 따라서 새로운 방법 시도
		// 1. 첫번째 자리수를 소수로 나머지 연산
		// 2. (1)*10 + (두번째 자리수를 소수로 나머지 연산한 값)
		// 3. (2)*10 + (세번째 자리수를 소수로 나머지 연산한 값)
		// 마지막에는 결국 전체 값에 대한 나머지 값만 남음
		for (int i = 0; i < s.size(); i++) {
			int at = s[i] - '0';	// 현재 자리 값
			tmp *= 10;	// 이전 것 * 10
			at %= prime[j];	// 현재 자리를 소수로 나머지 연산
			tmp += at;	// 더해줌

			// 나중에 너무 커질 수도 있으므로 커질 때마다 미리미리 나눠주기
			if (tmp >= prime[j]) tmp %= prime[j];
		}

		// 최종 나머지가 0인가?
		if (tmp == 0) {
			printf("BAD %d\n", prime[j]);
			return 0;
		}
	}

	printf("GOOD\n");

	return 0;
}
