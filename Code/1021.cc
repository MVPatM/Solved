#include <iostream>
#include <deque>
#include <vector>

using namespace std;

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int num_all, num_out, count = 0;
	cin >> num_all >> num_out;

	deque<int> dq;
	vector<pair<int, int>> v;

	for (int i = 1; i <= num_all; i++) dq.push_back(i); // put in deque

	for (int i = 0; i < num_out; i++) { // put in the vector
		int num;
		cin >> num;

		v.push_back(make_pair(num, num)); // (value, position in deque)
	}

	for (int i = 0; i < num_out; i++) {
		int itr;

		if (num_all < 2 * v[i].second - 2) { 
			// 3rd operation
			itr = num_all - v[i].second + 1;
			for (int j = 0; j < itr; j++) { // deque operation
				dq.push_front(dq.back());
				dq.pop_back();
				count += 1;
			}

			for (int k = i; k < num_out; k++) { // position change in deque
				if (v[k].second < v[i].second)
					v[k].second = v[k].second + num_all - v[i].second;
				else if (v[k].second > v[i].second)
					v[k].second -= v[i].second;
			}
		}
		else { 
			// 2nd operation
			itr = v[i].second - 1;
			for (int j = 0; j < itr; j++) { //deque operation
				dq.push_back(dq.front());
				dq.pop_front();
				count += 1;
			}

			for (int k = i; k < num_out; k++) { // position change in deque
				if (v[k].second > v[i].second) // if position is same, just defy
					v[k].second -= v[i].second;
				else if (v[k].second < v[i].second)
					v[k].second = num_all - v[i].second + v[k].second;
			}
		}

		dq.pop_front(); // 1st operation 
		num_all -= 1;
	}

	cout << count << "\n";

	return 0;
}