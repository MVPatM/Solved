/*
1. 2������ �̿� �ϴ� ��� -> �ξ� ������....
2�������� ǥ���� �Ͽ��� �� 1�� ǥ���� �Ǿ����� 
�� �ڸ����� ���� ���� ǥ���ϴ� ��Ŀ� ���� �ϴ� ����̴�.

2. Ȧ���̸� -1, ¦���̸� x2�� �ϴ� ��� -> 1�� ��ĺ��� ������.
*/
#include <iostream>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);
#define divisor 1000000007
using LL = long long;

LL num; // 9õ�� ���� ������ cover�� �� �ִ�.
LL ans[2][2] = { {1, 0}, {0, 1} };

inline void InputInfo() { cin >> num; }
void MulMatrix(LL n);
void MulMatrixVer2();
void Solve();

int main(void) {
	fastio;
	InputInfo();
	Solve();

	return 0;
}

void MulMatrix(LL n) {
	if (!n)
		return;

	int i, j;
	LL tmp[2][2] = { {0,0}, {0,0} };

	if (n % 2) {
		MulMatrix(n - 1);
		tmp[0][0] = ans[0][0] + ans[0][1];
		tmp[0][1] = ans[0][0];
		tmp[1][0] = ans[1][0] + ans[1][1];
		tmp[1][1] = ans[1][0];

		for (i = 0; i < 2; i++) {
			for (j = 0; j < 2; j++)
				ans[i][j] = tmp[i][j] % divisor;
		}
	}
	else {
		MulMatrix(n / 2);
		for (i = 0; i < 2; i++) {
			for (j = 0; j < 2; j++) {
				for (int k = 0; k < 2; k++) 
					tmp[i][j] += (ans[i][k] * ans[k][j]);
			}
		}

		for (i = 0; i < 2; i++) {
			for (j = 0; j < 2; j++)
				ans[i][j] = tmp[i][j] % divisor;
		}
	}
}

void MulMatrixVer2() {
	int i, j;
	LL tmp[2][2] = { {1,1}, {1,0} };

	while (num > 0) {
		if (num % 2) {

		}

		num /= 2;
		for (i = 0; i < 2; i++) {
			for (j = 0; j < 2; j++) {
				for (int k = 0; k < 2; k++)
					tmp[i][j] += (ans[i][k] * ans[k][j]);
			}
		}

		for (i = 0; i < 2; i++) {
			for (j = 0; j < 2; j++)
				ans[i][j] = tmp[i][j] % divisor;
		}
	}


}

void Solve() {
	MulMatrix(num);
	cout << ans[0][1];
}