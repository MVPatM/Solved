#include <iostream>
#include <cstring>
#include <algorithm> // reverse�Լ��� algorithm ������Ͽ� �����Ѵ�.

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);

string dp[101][101];
int N, R;

inline void InputInfo() { cin >> N >> R; }
void Init();
string Comb(int n, int r);
string StringSum(string str1, string str2);

int main(void) {
	fastio;
	InputInfo();
	Init();
	cout << Comb(N, R);

	return 0;
}

// N�� R�� 5�̻��̿��� 4c1�� ���Ǿ��� �� �ֱ� ������ 1���� ��� push�� ���־�� �Ѵ�.
void Init() {
	for (int n = 1; n <= N; n++) {
		string tmp;
		int tmpN = n;
		
		while (tmpN) {
			tmp.push_back((tmpN % 10) + '0'); // ���ڸ� int�������� char������ ��ȯ��Ű�� code
			tmpN /= 10;
		}
	
		reverse(tmp.begin(), tmp.end());
		dp[n][1] = tmp;
		dp[n][n - 1] = tmp;
		dp[n][0] = "1";
		dp[n][n] = "1";
	}
}

// �Ľ�Į �ﰢ���� �̿��� ��� �Լ��� �̿��ؼ� ���� ���Ϸ��� �Ѵ�.
// �� �� �ߺ��Ǿ����� ���� dp�� �̿��Ͽ��� ����� �ߺ����� �ʵ��� �Ѵ�.
string Comb(int n, int r) {
	if (dp[n][r] != "")
		return dp[n][r];

	dp[n][r] = StringSum(Comb(n - 1, r - 1), Comb(n - 1, r));
	dp[n][n - r] = dp[n][r];
	return dp[n][r];
}

// long long �ڷ������� ������ ���̰� �Ѱ谡 ������ string�� �̿��ؼ� ����� �����Ͽ��� �Ѵ�.
string StringSum(string str1, string str2) {
	string ans = "";
	int sum = 0;

	// while�� �տ��� empty�� ���� ���� ���̰� 
	// if �������� empty�� ������ ���� ������ �ߺ��� �����̶�� ������ �ؼ� ������ code��� ������ �Ͽ���.
	// �ߺ��ǰ� �����ٰ� �Ͽ��� ����� ������ ����
	while (!str1.empty() || !str2.empty() || sum) {
		if (!str1.empty()) {
			sum += (str1.back() - '0');
			str1.pop_back();
		}

		if (!str2.empty()) {
			sum += (str2.back() - '0');
			str2.pop_back();
		}

		ans.push_back((sum % 10) + '0'); // ���ڸ� int�������� char������ ��ȯ�� ��Ű�� ���
		sum /= 10;
	}

	reverse(ans.begin(), ans.end());
	return ans;
}