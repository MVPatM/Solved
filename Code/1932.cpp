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

	for (int i = 0; i < length; i++) { // i -> height variable, k -> �þ�� �غ��� ũ��
		for (int j = 0; j < i + 1; j++) { // k��ŭ�� input���� �ޱ� ���� for��
			int tmp;
			cin >> tmp;
			tri[i][j] = tmp;
		}
	}
}

// �ߺ��̳� �� ���ϴ� ��찡 �߻��� �Ǿ���.
void DoTriangle() {
	for (int i = 0; i < length; i++)
		dp[i] = tri[length - 1][i];

	for (int i = length - 2; i >= 0; i--) { // i -> ���̺�ȭ�ǹ� k -> ���̿� ���� �غ��� ���� ��ȭ �ǹ�
		dp[0] += tri[i][0];
		for (int j = 1; j < i + 1; j++) { // ����dp to ���ο�dp�� ����
			dp[j - 1] = max(dp[j - 1], dp[j] + tri[i][j - 1]);
			dp[j] += tri[i][j];
		}
		
		dp[i] = max(dp[i], dp[i + 1] + tri[i][i]);
	}
}