#include <iostream>
#include <stack>
#include <string>

using namespace std;

#define bracket (input[index])
string input;
stack<char> s;
int str_length, index = 0;

void bracket_operation();
int operation();

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	bracket_operation();
	return 0;
}

void bracket_operation() {
	cin >> input;
	str_length = input.length();
	int answer = 0;

	while (index < str_length) {
		int arb = operation();
		
		if (!arb) {
			answer = 0;
			break;
		}
		else 
			answer += arb;
	}
	
	cout << answer << "\n";
}

int operation() {
	int arb = 0;
	
	while (1) {
		if (index >= str_length)
			return 0;

		if (bracket == '(' || bracket == '[') {
			s.push(bracket);
			int tmp = bracket == '(' ? 2 : 3;
			index++;
			arb += tmp * operation();
		}
		else {
			if ((bracket == ')' && (s.empty() || s.top() != '(')) || (bracket == ']' && (s.empty() || s.top() != '['))) {
				index++;
				return 0;
			}
			else {
				index++;
				s.pop();
				if (!arb)
					return 1;
				else
					return arb;
			}
		}

		if (s.empty())
			return arb;
	}
}