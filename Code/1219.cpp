/*
negative cycle이 존재하는데 그게 finish값에 영향을 줄 수도 있고 영향을 안 줄수도 있다.
이것이 예외사항을 만들어 낼 수있다.

만약 bellman ford algorithm을 사용하면 
처음에 v-1번만큼 모든 edge에 대해서 edge relaxion을 하고 
negative cycle이 finish값에 영향을 주는 지 확인을 하기 위해서는
v번만큼 모든 edge에 대해서 edge relaxion을 해서 finish값이 바뀌는 지를 확인한다.
바뀌면 negative cycle이 finish값에 영향을 주는 것이고 바뀌지 않으면 finish값에 영향을 주지 않는 cycle인 것이다.
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
// int를 사용을 하면 문제스펙에 맞지 않아서 error가 발생한다. 
// 만약 100개의 city에 cycle이 형성이 되어 있다면
// 100 * 100 * 10000000의 값이 만들어 지기 때문에 overflow가 발생한다.
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