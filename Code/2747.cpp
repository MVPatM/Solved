/*
���� ����Լ��� �ݺ��� ���� ���ؼ� �迭�� ����� �ؼ� ��� ����� ������ �Ͽ��� ���Ƚ���� �ٿ��ش�.
*/
#include <iostream>

using namespace std;

#define fastio ios_base::sync_with_stdio(0), cin.tie(0);

int fibo[46];

void Fibonaci();
void InputInfo();
int DoFibo(int n);

int main(void) {
	fastio;
	InputInfo();
	Fibonaci();

	return 0;
}

void Fibonaci() {
	int n;
	cin >> n;

	cout << DoFibo(n);
}

void InputInfo() {
	fibo[0] = 0;
	fibo[1] = 1;
}

int DoFibo(int n) {
	if (n == 1) 
		return fibo[1];
	
	fibo[n] = DoFibo(n - 1) + fibo[n - 2];
	return fibo[n];
}