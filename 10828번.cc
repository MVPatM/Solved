#include<iostream>
#include<stack>
#include<string>

using namespace std;

int main(void){
    int itr;
    cin >> itr;
    string str;
    stack<int> s;
    
    for (int i = 0;i < itr; i++){
        cin >> str;
        if (str == "push"){
            int n;
            cin >> n;
            s.push(n);
        }else if (str == "pop"){
            if(!s.empty()){
                cout << s.top() << endl;
                s.pop();
            }else {
                cout << -1 << endl;
            }
        }else if (str == "size"){
            cout << s.size() << endl;
        }else if (str == "top"){
            if(!s.empty()){
                cout << s.top() << endl;
            }else {
                cout << -1 << endl;
            }
        }else if (str == "empty"){
            cout << s.empty() << endl;
        }
    }
    
    return 0;
}