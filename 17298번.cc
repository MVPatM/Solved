/*
 array 안에 있는 값을 비교를 할 때 그 값을 직접 stack에 넣는 것이 아니라 
 해당 array의 index를 stack에 넣은 다음에 index를 통해서 값을 비교한다.
 원하는 값을 직접 비교를 할 것인지 아니면 다른 우회적인 방법을 통해서 비교를 할 것인지 잘 선택을 해야 한다.
*/

#include <iostream>
#include <vector>
#include <stack>
#include <utility>

using namespace std;

int main(void) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
	int itr;
	cin >> itr;
	stack<int> sequence;
	vector<int> numbers;

	for (int i = 0; i < itr; i++) {
		int num;
		cin >> num;
		numbers.push_back(pair<int, int>(num, i));
	}

	vector<int> answer(numbers.size(), -1);

	for (int i = 0; i < itr; i++) {
		if (sequence.empty())
			sequence.push(i);
		else {
			while (!sequence.empty() && (numbers[sequence.top()] < numbers[i])) {
				ans[sequence.top()] = numbers[i];
				sequence.pop();
			}

			sequence.push(i);
		}
	}

	for (int i = 0; i < numbers.size(); i++) cout << numbers[i].first << " ";

	return 0;
}