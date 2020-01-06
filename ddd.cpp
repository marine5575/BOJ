#include <iostream>
#include <algorithm>

using namespace std;

int arr[8003] = {0};

int main(void) {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n, tmp, sum = 0;
    int maxi = -4001, mini = 4001;
    int m_max = -1, flag = 0;

    cin >> n;

    for(int i = 0; i < n; i++) {
        cin >> tmp;
        sum += tmp;
        if(maxi < tmp) maxi = tmp;
        if(mini > tmp) mini = tmp;
        arr[tmp + 4000]++;
    }

    for(int i = 0; i <= 8000; i++) {
        if(m_max < arr[i]) {
            m_max = arr[i];
            flag = 0;
        }
        else if(m_max == arr[i] && flag == 0) {
            m_max = arr[i];
            flag = 1;
        }
    }

    for(int i = 1; i <= 8000; i++) {
        arr[i] += arr[i - 1];
    }

    cout << sum / n << "\n" << lower_bound(arr, arr + 8001, arr[8000] / 2) - arr + 1 << "\n" << m_max << "\n" << maxi - mini << "\n";

    return 0;
}
