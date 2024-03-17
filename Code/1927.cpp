#include <iostream>
#include <queue>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);

int main(void) {
	fastio;

	priority_queue<int, vector<int>, greater<int>> minheap;
	int opnum;

	cin >> opnum;

	while (opnum--) {
		int num;
		cin >> num;

		if (!num) {
			if (minheap.empty())
				cout << "0\n";
			else {
				cout << minheap.top() << "\n";
				minheap.pop();
			}
		}
		else 
			minheap.push(num);


	}

	return 0;
}