/*
이 문제는 분류 작업을 2번을 진행해 주어야 한다. 
소의 시작시간이 기준점일 때와 소의 끝나는 시간이 기준점일 떄로 구분을 해주어야 한다.
이 2번의 분류작업을 한꺼번에 진행을 할 수도 있고 따로 따로 진행을 하여도 된다.
ver1: 한꺼번에 분류를 진행해서 답을 찾는 과정이다,
ver2: 따로 따로 분류를 진행하여 답의 후보를 점점 줄여가면서 답을 찾는 과정이다.
*/

#include <iostream>
#include <queue>
#include <utility>
#include <algorithm>
#include <vector>

using namespace std;

#define fastio ios_base::sync_with_stdio(0), cin.tie(0);

using Time = pair<int, int>;

int hen, cow;
vector<Time> forcow;
vector<int> forhen;

void HelpCow();
void InputInfo();
void Sorting();
int CountCowNumber();

int main(void) {
	fastio;
	HelpCow();

	return 0;
}

void HelpCow() {
	InputInfo();
	Sorting();
	cout << CountCowNumber();
}

void InputInfo() {
	cin >> hen >> cow;
	
	for (int i = 0; i < hen; i++) {
		int tmp;
		cin >> tmp;
		forhen.push_back(tmp);
	}

	for (int i = 0; i < cow; i++) {
		int tmp1, tmp2;
		cin >> tmp1 >> tmp2;
		forcow.emplace_back(tmp1, tmp2);
	}
}

void Sorting() {
	sort(forhen.begin(), forhen.end());
	sort(forcow.begin(), forcow.end());
}

int CountCowNumber() {
	int count = 0, j = 0;
	priority_queue<int, vector<int>, greater<int>> cont;

	for (int i = 0; i < hen; i++) {
		while (j < cow && forcow[j].first <= forhen[i])
			cont.push(forcow[j++].second);

		while (!cont.empty() && forhen[i] > cont.top())
			cont.pop();

		if (!cont.empty()) {
			cont.pop();
			count++;
		}
	}

	return count;
}