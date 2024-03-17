#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;
using cord = pair<int, int>;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);

int slate_len;
vector<cord> jewel;
vector<cord> impurity;

void InputInfo();
void GetResult();
int recur(int square_cord[], bool iscolumn); // square_cord: {row1, row2, col1, col2} 
                                            // cur_dir = 0(false) : row, cut_dir = 1(true) : column

int main(void){
    fastio;
    InputInfo();
    GetResult();

    return 0;
}

void InputInfo(){
    int value;
    cin >> slate_len;

    for (int r = 0; r < slate_len; r++){
        for (int c = 0; c < slate_len; c++){
            cin >> value;
            if (value == 1) // impurity
                impurity.emplace_back(r, c);
            else if (value == 2) // jewel
                jewel.emplace_back(r, c);
        }
    }
}

void GetResult() {
    int square_cord[4] = {0, slate_len - 1, 0, slate_len - 1};
    int row = recur(square_cord, 0);
    int col = recur(square_cord, 1);
    int ret = row + col;

    if (ret == 0)
        cout << "-1";
    else
        cout << ret;
}

int recur(int square_cord[], bool iscolumn) {
    if ((square_cord[0] > square_cord[1]) || (square_cord[2] > square_cord[3]))
        return 1;

    vector<cord> included_jewel;
    vector<int> included_impurity;
    bool isin[20];
    fill_n(isin, 20, 0);
    int ret = 0;
    
    for (int i = 0; i < jewel.size(); i++){
        int jewel_row = jewel[i].first;
        int jewel_col = jewel[i].second;

        if ((jewel_row >= square_cord[0] && jewel_row <= square_cord[1]) && 
                    (jewel_col >= square_cord[2] && jewel_col <= square_cord[3])){
            included_jewel.emplace_back(jewel_row, jewel_col);

            if (iscolumn)
                isin[jewel_col] = true;
            else
                isin[jewel_row] = true;
        }
    }

    for (int i = 0; i < impurity.size(); i++){
        int impurity_row = impurity[i].first;
        int impurity_col = impurity[i].second;
        if ((impurity_row >= square_cord[0] && impurity_row <= square_cord[1]) && 
                (impurity_col >= square_cord[2] && impurity_col <= square_cord[3])){
            if (iscolumn)
                included_impurity.emplace_back(impurity_col);
            else 
                included_impurity.emplace_back(impurity_row);
        }
    }

    sort(included_impurity.begin(), included_impurity.end());
    included_impurity.erase(unique(included_impurity.begin(), included_impurity.end()), included_impurity.end());

    if ((included_jewel.size() == 1) && (included_impurity.size() == 0))
        return 1;

    if ((included_jewel.size() >= 2 && included_impurity.size() == 0) || (included_jewel.size() == 0))
        return 0;

    for (int i = 0; i < included_impurity.size(); i++){
        int leftside, rightside;
        if (isin[included_impurity[i]] == true)
            continue;
        
        if (iscolumn){
            int left_cord[] = {square_cord[0], square_cord[1], square_cord[2], included_impurity[i] - 1};
            leftside = recur(left_cord, !iscolumn);
            int right_cord[] = {square_cord[0], square_cord[1], included_impurity[i] + 1, square_cord[3]};
            rightside = recur(right_cord, !iscolumn);
        }
        else {
            int left_cord[] = {square_cord[0], included_impurity[i] - 1, square_cord[2], square_cord[3]};
            leftside = recur(left_cord, !iscolumn);
            int right_cord[] = {included_impurity[i] + 1, square_cord[1], square_cord[2], square_cord[3]};
            rightside = recur(right_cord, !iscolumn);
        }

        ret += (leftside * rightside);
    }

    return ret;
}