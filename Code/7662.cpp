/*
1. max�� ������ ���� maxheap�� min�� ������ ���� minheap�� �����
	minheap�� maxheap������ ������ ���� �� �ִ� ��ġ�� �ʿ��ϴ�.
	�� ��ġ�� ���° �������� priority queue�� ���� ������ ������ ���ָ� �ȴ�.
	�׷��� ������ �� ���° �������� ���� ������ Ȯ���� �ϰ� �����Ǿ��ٰ� data���� �˷� �ָ� �ȴ�.

*/
#include <iostream>
#include <queue>
#include <set>
#include <functional>

using namespace std;

#define fastio ios_base::sync_with_stdio(0), cin.tie(0);
using pii = pair<int, int>;

bool isinQueue[1000001];

void DualPQ();
void DualPQVer2();

int main(void) {
	fastio;
	DualPQVer2();

	return 0;
}

void DualPQ() {
	int testcase, order_num;
	cin >> testcase;

	for (int i = 0; i < testcase; i++) { // i = ����� testcase������ �˷��ش�.
		// greater<pair<int, int>>�� first�� ũ�� �켱������ �� ���� �ΰ� first�� ���� ���� �ι�°�� ũ�� Ŭ���� �켱������ �� ���� �д�.
		priority_queue<pii> forMax; // (priority queue�� ���� ��, ���° ��ɾ ���� ���� �� ǥ��)
		// �� ũ�� ������ heap������ �� ����� ���� �ʱ� ������ greater�� ����� �ؾ� minheap�� ����� ����.
		priority_queue<pii, vector<pii>, greater<pii>> forMin;
		char order_kind;
		int input_num, Qlen = 0;
		cin >> order_num;
		// �ѹ��� testcase�� ������ �ش� �ڷᱸ���� �ʱ�ȭ�� �����־�� �Ѵ� �׷��� ������ ���� testcase�� �������� data�� �����ϱ� �����̴�.

		for (int j = 1; j <= order_num; j++) { // j = ���° ����� ��ɾ����� �˷��ش�.
			cin >> order_kind;

			if (order_kind == 'I') { // insert
				cin >> input_num;
				Qlen++;
				isinQueue[j] = true;
				forMax.emplace(input_num, j);
				forMin.emplace(input_num, j);
			}
			else if (order_kind == 'D') {
				int MinMaxkind, curS;
				cin >> MinMaxkind;
				
				if (!Qlen)
					continue;

				Qlen--;
				if (MinMaxkind == 1) { // �ִ� ����
					do {
						curS = forMax.top().second;
						forMax.pop();
					} while (!isinQueue[curS] && !forMax.empty());

					isinQueue[curS] = false;
				}
				else if (MinMaxkind == -1) { // �ּڰ� ����
					do {
						curS = forMin.top().second;
						forMin.pop();
					} while (!isinQueue[curS] && !forMin.empty()); // or�� ����ϸ� empty�� �ƴ� ������ ��� �ݺ����� ����.

					isinQueue[curS] = false;
				}
			}
		}

		if (!Qlen)
			cout << "EMPTY\n";
		else {
			int mx, mn, cur;

			do {
				mx = forMax.top().first;
				cur = forMax.top().second;
				forMax.pop();
			} while (!isinQueue[cur]);

			do {
				mn = forMin.top().first;
				cur = forMin.top().second;
				forMin.pop();
			} while (!isinQueue[cur]);

			cout << mx << " " << mn << "\n";
		}
	}
}

// set�̿�
void DualPQVer2() {
	int testcase;
	cin >> testcase;

	for (int i = 0; i < testcase; i++) {
		int order_num;
		multiset<int> s;
		cin >> order_num;
		 

		for (int i = 0; i < order_num; i++) {
			char order_kind;
			cin >> order_kind;

			if (order_kind == 'I') {
				int num;
				cin >> num;
				s.insert(num);
			}
			else if (order_kind == 'D') {
				int Del_kind;
				cin >> Del_kind;

				if (s.empty())
					continue;

				if (Del_kind == 1) 
					s.erase(--s.end());
				else if (Del_kind == -1)
					s.erase(s.begin());
			}
		}

		if (s.empty()) 
			cout << "EMPTY\n";
		else 
			cout << *(--s.end()) << " " << *s.begin() << "\n";
	}
}