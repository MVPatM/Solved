/*
�� �������� ���� ���ϱ� ���ؼ� ������ ȹ������ ����� �����ϴ� ���� �ƴ϶� 
�ϳ��ϳ� ���� ����� ������ �Ͽ��� ���� ���ϴ� ���̴�.
���ʴ�� �ϳ��ϳ��� �ּ��� ���� ������ �ϵ��� �����.
*/
#include <iostream>
#include <algorithm>

using namespace std;

#define fastio ios_base::sync_with_stdio(0), cin.tie(0);
const int Inf = 1500000;
const int sz = 1000001;

int times[sz];

void Init() { fill(times, times + sz, Inf); }
void MakeOne();
void makeone();

int main(void) {
	fastio;
	Init();
	makeone();

	return 0;
}

// Bottom Up
void MakeOne() {
	int n;
	cin >> n;
	times[1] = 0;

	for (int i = 1; i < n; i++) {
		if (2 * i <= n)
			times[2 * i] = min(times[2 * i], times[i] + 1);
		if (3 * i <= n)
			times[3 * i] = min(times[3 * i], times[i] + 1);
		times[i + 1] = min(times[i + 1], times[i] + 1);
	}

	cout << times[n];
}

// Top Down
void makeone() {
	int n;
	cin >> n;
	times[n] = 0;

	for (int i = n; i > 0; i--) {
		if (i % 3 == 0)
			times[i / 3] = min(times[i / 3], times[i] + 1);
		if (i % 2 == 0)
			times[i / 2] = min(times[i / 2], times[i] + 1);
		times[i - 1] = min(times[i - 1], times[i] + 1);
	}

	cout << times[1];
}