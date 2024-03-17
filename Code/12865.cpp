#include <iostream>
#include <algorithm>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);

int itemNum, weightLimit;
int weight[101]; // index 1부터 시작
int value[101]; // index 1부터 시작
int dp[101][100001];

void InputInfo();
void Solve();

int main(void) {
	fastio;
	InputInfo();
	Solve();

	return 0;
}

void InputInfo() {
	cin >> itemNum >> weightLimit;

	for (int i = 1; i <= itemNum; i++) 
		cin >> weight[i] >> value[i];
}

void Solve() {
	for (int i = 1; i <= itemNum; i++) {
		for (int j = 0; j <= weightLimit; j++) {
			if (j >= weight[i])  // can push
				dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weight[i]] + value[i]);
			else  // can't push
				dp[i][j] = dp[i - 1][j];
		}
	}

	cout << dp[itemNum][weightLimit];
}