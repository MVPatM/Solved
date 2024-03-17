#include <iostream>
#include <utility>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);
using pii = pair<int, int>; // row, column

int matLen, testcase;
int mat[1025][1025];
int dp[1025][1025];

void InputInfo();
void Solve();

int main(void) {
	fastio;
	InputInfo();
	Solve();

	return 0;
}

void InputInfo() {
	cin >> matLen >> testcase;

	for (int i = 1; i <= matLen; i++) {
		for (int j = 1; j <= matLen; j++) 
			cin >> mat[i][j];
	}
}

void Solve() {
	for (int i = 1; i <= matLen; i++) {
		int sum = 0;
		for (int j = 1; j <= matLen; j++) {
			sum += mat[i][j];
			dp[i][j] = dp[i - 1][j] + sum;		}
	}

	for (int i = 0; i < testcase; i++) {
		pii start, end;
		cin >> start.first >> start.second >> end.first >> end.second;
		int ans = dp[end.first][end.second];
		ans -= (dp[end.first][start.second - 1] + dp[start.first - 1][end.second]);
		ans += dp[start.first - 1][start.second - 1];
		cout << ans << "\n";
	}
}