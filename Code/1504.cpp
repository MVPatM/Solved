/*
�ִ� �Ÿ� �ε� �ߺ��Ǵ� ������ ������ �� ������ �ִ� �Ÿ��� �ƴϴ�.
�ֳ��ϸ� �� ������ �ѹ��� ������ ����� route�� ����� �� �� �ֱ� �����̴�.
*/
#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <algorithm>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);
#define INF 700000000 // 10������ ������ �ϸ� overflow�� �߻��� �� �� �ִ�.
// greater<pii>�� �Ͽ��� ����� ����.
using pii = pair<int, int>; // distance, vertex 

int vertexNum, edgeNum, targetV1, targetV2;
int d[801];
vector<vector<pii>> graph(801);

void InputInfo();
inline void Init() { fill(d, d + vertexNum + 1, INF); }
void Dijkstra(int s);
void Solve();

int main(void) {
	fastio;
	InputInfo();
	Solve();

	return 0;
}

void InputInfo() {
	cin >> vertexNum >> edgeNum;

	for (int i = 0; i < edgeNum; i++) {
		int v1, v2, cost;
		cin >> v1 >> v2 >> cost;
		graph[v1].emplace_back(v2, cost);
		graph[v2].emplace_back(v1, cost);
	}

	cin >> targetV1 >> targetV2;
}

void Dijkstra(int s) {
	priority_queue<pii, vector<pii>, greater<pii>> pq;
	Init();
	d[s] = 0;
	pq.emplace(d[s], s);

	while (!pq.empty()) {
		pii cur = pq.top(); // cur.second = vertex, cur.first = d[v]��
		pq.pop();
		int cur_cost = cur.first;
		int cur_vertex = cur.second;

		for (int i = 0; i < graph[cur_vertex].size(); i++) {
			int next_vertex = graph[cur_vertex][i].first;
			int edgecost = graph[cur_vertex][i].second;

			if (d[next_vertex] >= cur_cost + edgecost) {
				d[next_vertex] = d[cur_vertex] + edgecost;
				pq.emplace(cur_cost + edgecost, next_vertex);
			}
		}
	}
}

// ���ͽ�Ʈ�� �˰����� 2���� ������ �Ͽ��� ������ �ذ��� �� �ִ�.
void Solve() {
	Dijkstra(targetV1);
	int p1 = d[targetV2]; // from v2 to v1
	int p2 = d[1]; // from v1 to 1
	int p3 = d[vertexNum]; // from v1 to vertexnum

	Dijkstra(targetV2);
	int p4 = d[1]; // from v2 to 1
	int p5 = d[vertexNum]; // from v2 to vertexnum
	int ans = min(p1 + p2 + p5, p1 + p3 + p4);

	// �������� ������ v1�� v2�� ������ ans�� INF���� �� ���ִ�.
	if (ans > INF) // =�� �Ⱥٿ��� ���� ��찡 �߻��Ͽ���.
		cout << "-1";
	else
		cout << ans;
}