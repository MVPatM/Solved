#include<iostream>
#include <cstring>
#include <algorithm>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);

int dp[100000][2];
int dp2[3][2];
int sticker[100000][2];

void Init();
void Solve();

int main(void) {
	fastio;
	Solve();

	return 0;
}

void Init() {
	// 항상 원하는 값으로 바뀜
	dp[0][0] = sticker[0][0];
	dp[0][1] = sticker[0][1];

	// sticker_len이 1인 경우 원하는 대로 진행이 안된다
	dp[1][0] = dp[0][1] + sticker[1][0];
	dp[1][1] = dp[0][0] + sticker[1][1];
}

void Solve() {
	int testcase;
	cin >> testcase;

	for (int i = 0; i < testcase; i++) {
		int sticker_len, j;
		cin >> sticker_len;
		
		// input sticker
		for (j = 0; j < sticker_len; j++)
			cin >> sticker[j][0];
		for (j = 0; j < sticker_len; j++)
			cin >> sticker[j][1];

		Init();
		// using dp to solve the problem
		/*
		for (j = 2; j < sticker_len; j++) {
			dp[j][0] = max(dp[j - 1][1] + sticker[j][0], dp[j - 2][1] + sticker[j][0]);
			dp[j][1] = max(dp[j - 2][0] + sticker[j][1], dp[j - 1][0] + sticker[j][1]);
		}
		*/

		// 작은 크기의 배열을 이용해서 문제를 해결하는 방법
		for (j = 2; j < sticker_len; j++) {
			dp2[j % 3][0] = max(dp2[(j - 1) % 3][1] + sticker[j][0], dp2[(j - 2) % 3][1] + sticker[j][0]);
			dp2[j % 3][1] = max(dp2[(j - 2) % 3][0] + sticker[j][1], dp2[(j - 1) % 3][0] + sticker[j][1]);
		}
		
		cout << max(dp[(j - 1) % 3][0], dp[(j - 1) % 3][1]) << "\n";
	}
}