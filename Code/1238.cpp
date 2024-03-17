/*
Dijkstra알고리즘은 한 점에서 다른 한 점까지의 최단 거리를 구하는 알고리즘이 아니라
한 점에서 다른 모든 점까지의 최단 거리를 구할 수 있는 알고리즘이다.
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>
#include <cstring>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);
#define Inf 10000000
using pii = pair<int, int>;

int std_num, road_num, PartyPlace;
// vector index를 잘못 입력해도 compile error가 발생하지 않는다.
vector<vector<pair<int, int>>> viliage[2]; // (cost, finish), 0: 순방향 1: 역방향
int cost[1001]; // viliage나 student에서 0은 존재 하지 않는다. 다익스트라 알고리즘에 사용하기 위한 data -> inf로 초기화해야 한다.
int dist[1001];
bool isvisited[1001];

void InputInfo();
int GetMaxTimetoGo();
void Init();
void Dijkstra(bool dir);

int main(void) {
	fastio;
	InputInfo();
	cout << GetMaxTimetoGo();

	return 0;
}

void InputInfo() {
	cin >> std_num >> road_num >> PartyPlace;
	vector<pair<int, int>> tmp;
	for (int i = 0; i <= std_num; i++) {
		viliage[0].push_back(tmp);
		viliage[1].push_back(tmp);
	}

	for (int i = 0; i < road_num; i++) {
		int s, f, c;
		cin >> s >> f >> c;
		viliage[0][s].emplace_back(c, f);
		viliage[1][f].emplace_back(c, s);
	}
}

int GetMaxTimetoGo() {
	int ans = 0;
	Init();
	Dijkstra(0);
	Init();
	Dijkstra(1);

	for (int i = 1; i <= std_num; i++)
		ans = max(ans, dist[i]);

	return ans;
}

void Init() {
	fill(cost, cost + std_num + 1, Inf);
	memset(isvisited, 0, sizeof(isvisited));
}

void Dijkstra(bool dir) {
	priority_queue<pii, vector<pii>, greater<pii>> pq;
	cost[PartyPlace] = 0;
	pq.emplace(0, PartyPlace); // (cost, pos)

	while (!pq.empty()) {
		int curP = pq.top().second;
		int curC = pq.top().first;
		pq.pop();

		if (isvisited[curP])
			continue;

		isvisited[curP] = true;

		for (int i = 0; i < viliage[dir][curP].size(); i++) {
			int nextP = viliage[dir][curP][i].second;
			int nextC = viliage[dir][curP][i].first;

			if (cost[nextP] > curC + nextC) {
				cost[nextP] = curC + nextC;
				pq.emplace(curC + nextC, nextP);
			}
		}
	}

	for (int i = 1; i <= std_num; i++)
		dist[i] += cost[i];
}