#include <iostream>
#include <cstdio>

using namespace std;

int gcd(int a, int b) {
	// 나머지가 0이 아닐 동안 돌림
	while (b > 0) {
		int tmp = a;	// a 임시 저장
		a = b;	// a 자리에 b를 앉힘
		b = tmp % b;	// 새로운 b는 나머지로 만듬
	}

	return a;	// 최대 공약수
}

int lcm(int a, int b) {
	return a * b / gcd(a, b);	// 최소 공배수
}


int main(void) {
	int nu1, nu2, dem1, dem2, nu, dem;	// 각각 더할 분자1, 분자2, 분모1, 분모2, 구할 분자, 분모

	scanf("%d %d", &nu1, &dem1);
	scanf("%d %d", &nu2, &dem2);

	int LCM = lcm(dem1, dem2);	// 최소 공배수
	int mul1 = LCM / dem1;	// 분수1 분자에 곱할 값
	int mul2 = LCM / dem2;	// 분수2 분자에 곱할 값

	nu1 *= mul1;
	nu2 *= mul2;

	nu = nu1 + nu2;	// 분자 더함
	dem = LCM;	// 분모는 아까 최소 공배수

	int div = gcd(nu, dem);	// 기약 분수 만들기 위한 최대 공약수

	nu /= div;
	dem /= div;

	printf("%d %d\n", nu, dem);

	return 0;
}
