#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <cstring>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);
#define INF 10000
using pii = pair<int, int>;

int dist_num, range, road_num;
bool isvisited[101];
int cost[101];
int item[101];
vector<vector<pii>> ground(101);

void InputInfo();
inline void Init() { fill(cost, cost + dist_num + 1, INF), memset(isvisited, 0, sizeof(isvisited)); }
void Solve();

int main(void) {
	fastio;
	InputInfo();
	Solve();

	return 0;
}

void InputInfo() {
	int i;
	cin >> dist_num >> range >> road_num;

	for (int i = 1; i <= dist_num; i++)
		cin >> item[i];

	for (int i = 0; i < road_num; i++) {
		int d1, d2, len;
		cin >> d1 >> d2 >> len;
		ground[d1].emplace_back(d2, len);
		ground[d2].emplace_back(d1, len);
	}
}

void Solve() {
	int maxitem = 0;
	for (int i = 1; i <= dist_num; i++) {
		Init();
		int tmp = 0;
		priority_queue<pii, vector<pii>, greater<pii>> pq;
		cost[i] = 0;
		pq.emplace(i, 0);

		while (!pq.empty()) {
			pii cur = pq.top();
			// ���� code�� �߰� �������� ������ item������ �ߺ����� ����ϰ� �Ǵ� ������ �߻��Ѵ�.
			if (!isvisited[cur.first])
				tmp += item[cur.first];
			isvisited[cur.first] = true;
			pq.pop();

			for (int j = 0; j < ground[cur.first].size(); j++) {
				pii next = ground[cur.first][j]; // ground���� �̾� ���� ���̹Ƿ� second���� ���� ���̸� �ǹ��Ѵ�.
				int newcost = cur.second + next.second;

				if ((cost[next.first] > newcost) && (newcost <= range)) {
					cost[next.first] = newcost;
					pq.emplace(next.first, newcost);
				}
			}
		}

		maxitem = max(maxitem, tmp);
	}

	cout << maxitem;
}