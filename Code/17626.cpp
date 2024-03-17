/*
sol1 -> dp�� �̿��ؼ� Ǯ �� �ִ�.

sol2 -> brute force algorithm�� �̿��ؼ� Ǯ �� �ִ�.
�־��� ���� square�� ������ ����� ����� �ϳ��ϳ� ã�� ����̴�.
���� 1��� ������ �ϸ� �� ���� for���� ������ ���� 1�� �Ǵ� ���� Ȯ���Ѵ�.
�׸��� �ű⼭ ���� ã�� ���ϸ� ���� 2��� ������ �ؼ� ���� ��������� ���� Ȯ���ؾ� �Ѵ�.
���� 2��� ������ �ϸ� �� ���� for������ ������ ���� 2�� �Ǵ� ���� Ȯ���ϸ� �ȴ�.
�� ���� 3�� ���������̴�.
�������� ������ 4���� ������ ���� ���� ��� ���� ǥ���� �����ϴ� �����Ƿ� 
3�� �ƴϸ� ���� �ᱹ 4�� �Ǵ� ���̴�.
*/
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

#define fastio ios_base::sync_with_stdio(0), cin.tie(0);

int value;
int NeededNaturalNumber[50001];

inline void InputInfo() { cin >> value; }
int GetMinNum();

int main(void) {
	fastio;
	InputInfo();
	cout << GetMinNum();

	return 0;
}

int GetMinNum() {
	int limit = (int)sqrt(value);
	fill(NeededNaturalNumber, NeededNaturalNumber + 50001, 5); // exist in <algorithm> header file
	NeededNaturalNumber[0] = 0;

	for (int i = 0; i <= value; i++) { // ���� ���� ������
		for (int j = 1; j <= limit; j++) { // ������ ��ų ����
			int square = j * j;

			if (i + square > value)
				break;

			NeededNaturalNumber[i + square] = min(NeededNaturalNumber[i] + 1, NeededNaturalNumber[i + square]);
		}
	}
	
	return NeededNaturalNumber[value];
}