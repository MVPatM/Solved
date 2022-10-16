/*
2차원 dp를 사용을 해서 만들 수 있다. 1차원 dp로만 해결을 하려고 해서 문제 해결이 안 되었다.
각각의 문자열을 한꺼번에 한 문자씩 추가하려고 해서 문제 해결에 어려웠다.
한번의 turn마다 2개의 문자열중에서 하나의 문자만 추가시키면서 진행을 하면 된다.
*/
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);

string str1, str2; // str1: 기준(행), str2: 비교(열)
int dp[1001][1001]; // dp의 size를 [2][1001]로 설정을 하여도 충분하다. 왜냐하면 값을 update시키는 데 2개면 충분하기 때문이다. 아니다 1개여도 충분하다.

inline void InputInfo() { cin >> str1 >> str2; }
void Solve();

int main(void) {
	fastio;
	InputInfo();
	Solve();

	return 0;
}

void Solve() {
	int i, j;
	// str에 접근을 하려면 -1을 해주어야 하고
	// dp에 접근을 하려면 그대로 접근을 하면 된다.
	for (int i = 1; i <= str2.length(); i++) {
		for (int j = 1; j <= str1.length(); j++) {
			// dp[i][j]에 들어갈 값 찾기
			if (str2[i - 1] == str1[j - 1]) 
				dp[i][j] = dp[i - 1][j - 1] + 1;
			else 
				dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);

			// 출력값 찾기
		}
	}

	cout << ans;
}