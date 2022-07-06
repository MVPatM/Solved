#include <iostream>
#include <vector>
#include <utility>
#include <cstring>
#include <stack>
#include <algorithm>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);
using pii = pair<int, int>;

int N, M, MinArea = 100, wallnum = 0;
int lab[9][9];
int dr[4] = {1,0,-1,0};
int dc[4] = {0,1,0,-1};
bool isvisited[9][9];
vector<pii> virus;
int num = 0;

void InputInfo();
void calMinArea();
void GetWall(int cur, pii bef);
void Solve();

int main(void){
    fastio;
    Solve();

    return 0;
}

void InputInfo() {
    cin >> N >> M;

    for (int i = 1; i <= N; i++){
        for (int j = 1; j <= M; j++) {
            int var;
            cin >> var;
            lab[i][j] = var;
            if (var == 2)
                virus.emplace_back(i,j);
            else if (var == 1)
                wallnum++;
        }
    }
}

void calMinArea(){
    int area = 0;
    
    // memset을 통한 2차원 배열 초기화
    for (int i = 1; i <= N; i++)
        memset(isvisited[i], false, sizeof(isvisited[i]));
    
    for (int i = 0; i < virus.size(); i++){
        stack<pii> stk;
        stk.push(virus[i]);
        isvisited[virus[i].first][virus[i].second] = true;
        area++;

        while (!stk.empty()){
            pii start = stk.top();
            stk.pop();

            for (int k = 0; k < 4; k++){
                int nextr = start.first + dr[k];
                int nextc = start.second + dc[k];
                if ((nextr > 0 && nextr <= N && nextc > 0 && nextc <= M) &&
                            lab[nextr][nextc] == 0 && isvisited[nextr][nextc] == false){
                    isvisited[nextr][nextc] = true;
                    area++;
                    stk.emplace(nextr, nextc);
                }
            }
        }
    }
    
    MinArea = min(MinArea, area);
}

// 3개의 벽을 추가하는 과정에서 몇가지의 경우를 생략하는 실수를 하였다.
void GetWall(int cur, pii bef){
    if (cur == 3){
        calMinArea();
        return;
    }
   
    for (int j = bef.second; j <= M; j++){
        if (lab[bef.first][j] == 0){
            lab[bef.first][j] = 1;
            GetWall(cur + 1, make_pair(bef.first,j));
            lab[bef.first][j] = 0;
        }
    }

    for (int i = bef.first + 1; i <= N; i++){
        for (int j = 1; j <= M; j++){
            if (lab[i][j] == 0){
                lab[i][j] = 1;
                GetWall(cur + 1, make_pair(i,j));
                lab[i][j] = 0;
            }
        }
    }
}

void Solve() {
    InputInfo();
    GetWall(0, make_pair(1, 1));
    cout << N * M - MinArea - (wallnum + 3);
}