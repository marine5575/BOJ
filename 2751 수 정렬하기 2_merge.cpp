/*
merge sort로 풀었다.
최선 O(nlogn), 최악 O(nlogn)으로 안정 정렬이다 
*/
#include <iostream>

using namespace std;

int sorted[1000001];	// 임시 저장소 
int list[1000001];	// 원래 배열 -> 정렬된 배열 

/*
실제로 정렬이 수행되는 병합 과정 
*/
void merge(int left, int mid, int right) {
	int i, j, k, l;	// 왼쪽 배열 시작, 오른쪽 배열 시작, 임시 저장 시작, 그냥 temp 
	i = left; j = mid + 1; k = left;
	
	// 왼쪽 배열이나 오른쪽 배열이 끝에 다다르지 않음 
	while(i <= mid && j <= right) {
		// 왼쪽이 더 작을 때 
		if(list[i] <= list[j]) sorted[k++] = list[i++];
		// 오른쪽이 더 작을 때 
		else sorted[k++] = list[j++];
	}
	
	// 왼쪽 배열이 끝났을 때 
	if(i > mid) {
		// 나머지 오른쪽 배열을 옮김 
		for(l = j; l <= right; l++) sorted[k++] = list[l];
	}
	// 오른쪽 배열이 끝났을 때 
	else {
		// 나머지 왼쪽 배열을 옮김 
		for(l = i; l <= mid; l++) sorted[k++] = list[l];
	}
	
	// 정렬된 배열을 다시 저장 
	for(l = left; l <= right; l++) list[l] = sorted[l];
}

/*
DIVIDE 부분 
*/
void merge_sort(int left, int right) {
	// 왼쪽 < 오른쪽 
	if(left < right) {
		int mid = (left + right) / 2;	// 중간 지점 
		
		// 왼쪽 배열 
		merge_sort(left, mid);
		// 오른쪽 배열 
		merge_sort(mid + 1, right);
		// 합침 
		merge(left, mid, right);
	}
}


int main(void) {
	cin.tie(0);
	ios::sync_with_stdio(0);
	
	int n;	// 배열에 들어가는 숫자 수 
	cin >> n;
	
	for(int i = 0; i < n; i++) {
		cin >> list[i];
	}
	
	merge_sort(0, n - 1);
	
	for(int i = 0; i < n; i++) {
		cout << list[i] << "\n";
	}
	
	return 0;
}
