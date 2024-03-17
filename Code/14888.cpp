/*
�������� redo ��ų �� ������ �߻��Ѵ�.
�������� �ϸ� ������ ����� �ϴµ� �� �������� �����ϸ� ���ϱ⸦ �ؼ� ������ ������ ������ ������ ���� �ʴ´�.
BackTracking Algorithm >> �ϳ��ϳ� ��� ���縦 �ؾ��Ѵ�, ���� ����Լ��� �̿��� �ϴ� ���� ����.
� �ڷ����� �ִ񰪰� �ּڰ��� ���ϱ� ���ؼ��� climits ���̺귯���� limits.h ��������� �̿��� �ϸ� �ȴ�.
*/
#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0); 
const int OperL = 4;
int mx = INT_MIN;
int mn = INT_MAX;
int length;
int operand[11];
int ans[11];
int oper[4]; // 0: +, 1: -, 2: *, 3: /


void InputInfo();
void FindValue();
void BT(int n, int o);
void DoOp(int n, int o);
void PrintAns();

int main(void) {
	fastio;
	InputInfo();
	FindValue();
	PrintAns();

	return 0;
}

void InputInfo() {
	cin >> length;

	for (int i = 0; i < length; i++) {
		int tmp;
		cin >> tmp;
		operand[i] = tmp;
	}

	for (int i = 0; i < OperL; i++) {
		int tmp;
		cin >> tmp;
		oper[i] = tmp;
	}
}

void FindValue() {
	ans[0] = operand[0];

	for (int i = 0; i < OperL; i++) {
		if (oper[i]) {
			oper[i]--;
			BT(1, i);
		}
	}
}

void BT(int n, int o) {
	DoOp(n, o);
	
	if (n + 1 == length) { // check if it's end point
		mx = max(mx, ans[n]);
		mn = min(mn, ans[n]);
	}
	else {
		for (int i = 0; i < OperL; i++) {
			if (oper[i]) {
				oper[i]--;
				BT(n + 1, i);
			}
		}
	}

	n--;
	oper[o]++;
}

void DoOp(int n, int o) {
	switch (o) {
	case 0:
		ans[n] = ans[n - 1] + operand[n];
		return;
	case 1:
		ans[n] = ans[n - 1] - operand[n];
		return;
	case 2:
		ans[n] = ans[n - 1] * operand[n];
		return;
	case 3:
		ans[n] = ans[n - 1] / operand[n];
		return;
	}
}

void PrintAns() {
	cout << mx << "\n";
	cout << mn << "\n";
}