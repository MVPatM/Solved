#include <iostream>
#include <queue>

using namespace std;

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int itr;
	cin >> itr;
	queue<int> cards;

	for (int i = 1; i <= itr; i++) {
		cards.push(i);
	}

	while (cards.size() != 1) {
		cards.pop(); //throwing
		cards.push(cards.front()); //exchanging the position
		cards.pop();
	}

	cout << cards.front() << "\n";
	
	return 0;
}