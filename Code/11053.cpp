#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);

int arr[1000];
int dp[1000];
int pointer[1000]; // index를 가리키는 array이다.
int len;

void InputInfo();
void Solve();

int main(void) {
	fastio;
	InputInfo();
	Solve();

	return 0;
}

void InputInfo() {
	cin >> len;

	for (int i = 0; i < len; i++)
		cin >> arr[i];
}

void Solve() {
	int maxvalue = 1, maxidx = 0, i;
	fill(dp, dp + len, 1);
	for (i = 0; i < len; i++)
		pointer[i] = i;

	for (i = 0; i < len; i++) {
		for (int j = 0; j < i; j++) {
			/* 이런 식으로 코딩을 하면 같은 값을 여러번 계산하게 된다.
			if (arr[j] < arr[i]) { 
				num++;
			}
			*/
			if (arr[j] < arr[i]) { // 위의 경우 때문에 dp를 이용해야 한다.
				//dp[i] = max(dp[i], dp[j] + 1);하나씩 검색을 하면서 자기 자신의 값이 큰지 아니면 index j의값을 포함을 시킬 것인지 파악

				if (dp[j] + 1 > dp[i]) {
					dp[i] = dp[j] + 1;
					pointer[i] = j;
				}
			}
		}
		
		if (dp[i] > maxvalue) {
			maxvalue = dp[i];
			maxidx = i;
		}
	}

	cout << maxvalue << "\n";

	// 백준 14002번 추가 내용
	vector<int> tmp;
	for (i = maxidx; i != pointer[i]; i = pointer[i])
		tmp.push_back(arr[i]);
	tmp.push_back(arr[i]);
	// reverse함수를 이용해서 index를 통해서 접근을 하는 것이 아니라 back함수를 이용해서 뒤에서 부터 접근을 할 수 있다.
	reverse(tmp.begin(), tmp.end());

	for (i = 0; i < tmp.size(); i++)
		cout << tmp[i] << " ";

	/*
	* version 2
	for (i = 0; i < tmp.size(); i++) {
		cout << tmp.back();
		tmp.pop_back();
	}
	*/
}