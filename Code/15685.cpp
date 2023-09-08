#include <iostream>
#include <utility>
#include <vector>
#include <cmath>

using namespace std;

#define fastio ios_base::sync_with_stdio(0), cin.tie(0);
using cord = pair<int, int>;

vector<cord> house;
vector<cord> chicken_place;
int dp[100][13]; // (��, ġŲ��), ������ �� <-> ġŲ�� ���� ġŲ �Ÿ��� ����ؼ� dp�� �ִ´�.
int dp2[100][14]; // recursive function���� ����� �Ǵ� dp
int city_size, house_num, chicken_place_num, chicken_place_Max, MinDis = 250000; // �ʱ� ������ ū ���� �־�� �Ѵ�

void InputInfo();
void CalDis();
void CalMin(int selected_num, int recur_num);
void Solve();

int main(void){
    fastio;
    Solve();

    return 0;
}

void InputInfo() {
    cin >> city_size >> chicken_place_Max;
 
    for (int i = 0; i < city_size; i++){
        for (int j = 0; j < city_size; j++){
            int input;
            cin >> input;

            if (input == 1) // ��
                house.emplace_back(i,j);
            else if (input == 2) //ġŲ��
                chicken_place.emplace_back(i, j);
        }
    }

    chicken_place_num = chicken_place.size();
    house_num = house.size();

    for (int i = 0; i < house_num; i++)
        dp2[i][0] = 100;
}

void CalDis(){
    for (int i = 0; i < house_num; i++){
        for (int j = 0; j < chicken_place_num; j++)
            dp[i][j] = abs(house[i].first - chicken_place[j].first) + abs(house[i].second - chicken_place[j].second);
    }
}

void CalMin(int selected_num, int recur_num){
    if (chicken_place_num - selected_num - 1 < chicken_place_Max - recur_num) // �����ִ� recurȽ�� ���� �����ִ� ġŲ���� ������ ���
        return;

    for (int i = 0; i < house_num; i++) // update
        dp2[i][recur_num] = min(dp2[i][recur_num - 1], dp[i][selected_num]);

    if (recur_num == chicken_place_Max){
        int arb = 0;

        for (int i = 0; i < house_num; i++)
            arb += dp2[i][recur_num];

        MinDis = min(MinDis, arb);
        return;
    }
    else {
        for (int i = selected_num + 1; i < chicken_place_num; i++)
            CalMin(i, recur_num + 1);
    }
}

void Solve() {
    InputInfo();
    CalDis();

    for(int i = 0; i < chicken_place_num; i++)
        CalMin(i, 1);

    cout << MinDis;
}