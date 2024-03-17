/*
	ù �õ��� ������: ���� ������ �ִ� ������ �� �ٸ� ���� input�� �޾Ƽ� ������ �� ������ ���̸� �ߺ��ؼ� ����ϴ� ������ �߻��Ͽ���.

	ver1: input�� �����´�� ���ǿ� ���� data�� �з��� ���ش�. �׷��� �ϴ� group���� ������ְ� �� ���� �������� ���ܸ� �ذ��Ѵ�
	      �׸��� group���� ���̸� ���ؼ� �� ���ش�. ���� ����Ǵ� ���� group���� ���Ѵ�.
    ver2: �ϴ� input�� ������ data�� ������ �ϰ� sort�� ���־ ������ �����ش�. �׸��� ���� �������� �κ��� �����ָ鼭 ���̸� ���Ѵ�.

	sorting�� ������ ��� ���� ������� ������ ���־ ����� ����� ���� �ٿ��ش�.
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
	// �������� �κ��� ���� �� �ߺ��ؼ� ���̸� ����ϴ� ��츦 �����ش�.
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