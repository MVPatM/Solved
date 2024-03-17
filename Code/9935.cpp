/*
version1: stack에 폭발 문자열중 일부와 순서가 같으면 stack에
폭발 x문자열이 될 수있는 후보이기 때문에 stack에 일부분의 마지막 index를 stack에 저장한다.
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
			if (boomstr.length() != 1) // 폭발문자열의 길이가 1인 경우 예외처리
				dq.push_back(0);
		}
		else if (dq.empty())
			ans += str[i];
		else { // empty인 경우는 존재하지 않는다.
			int top_value = dq.back();
			if (str[i] == boomstr[top_value + 1]) {
				dq.pop_back();

				if ((top_value + 2) != boomstr.length()) // 폭발 문자열이 완성되지 않은 경우 deque에 push
					dq.push_back(top_value + 1);
			}
			else { // a = a + b를 하는 것이 a += b를 하는 것보다 더 시간이 많이 걸린다. 그래서 timeover발생
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