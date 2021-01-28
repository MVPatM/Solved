/* 
  ���� ��� ���� ���� ��Ȳ�� ���� ���� �ʴ� ��Ȳ�� ǥ���ϱ� ���ؼ�
   0 �� 1�� �̿��� �ϴ� �ͺ��ٴ� 
   true �� false�� ���ؼ� ǥ���� �ϴ� ���� �� ����.

   string.substr()�Լ��� string�� �Ϻκи� �����ϴ� �Լ��̴�.
   �����Ϸ��� string�� ���� ��ŭ �ð��� �ɸ���.
*/

#include <iostream>
#include <deque>
#include <string>

using namespace std;

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int command_num, isbackward;// dis 0:forward, 1:backward
	bool iserror;
	string answer;
	cin >> command_num;
	
	for (int i = 0; i < command_num; i++) {
		isbackward = 0;
		iserror = false;
		string cmd, arr, tmp = "";
		cin >> cmd;

		deque<int> dq;
		int num;
		cin >> num >> arr;

		// parse the input
		if (num != 0) {
			for (int k = 1; k < arr.length(); k++) {
				if (arr[k] == ',' || arr[k] == ']') {
					dq.push_back(stoi(tmp));
					tmp = "";
				}
				else 
					tmp += arr[k]; // string operation, not int operation
			}
		}

		// execute the command
		for (unsigned int j = 0; j < cmd.length(); j++) {
			if (cmd[j] == 'D') {
				if (dq.empty()) {
					iserror = true;
					break;
				}

				if (isbackward == 0) 
					dq.pop_front();
				else if (isbackward == 1)
					dq.pop_back();
			}
			else if (cmd[j] == 'R')
				isbackward = (isbackward + 1) % 2;
		}

		//output the result
		if (iserror) 
			cout << "error\n";
		else {
			if (dq.empty())
				cout << "[]\n";
			else {
				cout << "[";

				while (1) {
					if (dq.size() == 1) {
						cout << dq.front() << "]\n";
						break;
					}

					if (isbackward == 0) {
						cout << dq.front() << ",";
						dq.pop_front();
					}
					else if (isbackward == 1) {
						cout << dq.back() << ",";
						dq.pop_back();
					}
				}
			}
		}
	}

	return 0;
}