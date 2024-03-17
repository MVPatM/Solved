/*
처음에
반복문의 마지막에 조건이 성립하는 경우를 고려하지 못했다. (end < line 으로 code를 작성을 할 때)
*/
#include <iostream>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);

int line, target;
int ar[10000];

void InputInfo();
void GetCase();

int main(void) {
	fastio;
	InputInfo();
	GetCase();
	
	return 0;
}

void InputInfo() {
	cin >> line >> target;

	for (int i = 0; i < line; i++) {
		int tmp;
		cin >> tmp;
		ar[i] = tmp;
	}
}

void GetCase() {
	int add = 0;
	int count = 0;
	bool isend = false;

	for (int start = 0; start < line; start++, add = 0) {
		for (int end = start; end <= line; end++) {
			if (add < target) {
				if (end == line)
					isend = true;
				add += ar[end];
			}
			else if (add == target) {
				count++;
				break;
			}
			else {
				break;
			}
		}

		if (isend)
			break;
	}

	cout << count;
}