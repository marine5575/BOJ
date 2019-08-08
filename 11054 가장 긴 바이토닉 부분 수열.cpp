/*
바이토닉 부분 수열은 어떻게 보면 어떤 점 하나를 기점으로 양쪽으로 정렬된 수열이 있는 것
따라서 한쪽으로도 수열을 찾고, 반대쪽에서도 수열을 찾아
그 길이 합이 최대인 것을 찾으면 됨 
*/
#include <cstdio>

int arr[1001];	// 원래 수열 
int dpR[1001];	// dpR[i] = A : i번째 원소가 꽁무니일 때의 최장 수열의 길이 A (앞 first) 
int dpD[1001];	// dpD[i] = A : i번째 원소가 꽁무니일 때의 최장 수열의 길이 A (뒤 first) 


int main(void) {
	int n;	// 수열의 길이 
	scanf("%d", &n);
	
	for(int i = 0; i < n; i++) scanf("%d", arr + i);
	
	// 앞에서부터 꽁무니 가정 
	for(int i = 0; i < n; i++) {
		dpR[i] = 1;	// 초기화 : 일단 이게 첫번째라고 가정 
		
		// 나보다 앞에 있는 것들을 살펴봄 
		for(int j = 0; j < i; j++) {
			// 꽁무니보다 작은가?
			// 꽁무니 길이보다 지금 길이 다음이 더 긴가? 
			if(arr[j] < arr[i] && dpR[i] < dpR[j] + 1) {
				dpR[i] = dpR[j] + 1;
			}
		}
	}
	
	// 뒤에서부터 꽁무니 가정 
	for(int i = n - 1; i >= 0; i--) {
		dpD[i] = 1;	// 초기화 
		
		// 나보다 뒤에 있는 것들을 살펴봄 
		for(int j = n - 1; j > i ; j--) {
			// 꽁무니보다 작은가?
			// 꽁무니 길이보다 지금 길이 다음이 더 긴가? 
			if(arr[j] < arr[i] && dpD[i] < dpD[j] + 1) {
				dpD[i] = dpD[j] + 1;
			}
		}
	}
	 
	int ans = -1;	// 최댓값
	
	// 최댓값 저장 
	for(int i = 0; i < n; i++) {
		ans = ans < dpD[i] + dpR[i] - 1 ? dpD[i] + dpR[i] - 1 : ans;
	}
	
	printf("%d\n", ans);
	
	return 0;
} 
