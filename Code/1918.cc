/* 
   String�� ó������ ������ ������ index�� ����ؾ� �� ���� string.size() �� string.length() �Լ��� ����� �ϴ� ���� ����.
   String ������ �� �� a = a + b�� ������ ����ϸ� ������.
   string.append()�Լ��� +=�� �����ڸ� �̿��ؼ� string������ �ϸ� �ӵ��� ������. (in c++)
*/

#include <iostream>
#include <stack>
#include <string>

using namespace std;

int priority(char ch);

int main(void) {
	stack<char> operand;
	string input, output = "";
	cin >> input;

	for (unsigned int i = 0; i < input.size(); i++) {
		if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/') {
			while (!operand.empty() && (priority(operand.top()) >= priority(input[i]))) {
				output += operand.top();
				operand.pop();
			}
			operand.push(input[i]);
		}
		else if (input[i] == '(')
			operand.push(input[i]);
		else if (input[i] == ')') {
			while (operand.top() != '(') {
				output += operand.top();
				operand.pop();
			}
			operand.pop(); // '(' is popped
		}
		else
			output += input[i];
	}

	while (!operand.empty()) {
		output += operand.top();
		operand.pop();
	}

	for (unsigned int i = 0; i < output.length(); i++) cout << output[i];

	cout << "\n";

	return 0;
}

int priority(char ch) {
	if (ch == '(')
		return 0;
	else if (ch == '+' || ch == '-')
		return 1;
	else
		return 2;
}