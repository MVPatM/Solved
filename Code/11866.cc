#include <iostream>
#include <queue>

using namespace std;

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int num, k, count = 1;
	cin >> num >> k;
	queue<int> sequence;

	cout << "<";

	for (int i = 1; i <= num; i++) sequence.push(i);
	
	while (!sequence.empty()) {
		if (count % k == 0) {
			cout << sequence.front();
			sequence.pop();

			if (!sequence.empty())
				cout << ", ";
		}
		else {
			sequence.push(sequence.front());
			sequence.pop();
		}

		count++;
	}

	cout << ">";

	return 0;
}