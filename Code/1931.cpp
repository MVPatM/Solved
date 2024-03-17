/*
미팅이 없어서 회의실이 비어있을 때 제일 빨리 끝나는 회의를 
회의실에서 이용하도록 해주면 된다. 
미팅이 시작하자마자 끝날수도 있기 때문에 시작시간도 정렬을 해주어야한다.
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