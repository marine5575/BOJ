#include <cstdio>
#define swap(x, y, t) ((t) = (x), (x) = (y), (y) = (t)) // swap 함수 구현

int main(void) {
	int a[3], t;  // 세가지 수, 임시 저장
	scanf("%d %d %d", &a[0], &a[1], &a[2]);
	
  // 2번째 수가 3번째 수보다 클 때
	if(a[1] > a[2]) swap(a[1], a[2], t);
  // 1번째 수가 2번째 수보다 클 때
	if(a[0] > a[1]) swap(a[0], a[1], t);
  // 2번째 수가 3번째 수보다 클 때
	if(a[1] > a[2]) swap(a[1], a[2], t);
	
	printf("%d\n", a[1]);
	
	return 0;
}
