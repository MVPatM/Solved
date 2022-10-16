/*
2���� dp�� ����� �ؼ� ���� �� �ִ�. 1���� dp�θ� �ذ��� �Ϸ��� �ؼ� ���� �ذ��� �� �Ǿ���.
������ ���ڿ��� �Ѳ����� �� ���ھ� �߰��Ϸ��� �ؼ� ���� �ذῡ �������.
�ѹ��� turn���� 2���� ���ڿ��߿��� �ϳ��� ���ڸ� �߰���Ű�鼭 ������ �ϸ� �ȴ�.
*/
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);

string str1, str2; // str1: ����(��), str2: ��(��)
int dp[1001][1001]; // dp�� size�� [2][1001]�� ������ �Ͽ��� ����ϴ�. �ֳ��ϸ� ���� update��Ű�� �� 2���� ����ϱ� �����̴�. �ƴϴ� 1������ ����ϴ�.

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
	// str�� ������ �Ϸ��� -1�� ���־�� �ϰ�
	// dp�� ������ �Ϸ��� �״�� ������ �ϸ� �ȴ�.
	for (int i = 1; i <= str2.length(); i++) {
		for (int j = 1; j <= str1.length(); j++) {
			// dp[i][j]�� �� �� ã��
			if (str2[i - 1] == str1[j - 1]) 
				dp[i][j] = dp[i - 1][j - 1] + 1;
			else 
				dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);

			// ��°� ã��
		}
	}

	cout << ans;
}