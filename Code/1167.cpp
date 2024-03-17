/*
tree�� root node�� �������� �ʾ��� �� � vertex�̵� ���� user������� root node�� �����ϸ� 
������ node�� root�� �ϴ� tree�� ����� ����.
Ʈ���� ����(2���� node���̿� �����ϴ� �ִ� �Ÿ�)�� 2���� dfs�� ������ �ϸ� �� �� �ִ�. 
�� �̻��� dfs�� ������ �ϴ��� �ִ� �Ÿ��� ������ �ʰ� �״�� �̴�.


*/
#include <iostream>
#include <vector>
#include <utility>
#include <cstring>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);

int vertex_num, max_dist, max_node, dist = 0;
vector<vector<pair<int, int>>> tree; // (node_num, cost)
bool isvisited[100001];

void InputInfo();
void DFS(int n, int d);
int GetTreeDiameter();

int main(void) {
	fastio;
	InputInfo();
	cout << GetTreeDiameter();

	return 0;
}

void InputInfo() {
	cin >> vertex_num;
	vector<pair<int, int>> tmp;
	int node, cost, cur;

	for (int i = 0; i <= vertex_num; i++)
		tree.push_back(tmp);

	for (int i = 0; i < vertex_num; i++) {
		cin >> cur;

		while (1) {
			cin >> node;

			if (node == -1)
				break;

			cin >> cost;
			tree[cur].emplace_back(node, cost);
		}
	}
}

void DFS(int n, int d) {
	isvisited[n] = true;
	dist += d;

	for (int i = 0; i < tree[n].size(); i++) {
		int next_d = tree[n][i].second;
		int next_n = tree[n][i].first;
		if (isvisited[next_n]) {
			if (dist > max_dist) {
				max_dist = dist;
				max_node = n;
			}
		}
		else
			DFS(next_n, next_d);
	}

	dist -= d;
}

int GetTreeDiameter() {
	DFS(1, 0);
	memset(isvisited, 0, sizeof(isvisited));
	DFS(max_node, 0);

	return max_dist;
}