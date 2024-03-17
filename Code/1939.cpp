/*
����ϴ� �޸� ����ϴ� ��
1mb = 1024kb
1kb = 1024byte
int -> 4byte
*/
/*
�̹� Ž���� node�� ���Ӱ� �� ū �߷��� ���ο� �ٸ��� �ǳʴ� ���� �����ϸ�
�ٽ� Ž������ �ʵ��� algorithm�� ���踦 �߱� ������ ������ �߻��Ѵ�.
�׷��� ���峢�� �� ���ִ� �ִ� �߷��� ���ϴ� ���� �־ ������ �߻��� �Ѵ�.
�׸��� �� ������ �ٸ� �߷��� ���� ū �ٸ��� �����ϰ� ���� ���õ� �������� �ִ� �߷��� ���� �ٸ��� ������ �ϸ�
������ �߻��ϰ� �ȴ�. selected graph�� unselected graph���̸� ���� �� �߷��� �ִ��� �ٸ��� �̾�߸� 
������ �߻����� �ʰ� �ȴ�. 
*/
/*
ver1: kruskal�˰����� ����� �ϸ� start�� finish�� ������ �Ǿ����� ���� ���� �մ� �ٸ��� ������ �� ���� �ֱ� ������ �ð��� ���� �ȴ�.
	  �׷��� prim �˰����� ����� �ؼ� ������ �ذ��Ѵ�. �� ���� minimum spanning tree�� ����� ���� ���� �ƴ϶� 
	  maximum spanning tree�� ����� ���� �˰����̴�.
ver2: kruskal �˰����� ����� �ؼ� ������ �ذ��� ���� �ִ�.
      �Է��� ������ �׳� priority queue�� �־ ������ �ذ��ϸ� �޸𸮸� �� ���� �� �ִ�.
ver3: binary search�� ���Ը� ��� �����Ͽ��� ������ �ִ� ������ �ش� ���԰� �ǳμ� �ִ��� ���� ���� �Ǵ��Ͽ�
	  ������ �ǳμ� �ִ� �ִ� ���Ը� ���Ѵ�.
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
int fac1, fac2; // ������ �ִ� ���� ��ġ

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
	int islandNum, bridge; // ���� ����, �ٸ��� ����
	cin >> islandNum >> bridge;
	initialize(islandNum); // �ٸ� ������ ������ vector initialize

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