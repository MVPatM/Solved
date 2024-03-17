/*
사용하는 메모리 계산하는 법
1mb = 1024kb
1kb = 1024byte
int -> 4byte
*/
/*
이미 탐색한 node에 새롭게 더 큰 중량이 새로운 다리로 건너는 것이 가능하면
다시 탐색하지 않도록 algorithm을 설계를 했기 때문에 문제가 발생한다.
그래서 공장끼리 갈 수있는 최대 중량을 구하는 데에 있어서 오답이 발생을 한다.
그리고 한 섬에서 다리 중량이 제일 큰 다리를 선택하고 새로 선택된 섬에서의 최대 중량을 가진 다리를 선택을 하면
오답이 발생하게 된다. selected graph와 unselected graph사이를 이을 때 중량이 최대인 다리로 이어야만 
오답이 발생하지 않게 된다. 
*/
/*
ver1: kruskal알고리즘을 사용을 하면 start와 finish와 연결이 되어있지 않은 섬을 잇는 다리를 선택을 할 수도 있기 때문에 시간이 낭비가 된다.
	  그래서 prim 알고리즘을 사용을 해서 문제를 해결한다. 이 때는 minimum spanning tree를 만들기 위한 것이 아니라 
	  maximum spanning tree를 만들기 위한 알고리즘이다.
ver2: kruskal 알고리즘을 사용을 해서 문제를 해결할 수도 있다.
      입력을 받으면 그냥 priority queue에 넣어서 문제를 해결하면 메모리를 더 줄일 수 있다.
ver3: binary search로 무게를 계속 변경하여서 공장이 있는 섬끼리 해당 무게가 건널수 있는지 없는 지를 판단하여
	  공장을 건널수 있는 최대 무게를 구한다.
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>
#include <limits.h>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);
using node = pair<int, int>;
using Vnode = vector<node>;

struct comp {
	bool operator()(node i1, node i2) {
		return i1.second < i2.second;
	}
};

vector<Vnode> island;
bool isvisited[100001];
int fac1, fac2; // 공장이 있는 섬의 위치

void initialize(int n);
void InputInfo();
void GetMaxweight();

int main(void) {
	fastio;
	InputInfo();
	GetMaxweight();

	return 0;
}

void initialize(int n) {
	vector<node> tmp;

	for (int i = 0; i <= n; i++) 
		island.push_back(tmp);
}

void InputInfo() {
	int islandNum, bridge; // 섬의 개수, 다리의 개수
	cin >> islandNum >> bridge;
	initialize(islandNum); // 다리 정보를 저장할 vector initialize

	for (int i = 0; i < bridge; i++) {
		int ia, ib, w;
		cin >> ia >> ib >> w;
		island[ia].emplace_back(ib, w);
		island[ib].emplace_back(ia, w);
	}

	cin >> fac1 >> fac2;
}

void GetMaxweight() {
	priority_queue<node, vector<node>, comp> cand;
	int cur = fac1, Maxlimit = INT_MAX;

	while (cur != fac2) {
		isvisited[cur] = true;

		for (int i = 0; i < island[cur].size(); i++) {
			if (!isvisited[island[cur][i].first]) 
				cand.push(island[cur][i]);
		}

		cur = cand.top().first;
		Maxlimit = min(Maxlimit, cand.top().second);
		cand.pop();
	}

	cout << Maxlimit;
}