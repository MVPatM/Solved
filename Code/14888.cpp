/*
연산결과를 redo 시킬 때 문제가 발생한다.
나눗셈을 하면 몫으로 계산을 하는데 이 나눗셈을 복구하면 곱하기를 해서 완전한 예전의 값으로 복구가 되지 않는다.
BackTracking Algorithm >> 하나하나 모두 조사를 해야한다, 따라서 재귀함수를 이용을 하는 것이 좋다.
어떤 자료형의 최댓값과 최솟값을 구하기 위해서는 climits 라이브러리나 limits.h 헤더파일을 이용을 하면 된다.
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