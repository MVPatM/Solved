/*
������ ��� ȸ�ǽ��� ������� �� ���� ���� ������ ȸ�Ǹ� 
ȸ�ǽǿ��� �̿��ϵ��� ���ָ� �ȴ�. 
������ �������ڸ��� �������� �ֱ� ������ ���۽ð��� ������ ���־���Ѵ�.
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);
using Mtime = pair<int, int>;

bool cmp1(Mtime m1, Mtime m2) {
	return m1.first < m2.first;
}

bool cmp2 (Mtime m1, Mtime m2) {
	return m1.second < m2.second;
}

vector<Mtime> meeting;

void InputInfo();
void Sorting();
void Scheduling();

int main(void) {
	fastio;
	InputInfo();
	Sorting();
	Scheduling();

	return 0;
}

void InputInfo() {
	int n;
	cin >> n;

	for (int i = 0; i < n; i++) {
		int tmp1, tmp2;
		cin >> tmp1 >> tmp2;
		meeting.emplace_back(tmp1, tmp2);
	}
}

void Sorting() {
	sort(meeting.begin(), meeting.end(), cmp1);
	sort(meeting.begin(), meeting.end(), cmp2);
}

void Scheduling() {
	int m = 0;
	int end = 0;

	for(int i = 0; i < meeting.size(); i++){
		if (end <= meeting[i].first) {
			end = meeting[i].second;
			m++;
		}
	}

	cout << m;
}