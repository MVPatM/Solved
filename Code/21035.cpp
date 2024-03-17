/*
O(M*N + Q(M+N))
����) row�� ũ��� ������ �����̰� column�� ũ��� ������ �����̴�.
      �������� array�� index�� 1���� ���۵ȴٴ� ���� ��������.
*/
#include <iostream>
#include <cstring>
#include <climits>
#include <algorithm>

using namespace std;

int row, column;
int matrix[51][51] = { 0 };

void Do_Operation();
void InputToMatrix();
void PerformQuery();
void OutputThreeNumber();

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	Do_Operation();

	return 0;
}

void Do_Operation() {
	cin >> row >> column;

	InputToMatrix();
	PerformQuery();
	OutputThreeNumber();
}

void InputToMatrix() {
	int val;

	for (int i = 1; i <= row; i++) {
		for (int j = 1; j <= column; j++) {
			cin >> val;
			matrix[i][j] = val;
		}
	}
}

void PerformQuery() {
	string oper;
	int pos, v, query;

	cin >> query;

	for (int i = 0; i < query; i++) {
		cin >> oper >> pos >> v;

		if (oper == "row") { // column index change
			for (int j = 1; j <= column; j++) 
				matrix[pos][j] += v;
		}
		else { // row index change
			for (int j = 1; j <= row; j++)
				matrix[j][pos] += v;
		}
	}
}

void OutputThreeNumber() {
	int sum = 0, matmin = INT_MAX, matmax = INT_MIN;

	for (int i = 1; i <= row; i++) {
		for (int j = 1; j <= column; j++) {
			sum += matrix[i][j];
			matmin = min(matmin, matrix[i][j]);
			matmax = max(matmax, matrix[i][j]);
		}
	}

	cout << sum << " " << matmin << " " << matmax;
}