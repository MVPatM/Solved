#include <iostream>
#include <queue>
#include <string>

using namespace std;

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int order_num;
	cin >> order_num;
	queue<int> q;

	for (int i = 0; i < order_num; i++) {
		string order;
		cin >> order;

		if (order == "push") {
			int num;
			cin >> num;
			q.push(num);
		}
		else if (order == "pop") {
			if (q.empty())
				cout << "-1\n";
			else {
				cout << q.front() << "\n";
				q.pop();
			}
		}
		else if (order == "size")
			cout << q.size() << "\n";
		else if (order == "empty")
			cout << q.empty() << "\n";
		else if (order == "front") {
			if (q.empty())
				cout << "-1" << "\n";
			else
				cout << q.front() << "\n";
		}
		else if (order == "back") {
			if (q.empty())
				cout << "-1" << "\n";
			else
				cout << q.back() << "\n";
		}
	}

	return 0;
}