/*
another solution : union-find를 이용
data가 input되면서 같은 party에 있으면 같은 parent를 가진다고 설정을 해준다.
그리고 난뒤에 party 구성원들을 살펴보면서 만약 진실을 알고 있는 사람과 같은 parent를 가진다면
그 party는 진실을 말해야 하는 party로 count를 한다.
그렇게 해서 과장되게 말할 수 있는 party의 수를 구한다.
*/
#include <iostream>
#include <queue>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);

int human_num, party_num;
queue<int> PeopleKnowTruth;

// 사람이든 party이든 index0은 무시한다.
bool isKnowTruth[51]; // 어떤 사람이 진실을 아는지 나타내는 data
bool isTruthParty[51]; // truth만 말하는 party인지 나타내는 data
bool Table[51][51]; // (people, party)

void InputInfo();
int GetPartyNumToOversell();

int main(void) {
	fastio;
	InputInfo();
	cout << GetPartyNumToOversell();

	return 0;
}

void InputInfo() {
	cin >> human_num >> party_num;

	int truth_num;
	cin >> truth_num;
	for (int i = 0; i < truth_num; i++) {
		int pnum;
		cin >> pnum;
		PeopleKnowTruth.push(pnum);
		isKnowTruth[pnum] = true;
	}

	for (int party = 1; party <= party_num; party++) {
		int Join_num;
		cin >> Join_num;
		for (int j = 0; j < Join_num; j++) {
			int tmp;
			cin >> tmp;
			Table[tmp][party] = true;
		}
	}
}

int GetPartyNumToOversell() {
	int ans = 0;

	while (!PeopleKnowTruth.empty()) {
		int curPeo = PeopleKnowTruth.front();
		PeopleKnowTruth.pop();

		for (int p = 1; p <= party_num; p++) {
			if (Table[curPeo][p] && !isTruthParty[p]) { // party가 truth만 말하는 파티이고 그 이전에 포함되지 않았으면 party참석인원 확인하기
				isTruthParty[p] = true;
				
				for (int h = 1; h <= human_num; h++) { // party참석인원 check하는 것
					if (Table[h][p] && !isKnowTruth[h]) { // Truth party에 참석을 했는데 이전에 진실을 알지 않은 경우 queue에 push
						isKnowTruth[h] = true;
						PeopleKnowTruth.push(h);
					}
				}
			}
			
		}
	}

	for (int p = 1; p <= party_num; p++) {
		if (!isTruthParty[p])
			ans++;
	}

	return ans;
}
