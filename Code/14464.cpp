/*
�� ������ �з� �۾��� 2���� ������ �־�� �Ѵ�. 
���� ���۽ð��� �������� ���� ���� ������ �ð��� �������� ���� ������ ���־�� �Ѵ�.
�� 2���� �з��۾��� �Ѳ����� ������ �� ���� �ְ� ���� ���� ������ �Ͽ��� �ȴ�.
ver1: �Ѳ����� �з��� �����ؼ� ���� ã�� �����̴�,
ver2: ���� ���� �з��� �����Ͽ� ���� �ĺ��� ���� �ٿ����鼭 ���� ã�� �����̴�.
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