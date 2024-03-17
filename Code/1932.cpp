#include <iostream>
#include <algorithm>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);

int length;
int tri[500][500];
int dp[500];

void InputInfo();
void DoTriangle();

int main(void) {
	fastio;
	InputInfo();
	DoTriangle();
	cout << dp[0];

	return 0;
}

void InputInfo() {
	cin >> length;

	for (int i = 0; i < length; i++) { // i -> height variable, k -> 늘어나는 밑변의 크기
		for (int j = 0; j < i + 1; j++) { // k만큼의 input값을 받기 위한 for문
			int tmp;
			cin >> tmp;
			tri[i][j] = tmp;
		}
	}
}

// 중복이나 더 더하는 경우가 발생이 되었다.
void DoTriangle() {
	for (int i = 0; i < length; i++)
		dp[i] = tri[length - 1][i];

	for (int i = length - 2; i >= 0; i--) { // i -> 높이변화의미 k -> 높이에 따른 밑변의 길이 변화 의미
		dp[0] += tri[i][0];
		for (int j = 1; j < i + 1; j++) { // 이전dp to 새로운dp로 갱신
			dp[j - 1] = max(dp[j - 1], dp[j] + tri[i][j - 1]);
			dp[j] += tri[i][j];
		}
		
		dp[i] = max(dp[i], dp[i + 1] + tri[i][i]);
	}
}