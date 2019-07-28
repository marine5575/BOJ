#include <cstdio>

int main(void) {
	int h, m; // 시간, 분
	scanf("%d %d", &h, &m);
	
  // 45분 보다 작은가?
	if(m < 45) {
    // 1 ~ 23시인가?
		if(h >= 1) printf("%d %d\n", h - 1, 60 - 45 + m);
    // 0시일 때
		else printf("23 %d\n", 60 - 45 + m);
	}
  // 45분 보다 클 때
	else printf("%d %d\n", h, m - 45);
	
	return 0;
}
