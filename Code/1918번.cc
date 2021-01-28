/* 
   String을 처음부터 끝까지 각각의 index를 사용해야 할 때는 string.size() 나 string.length() 함수를 사용을 하는 것이 좋다.
   String 연산을 할 때 a = a + b의 연산을 사용하면 느리다.
   string.append()함수느 +=는 연산자를 이용해서 string연산을 하면 속도가 빠르다. (in c++)
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