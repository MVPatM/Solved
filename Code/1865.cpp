/*
using vs #define 구분하기
using 1. 자료형 이름 간단히
      2. 함수형꼴 간단히
#define 1. 매크로 상수
        2. 매크로 함수
		3. 기본적으로 제공해주는 기능 ex) __TIME__ 등등...
*/
/*
모든 vertex가 이어져 있는 graph만 생각을 해서 예외상황을 control하지 못헀다.
모든 vertex가 연결되어 있지 않는 상황을 고려해야 하므로 Inf와 같은 값일 때 edge의 연산을 진행을 하는 조건을 
없애야한다.
ver1: bellman ford알고리즘을 사용한다.
ver2: SPFA알고리즘을 사용한다.
	  vertex를 기준으로 graph탐색을 진행한다.
	  일단 모든 vertex를 queue에 넣는다. 
	  queue에서 vertex 번호를 꺼내서 그 vertex에서 시작하는 edge의 계산을 진행한다. 그리고나서 edge계산을 통해서
	  반대편의 vertex의 cost값을 변경을 시키면 그 vertex를 queue에 넣어서 탐색을 하도록 한다.
	  왜냐하면 그 vertex의 값이 변경이 되었기 때문에 그 vertex에서 출발하는 path의 최소값이 변경이 될 수 있기 때문이다.
	  그래서 마지막에 queue에 값이 있으면 음의 cycle이 존재하는 것이고 queue에 값이 없으면 음의 cycle이 존재하지 않는 것이다.
*/
// size함수랑 sizeof함수는 차이가 존재한다.
// size함수: container나 array의 length or size를 return 해주는 함수이다.
// sizeof함수: array가 차지하고 있는 memory공간을 차지하는 byte수를 return 해주는 함수이다.
/*
	만약 count++를 하는데 queue에 있는 지 확인을 하지 않고서 count를 해주게 되면
	input으로 넣는 edge의 cost에 영향을 받는다.
	그래서 만약 1에서 2로가는 웜홀이 점점 걸리는 시간이 내림차순으로 input이 되면 계속 count가 올라가기 때문에
	양의 cycle이더라도 음의 cycle처럼 인식을 하는 경우가 발생 할 수 있다.
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
// vector를 2개를 사용하면 compiler가 만든 vector의 여유분 때문에 1개의 vector를 사용한 것보다 더 많은 메모리를 사용을 할 수 있다.
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

	// v번 계산할 때 음의 edge만 계산한다고 해서 음의 cycle을 모두 파악 하는 것은 불가능 하다.
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