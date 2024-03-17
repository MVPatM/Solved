/*
another solution : union-find�� �̿�
data�� input�Ǹ鼭 ���� party�� ������ ���� parent�� �����ٰ� ������ ���ش�.
�׸��� ���ڿ� party ���������� ���캸�鼭 ���� ������ �˰� �ִ� ����� ���� parent�� �����ٸ�
�� party�� ������ ���ؾ� �ϴ� party�� count�� �Ѵ�.
�׷��� �ؼ� ����ǰ� ���� �� �ִ� party�� ���� ���Ѵ�.
*/
#include <iostream>
#include <queue>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);

int human_num, party_num;
queue<int> PeopleKnowTruth;

// ����̵� party�̵� index0�� �����Ѵ�.
bool isKnowTruth[51]; // � ����� ������ �ƴ��� ��Ÿ���� data
bool isTruthParty[51]; // truth�� ���ϴ� party���� ��Ÿ���� data
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
			if (Table[curPeo][p] && !isTruthParty[p]) { // party�� truth�� ���ϴ� ��Ƽ�̰� �� ������ ���Ե��� �ʾ����� party�����ο� Ȯ���ϱ�
				isTruthParty[p] = true;
				
				for (int h = 1; h <= human_num; h++) { // party�����ο� check�ϴ� ��
					if (Table[h][p] && !isKnowTruth[h]) { // Truth party�� ������ �ߴµ� ������ ������ ���� ���� ��� queue�� push
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
