/*
negative cycle�� �����ϴµ� �װ� finish���� ������ �� ���� �ְ� ������ �� �ټ��� �ִ�.
�̰��� ���ܻ����� ����� �� ���ִ�.

���� bellman ford algorithm�� ����ϸ� 
ó���� v-1����ŭ ��� edge�� ���ؼ� edge relaxion�� �ϰ� 
negative cycle�� finish���� ������ �ִ� �� Ȯ���� �ϱ� ���ؼ���
v����ŭ ��� edge�� ���ؼ� edge relaxion�� �ؼ� finish���� �ٲ�� ���� Ȯ���Ѵ�.
�ٲ�� negative cycle�� finish���� ������ �ִ� ���̰� �ٲ��� ������ finish���� ������ ���� �ʴ� cycle�� ���̴�.
*/
#include <iostream>
#include <vector>
#include <utility>
#include <deque>
#include <queue>
#include <cstring>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0)
#define Inf 200000000
// int�� ����� �ϸ� �������忡 ���� �ʾƼ� error�� �߻��Ѵ�. 
// ���� 100���� city�� cycle�� ������ �Ǿ� �ִٸ�
// 100 * 100 * 10000000�� ���� ����� ���� ������ overflow�� �߻��Ѵ�.
using piLL = pair<int, long long>;

int city_num, start, finish, trans_num;
long long cost[100];
int Count[100];
bool InQ[100];
bool isvisited[100];
vector<vector<piLL>> edge; // (start, (finish, cost))

void InputInfo();
void UpdateCost();
void Init();
void Spfa();
bool isconnected(queue<int> q);
void GetMaxMoney();

int main(void) {
	fastio;
	GetMaxMoney();

	return 0;
}

void InputInfo() {
	cin >> city_num >> start >> finish >> trans_num;
	vector<piLL> tmp;
	
	for (int i = 0; i < city_num; i++)
		edge.push_back(tmp);

	for (int i = 0; i < trans_num; i++) {
		int s, f, c;
		cin >> s >> f >> c;
		edge[s].emplace_back(f, c);
	}

	for (int i = 0; i < city_num; i++) {
		int c;
		cin >> c;
		cost[i] = c;
	}
}

void UpdateCost() {
	for (int i = 0; i < city_num; i++) {
		for (int j = 0; j < edge[i].size(); j++) {
			int next = edge[i][j].first;
			edge[i][j].second -= cost[next];
		}
	}
}

void Init() {
	int c = cost[start];

	for (int i = 0; i < city_num; i++)
		cost[i] = Inf;
	cost[start] = -c;
	memset(Count, 0, sizeof(Count));
	memset(InQ, 0, sizeof(InQ));
	memset(isvisited, 0, sizeof(isvisited));
}

void Spfa() {
	bool iscycle = false;
	queue<int> dq;
	queue<int> Q;
	dq.push(start);
	InQ[start] = true;

	while (!dq.empty()) {
		int cur = dq.front();
		dq.pop();
		InQ[cur] = false;

		for (int i = 0; i < edge[cur].size(); i++) {
			int next = edge[cur][i].first;
			long long c = edge[cur][i].second;

			if (cost[cur] + c < cost[next]) {
				cost[next] = cost[cur] + c;

				if (!InQ[next]) {
					InQ[next] = true;
		 			if (++Count[next] < city_num) 
						dq.push(next);
					else {
						// existing negative cycle, push to queue
						// so if any city is in queue, that city is on negative cycle
						isvisited[next] = true;
						Q.push(next);
					}
				}
			}
		}
	}

	if (cost[finish] == Inf)
		cout << "gg";
	else if (isconnected(Q))
		cout << "Gee";
	else
		cout << -cost[finish];
}

// Using BFS, check if negative cycle is connected to finish
bool isconnected(queue<int> q) {
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		
		for (int i = 0; i < edge[cur].size(); i++) {
			int next = edge[cur][i].first;
			if (!isvisited[next]) {
				q.push(next);
				isvisited[next] = true;
			}
		}
	}

	return isvisited[finish];
}

void GetMaxMoney() {
	InputInfo();
	UpdateCost();
	Init();
	Spfa();
}