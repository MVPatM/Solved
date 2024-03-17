/*
	첫 시도의 문제점: 따로 떨어져 있던 선들이 또 다른 선의 input을 받아서 합쳐질 때 선들의 길이를 중복해서 계산하는 문제가 발생하였다.

	ver1: input이 들어오는대로 조건에 따라서 data를 분류를 해준다. 그래서 일단 group들을 만들어주고 그 다음 겹쳐지는 예외를 해결한다
	      그리고 group마다 길이를 구해서 더 해준다. 서로 연결되는 것을 group으로 정한다.
    ver2: 일단 input이 들어오면 data를 저장을 하고 sort를 해주어서 정렬을 시켜준다. 그리고 나서 겹쳐지는 부분을 없애주면서 길이를 구한다.

	sorting의 장점은 어느 정도 순서대로 정렬을 해주어서 고려할 경우의 수를 줄여준다.
*/
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define fastio ios_base::sync_with_stdio(0), cin.tie(0);
using Pos = pair<int, int>;
vector<Pos> container;

// ver1
void DrawLine();
int GetLength();

// ver2
void Drawing();

int main(void) {
	fastio;
	Drawing();

	return 0;
}

void DrawLine() {
	int line;
	cin >> line;

	for (int i = 0; i < line; i++) {
		bool isadded = true;
		int x, y;
		cin >> x >> y;

		for (int j = 0; j < container.size(); j++) {
			if ((container[j].first <= x && x <= container[j].second ) ||
				(container[j].first <= y && y <= container[j].second)) {
				isadded = false;
				container[j].first = min(x, container[j].first);
				container[j].second = max(y, container[j].second);
				break;
			}
		}

		if (isadded)
			container.emplace_back(x, y);
	}

	cout << GetLength() << "\n";
}

int GetLength() {
	int l = 0;
	// vector sort
	sort(container.begin(), container.end());
	
	// Exception Handling 
	// 겹쳐지는 부분이 있을 때 중복해서 길이를 계산하는 경우를 막아준다.
	for (int i = 1; i < container.size(); i++) {
		if (container[i - 1].second > container[i].second) {
			container[i].second = container[i - 1].second;
			container[i - 1].second = container[i].first;
		}
		else if (container[i - 1].second > container[i].first)
			container[i - 1].second = container[i].first;
	}

	// calculate the length
	for (int i = 0; i < container.size(); i++) 
		l += (container[i].second - container[i].first);
	
	return l;
}

void Drawing() {
	int line, l = 0;
	cin >> line;

	vector<Pos> paper;

	for (int i = 0; i < line; i++) {
		int x, y;
		cin >> x >> y;
		paper.emplace_back(x, y);
	}

	sort(paper.begin(), paper.end());

	for (int i = 0; i < paper.size() - 1; i++) {
		if (paper[i + 1].first <= paper[i].second) {
			l += (paper[i + 1].first - paper[i].first);
			paper[i + 1].second = max(paper[i].second, paper[i + 1].second);
		}
		else if (paper[i+1].first > paper[i].second)
			l += (paper[i].second - paper[i].first);
	}

	l += (paper[paper.size() - 1].second - paper[paper.size() - 1].first);
	cout << l << "\n";
}