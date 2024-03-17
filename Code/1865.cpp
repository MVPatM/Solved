/*
using vs #define �����ϱ�
using 1. �ڷ��� �̸� ������
      2. �Լ����� ������
#define 1. ��ũ�� ���
        2. ��ũ�� �Լ�
		3. �⺻������ �������ִ� ��� ex) __TIME__ ���...
*/
/*
��� vertex�� �̾��� �ִ� graph�� ������ �ؼ� ���ܻ�Ȳ�� control���� ������.
��� vertex�� ����Ǿ� ���� �ʴ� ��Ȳ�� ����ؾ� �ϹǷ� Inf�� ���� ���� �� edge�� ������ ������ �ϴ� ������ 
���־��Ѵ�.
ver1: bellman ford�˰����� ����Ѵ�.
ver2: SPFA�˰����� ����Ѵ�.
	  vertex�� �������� graphŽ���� �����Ѵ�.
	  �ϴ� ��� vertex�� queue�� �ִ´�. 
	  queue���� vertex ��ȣ�� ������ �� vertex���� �����ϴ� edge�� ����� �����Ѵ�. �׸����� edge����� ���ؼ�
	  �ݴ����� vertex�� cost���� ������ ��Ű�� �� vertex�� queue�� �־ Ž���� �ϵ��� �Ѵ�.
	  �ֳ��ϸ� �� vertex�� ���� ������ �Ǿ��� ������ �� vertex���� ����ϴ� path�� �ּҰ��� ������ �� �� �ֱ� �����̴�.
	  �׷��� �������� queue�� ���� ������ ���� cycle�� �����ϴ� ���̰� queue�� ���� ������ ���� cycle�� �������� �ʴ� ���̴�.
*/
// size�Լ��� sizeof�Լ��� ���̰� �����Ѵ�.
// size�Լ�: container�� array�� length or size�� return ���ִ� �Լ��̴�.
// sizeof�Լ�: array�� �����ϰ� �ִ� memory������ �����ϴ� byte���� return ���ִ� �Լ��̴�.
/*
	���� count++�� �ϴµ� queue�� �ִ� �� Ȯ���� ���� �ʰ� count�� ���ְ� �Ǹ�
	input���� �ִ� edge�� cost�� ������ �޴´�.
	�׷��� ���� 1���� 2�ΰ��� ��Ȧ�� ���� �ɸ��� �ð��� ������������ input�� �Ǹ� ��� count�� �ö󰡱� ������
	���� cycle�̴��� ���� cycleó�� �ν��� �ϴ� ��찡 �߻� �� �� �ִ�.
*/
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstring>
#include <deque>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0)
#define Max 501
#define Inf 30000000

int testcase, point_num, road_num, wormhole_num;
// vector�� 2���� ����ϸ� compiler�� ���� vector�� ������ ������ 1���� vector�� ����� �ͺ��� �� ���� �޸𸮸� ����� �� �� �ִ�.
vector<pair<pair<int, int>, int>> road; // (vertex1, vertex2), cost
vector<pair<pair<int, int>, int>> wormhole; // (start, finish), cost
int cost[Max];
int Count[Max];
bool InQ[Max];
bool isvisited[Max];
vector<pair<pair<int, int>, int>> edge;
vector<vector<pair<int, int>>> Edge;

void InputTestCaseNum() { cin >> testcase; }

void InputInfo();
void InputInfoVer1();
void Init(); // Initialize cost value of the vertex
void DoWormhole();
void BellmanFord();
void Spfa();
void ClearVector() { Edge.clear(); }

int main(void) {
	fastio;
	DoWormhole();

	return 0;
}

void InputInfo() {
	cin >> point_num >> road_num >> wormhole_num;

	for (int i = 0; i < road_num; i++) {
		int v1, v2, c;
		cin >> v1 >> v2 >> c;
		edge.emplace_back(make_pair(v1, v2), c);
	}

	for (int i = 0; i < wormhole_num; i++) {
		int f, t, c;
		cin >> f >> t >> c;
		edge.emplace_back(make_pair(f, t), c);
	}
}

void InputInfoVer1() {
	cin >> point_num >> road_num >> wormhole_num;
	vector<pair<int, int>> tmp;
	int i, from, to, c;

	for (i = 0; i <= point_num; i++)
		Edge.push_back(tmp);
	
	for (i = 0; i < road_num; i++) {
		cin >> from >> to >> c;
		Edge[from].emplace_back(to, c);
		Edge[to].emplace_back(from, c);
	}

	for (i = 0; i < wormhole_num; i++) {
		cin >> from >> to >> c;
		Edge[from].emplace_back(to, -c);
	}
}

void Init() {
	memset(InQ, 0, sizeof(InQ)); 
	memset(Count, 0, sizeof(Count));
	for (int i = 0; i <= point_num; i++)
		cost[i] = Inf;

}

void BellmanFord() {
	for (int i = 1; i < point_num; i++) {
		for (int j = 0; j < road_num; j++) {
			cost[edge[j].first.second] = min(cost[edge[j].first.second], cost[edge[j].first.first] + edge[j].second);
			cost[edge[j].first.first] = min(cost[edge[j].first.first], cost[edge[j].first.second] + edge[j].second);
		}

		for (int j = road_num; j < wormhole_num; j++)
			cost[edge[j].first.second] = min(cost[edge[j].first.second], cost[edge[j].first.first] - edge[j].second);
	}

	for (int i = 0; i < road_num; i++) {
		if (cost[edge[i].first.second] > cost[edge[i].first.first] + edge[i].second) {
			cout << "YES\n";
			return;
		}
		if (cost[edge[i].first.first] > cost[edge[i].first.second] + edge[i].second) {
			cout << "YES\n";
			return;
		}
	}

	// v�� ����� �� ���� edge�� ����Ѵٰ� �ؼ� ���� cycle�� ��� �ľ� �ϴ� ���� �Ұ��� �ϴ�.
	for (int i = road_num; i < wormhole_num; i++) {
		if (cost[edge[i].first.second] > cost[edge[i].first.first] - edge[i].second) {
			cout << "YES\n";
			return;
		}
	}

	cout << "NO\n";
}

void Spfa() {
	int i, j, next, c;
	deque<int> dq;

	for (i = 1; i <= point_num; i++) {
		if (!isvisited[next]) {
			Init();
			cost[i] = 0;
			dq.push_back(i);
			InQ[i] = true;
			Count[i]++;

			while (!dq.empty()) {
				int cur = dq.front();
				dq.pop_front();
				InQ[cur] = false;

				for (j = 0; j < Edge[cur].size(); j++) {
					next = Edge[cur][j].first;
					c = Edge[cur][j].second;
					if (cost[cur] + c < cost[next]) {
						cost[next] = cost[cur] + c;
						isvisited[next] = true;

						if (Count[next] >= point_num) {
							cout << "YES\n";
							return;
						}
						
						if (!InQ[next]) {
							Count[next]++;
							InQ[next] = true;
							if (dq.empty() || cost[next] <= cost[dq.front()])
								dq.push_front(next);
							else
								dq.push_back(next);
						}
					}
				}
			}
		}
	}
	cout << "NO\n";
}

void DoWormhole() {
	InputTestCaseNum();

	for (int i = 0; i < testcase; i++) {
		InputInfoVer1();
		Init();
		memset(isvisited, 0, sizeof(isvisited));
		Spfa();
		ClearVector();
	}
}