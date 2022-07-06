/*
 array �ȿ� �ִ� ���� �񱳸� �� �� �� ���� ���� stack�� �ִ� ���� �ƴ϶� 
 �ش� array�� index�� stack�� ���� ������ index�� ���ؼ� ���� ���Ѵ�.
 ���ϴ� ���� ���� �񱳸� �� ������ �ƴϸ� �ٸ� ��ȸ���� ����� ���ؼ� �񱳸� �� ������ �� ������ �ؾ� �Ѵ�.
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
	vector<pair<int, int>> numbers;

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
				//answer[sequence.top()] = numbers[i];
				sequence.pop();
			}

			sequence.push(i);
		}
	}

	for (int i = 0; i < numbers.size(); i++) cout << numbers[i].first << " ";

	return 0;
}