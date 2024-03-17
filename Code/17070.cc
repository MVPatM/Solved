#include <iostream>
#include <utility>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);
using pii = pair<int, int>;

int len;
bool map[17][17];

void InputInfo();
bool CheckOutOfBound(int dir, pii cord);
bool CanMove(int dir, pii cord);
void Solve();

int main(void){
    fastio;
    InputInfo();
    Solve();

    return 0;
}

void InputInfo(){
    cin >> len;
    for (int i = 1; i <= len; i++){
        for (int j = 1; j <= len; j++)
            cin >> map[i][j];
    }
}

// 0: 가로, 1: 대각선, 2:세로
bool CheckOutOfBound(int dir, pii cord){
    if (dir == 0) 
        return len >= (cord.second + 1);
    else if (dir == 1)
        return (len >= (cord.first + 1)) && (len >= (cord.second + 1));
    else if (dir == 2)
        return len >= (cord.first + 1);
    
}

// 0: 가로, 1: 대각선, 2:세로
bool CanMove(int dir, pii cord){
    if (CheckOutOfBound(dir, cord))
        return false;

    if (dir == 0)
        return !map[cord.first][cord.second + 1];
    else if (dir == 1)
        return !map[cord.first][cord.second + 1]
            && !map[cord.first + 1][cord.second] 
            && !map[cord.first + 1][cord.second + 1]; 
    else if (dir == 2)
        return !map[cord.first + 1][cord.second];
}

void Solve() {

    
}