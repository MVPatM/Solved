/*
1. max값 삭제를 위한 maxheap과 min값 삭제를 위한 minheap을 만들고
	minheap과 maxheap사이의 정보를 얻을 수 있는 장치가 필요하다.
	그 장치에 몇번째 연산으로 priority queue에 들어온 것인지 저장을 해주면 된다.
	그래서 삭제할 때 몇번째 연산으로 들어온 것인지 확인을 하고 삭제되었다고 data에게 알려 주면 된다.

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

	for (int i = 0; i < testcase; i++) { // i = 몇번재 testcase인지를 알려준다.
		// greater<pair<int, int>>는 first가 크면 우선순위를 더 높게 두고 first가 같은 때는 두번째가 크면 클수록 우선순위를 더 높게 둔다.
		priority_queue<pii> forMax; // (priority queue에 들어가는 수, 몇번째 명령어에 의해 들어가는 지 표시)
		// 더 크지 않으면 heap안으로 더 깊숙이 들어가지 않기 때문에 greater을 사용을 해야 minheap이 만들어 진다.
		priority_queue<pii, vector<pii>, greater<pii>> forMin;
		char order_kind;
		int input_num, Qlen = 0;
		cin >> order_num;
		// 한번의 testcase가 끝나면 해당 자료구조를 초기화를 시켜주어야 한다 그렇지 않으면 전의 testcase에 남겨졌던 data가 존재하기 때문이다.

		for (int j = 1; j <= order_num; j++) { // j = 몇번째 실행된 명령어인지 알려준다.
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
				if (MinMaxkind == 1) { // 최댓값 삭제
					do {
						curS = forMax.top().second;
						forMax.pop();
					} while (!isinQueue[curS] && !forMax.empty());

					isinQueue[curS] = false;
				}
				else if (MinMaxkind == -1) { // 최솟값 삭제
					do {
						curS = forMin.top().second;
						forMin.pop();
					} while (!isinQueue[curS] && !forMin.empty()); // or을 사용하면 empty가 아닐 때까지 계속 반복문을 돈다.

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

// set이용
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