/*
version1: stack�� ���� ���ڿ��� �Ϻο� ������ ������ stack��
���� x���ڿ��� �� ���ִ� �ĺ��̱� ������ stack�� �Ϻκ��� ������ index�� stack�� �����Ѵ�.
*/
#include <iostream>
#include <stack>
#include <deque>
#include <cstring>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);

string str;
string boomstr;
string ans = "";
int idx = 0;
char ans1[1000001];

inline void InputInfo() { cin >> str >> boomstr; }
void BoomStr();
void BoomStr1();
void PrintResult();

int main(void) {
	fastio;
	InputInfo();
	BoomStr1();
	PrintResult();

	return 0;
}

void PrintResult() {
	if (idx) {
		for (int i = 0; i < idx; i++)
			cout << ans1[i];
	}
	else 
		cout << "FRULA";
}

void BoomStr() {
	deque<int> dq;

	for (int i = 0; i < str.length(); i++) {
		if (str[i] == boomstr[0]){
			if (boomstr.length() != 1) // ���߹��ڿ��� ���̰� 1�� ��� ����ó��
				dq.push_back(0);
		}
		else if (dq.empty())
			ans += str[i];
		else { // empty�� ���� �������� �ʴ´�.
			int top_value = dq.back();
			if (str[i] == boomstr[top_value + 1]) {
				dq.pop_back();

				if ((top_value + 2) != boomstr.length()) // ���� ���ڿ��� �ϼ����� ���� ��� deque�� push
					dq.push_back(top_value + 1);
			}
			else { // a = a + b�� �ϴ� ���� a += b�� �ϴ� �ͺ��� �� �ð��� ���� �ɸ���. �׷��� timeover�߻�
				while (!dq.empty()) {
					ans += boomstr.substr(0, dq.front() + 1);
					dq.pop_front();
				}

				ans += str[i];
			}
		}
	}

	while (!dq.empty()) {
		ans += boomstr.substr(0, dq.front() + 1);
		dq.pop_front();
	}
}

//
void BoomStr1() {
	for (int i = 0; i < str.length(); i++) {
	   	ans1[idx++] = str[i];

		if (idx < boomstr.length())
			continue;

		if (str[i] == boomstr[boomstr.length() - 1]) {
			bool isboom = true;
			for (int j = 2; j <= boomstr.length(); j++) {
				if (ans1[idx - j] != boomstr[boomstr.length() - j]) {
					isboom = false;
					break;
				}
			}

			if (isboom)
				idx -= boomstr.length();
		}
	}
}