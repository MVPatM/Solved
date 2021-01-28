#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int main(void) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
	bool ispossible = true;
	int max_num, ascending_power = 1;
	stack<int> sequence;
	vector<char> output;
	cin >> max_num;

	for (int i = 0; i < max_num; i++) {
		int num;
		cin >> num;

		if (!sequence.empty()) {
			if (num < sequence.top())
				ispossible = false;
		}

		while (sequence.empty() || (num > sequence.top())) {
			sequence.push(ascending_power++);
			output.push_back('+');
		}
		
		if (num == sequence.top()) {
			sequence.pop();
			output.push_back('-');
		}
	}

	if (ispossible) {
		for (int i = 0; i < output.size(); i++) {
			cout << output[i] << "\n";
		}
	}
	else
		cout << "NO" << "\n";

	return 0;
}