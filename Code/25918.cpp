#include <iostream>
#include <algorithm>
#include <cstring>
#include <stack>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);

int max_day = 1;
int str_len;
string str;

void InputInfo();
void Solve();

int main(void){
    fastio;
    InputInfo();
    Solve();

    return 0;
}

// get the data
void InputInfo() {
    cin >> str_len;
    cin >> str;
}

void Solve() {
    stack<char> stk;
    int now_day = 0; // represent stack's size

    // using stack, get the answer
    for (int i = 0; i < str_len; i++){
        char ch = str[i];

        // stack is empty or parenthesis is same
        if (stk.empty() || ch == stk.top()){ // ch == stk.top() 의 조건문은 stack이 empty가 아닐 때를 전제하고 이루어 지는 것이다. -> or문의 특성
            stk.push(ch);
            now_day++;
            max_day = max(now_day, max_day);
        }
        else {
            stk.pop();
            now_day--;
        }
    }

    if (stk.empty())
        cout << max_day;
    else
        cout << "-1";
}