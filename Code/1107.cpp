/*
getdigit�Լ����� 0�� �Է��� �ϸ��� digit�� 0���� return�Ǳ� ������ error�� �߻��Ѵ�.
�׷��Ƿ� exception handle�� ���־�� �Ѵ�.
*/
#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <limits.h>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);
#define defaultCh 100

int wantCh, broken_num, min_count = INT_MAX;
int broken[10];

void InputInfo();
inline void GetMin1() { min_count = abs(wantCh - defaultCh); }
void GetMin2();
void GetMin3();
bool isPossible(int n);
inline void PrintMin() { cout << min_count; }
int GetDigit(int n);

int main(void) {
	fastio;
	InputInfo();
	GetMin1();
	if (min_count || broken_num == 10) {
		GetMin2();
		GetMin3();
	}
	PrintMin();

	return 0;
} 

void InputInfo() {
	cin >> wantCh >> broken_num;

	for (int i = 0; i < broken_num; i++) {
		int tmp;
		cin >> tmp;
		broken[i] = tmp;
	}
}

void GetMin2() {
	if (isPossible(wantCh))
		min_count = min(min_count, GetDigit(wantCh));
}

void GetMin3() {
	int up = wantCh;
	int down = wantCh;
	int count = 0;

	while (++count < min_count) {
		if (down >= 0 && isPossible(--down)) {
			min_count = min(min_count, count + GetDigit(down));
			return;
		}

		if (isPossible(++up)) {
			min_count = min(min_count, count + GetDigit(up));
			return;
		}
	}
}

bool isPossible(int n) {
	string str = to_string(n);

	for (int i = 0; i < str.length(); i++) {
		int tmp = str[i] - '0'; // char���� �׳� int������ ��ȯ�� ���ָ� ascii code������ �ٲ�� �Ǵ� ���̴�.
		for (int j = 0; j < broken_num; j++) {
			if (broken[j] == tmp) 
				return false;
		}
	}

	return true;
}

int GetDigit(int n) {
	// 0�� ���ؼ� exception handling
	if (!n)
		return 1;

	int count = 0;
	while (n) {
		n /= 10;
		count++;
	}

	return count;
}