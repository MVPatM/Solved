#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);

// 건물은 1번부터 시작한다.
bool isvisited[1001];
int constructTime[1001]; // 건물 하나를 건설을 하는데 걸리는 시간
int totalTime[1001];
int inDegree[1001];
int buildingNum, rules, target;
vector<vector<int>> Game(1001);

void Init();
void InputInfo();
void Solve();

int main(void) {
	fastio;
	Solve();

	return 0;
}

void InputInfo() {
	vector<int> tmp;
	cin >> buildingNum >> rules;


	for (int i = 1; i <= buildingNum; i++) 
		cin >> constructTime[i];

	for (int i = 0; i <= buildingNum; i++)
		Game.push_back(tmp);


	for (int i = 0; i < rules; i++) {
		int to, from;
		cin >> from >> to;
		Game[from].push_back(to);
		inDegree[to]++;
	}

	cin >> target;
}

void Init() {
	memset(totalTime, 0, sizeof(int) * (buildingNum + 1));
	memset(isvisited, 0, sizeof(bool) * (buildingNum + 1));
	memset(inDegree, 0, sizeof(int) * (buildingNum + 1));
	Game.clear(); // 미리 선언할 때 vector의 열을 확장해 놓은 것도 초기화 시켜버린다.
}

void Solve() {
	int testcase;
	cin >> testcase;

	for (int i = 0; i < testcase; i++) {
		Init();
		InputInfo();

		// find the indgree value is zero
		queue<int> zero;
		for (int i = 1; i <= buildingNum; i++) {
			if (!inDegree[i])
				zero.push(i);
		}

		while (!zero.empty()) { // 마지막 건물까지 갈 수있는 route가 무조건 존재하기 때문에 이렇게 조건을 만들어도 상관이 없다.
			int cur = zero.front();
			zero.pop();
			totalTime[cur] += constructTime[cur];
			isvisited[cur] = true;

			for (int i = 0; i < Game[cur].size(); i++) {
				int next = Game[cur][i];
				inDegree[next]--;

				if (!inDegree[next])
					zero.push(next);
				totalTime[next] = max(totalTime[next], totalTime[cur]);
			}
		}

		cout << totalTime[target] << "\n";
	}
}