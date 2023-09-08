/*
   2�� n���� ���ϰų� 2�� n���� ���� ������ bit������ ('<<' or '>>')�� �̿��ؼ� ���� �� �ִ�.
   �׷��� n�� �ſ� Ŭ �� bit�����ڸ� �̿��ϸ� ���ϴ� ����� ���� �� ����.
   Hardware�� ��ɾ �� bit���� ������ �ϴ� ���� ���� �ٸ���.
*/

#include <iostream>
#include <cmath>

using namespace std;

void hanoi(int n, int from, int to);
void play_hanoi();

int main(void) {
	play_hanoi();
	return 0;
}

void hanoi(int n, int from, int to) {
	if (n == 0)
		return;

	int pos = 6 - from - to;
	hanoi(n - 1, from, pos);

	cout << from << " " << to << '\n';
	
	hanoi(n - 1, pos, to);
	
}

void play_hanoi() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;

	cout << (1 << n) - 1 << "\n";

	hanoi(n, 1, 3);
}