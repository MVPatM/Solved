/*
1. sweeping algorithm using stack

2. using segment tree
*/

#include <iostream>
#include <algorithm>
#include <utility>
#include <stack>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0)
using ullt = unsigned long long;
using idx = pair<ullt, ullt>; // (min value, sum)

ullt A[100001];
ullt Segment[210000];
int array_length;

void InputInfo();
ullt MakeSegTree(int start = 1, int end = array_length, int idx = 1);
void GetMaxValue();
ullt GetSum(int l, int r, int start = 1, int end = array_length, int idx = 1);
void Sweeping();
ullt UsingDivConq(int start, int end);

int main(void) {
	fastio;
	InputInfo();
	cout << UsingDivConq(1, array_length);

	return 0;
}

void InputInfo() {
	cin >> array_length;
	for (int i = 1; i <= array_length; i++) {
		ullt tmp;
		cin >> tmp;
		A[i] = tmp;
	}
}


ullt MakeSegTree(int start, int end, int idx) {
	if (start == end)
		return Segment[idx] = A[start];

	int mid = (start + end) / 2;

	return Segment[idx] = MakeSegTree(start, mid, 2 * idx) + MakeSegTree(mid + 1, end, 2 * idx + 1);
}

// 배열중에서 이 값이 최솟값이라면.....

// 내가 생각 하지 못한 풀이는 이 범위안에 부분배열의 최댓값이 있는 지를 확인하는 것이다.
void GetMaxValue() {
	int minidx, left_range, right_range;
	ullt ans = 0;

	for (minidx = 1; minidx <= array_length; minidx++) {
		left_range = minidx;
		right_range = minidx;

		// set the left's range
		while (1) {
			if ((left_range - 1) < 1 || (A[left_range - 1] < A[minidx]))
				break;

			left_range--;
		}

		// set the right's range
		while (1) {
			if ((right_range + 1) > array_length || (A[right_range + 1] < A[minidx]))
				break;

			right_range++;
		}

		ans = max(ans, A[minidx] * GetSum(left_range, right_range));
	}
	
	cout << ans;
}

ullt GetSum(int l, int r, int start, int end, int idx) {
	if (r < start || end < l) // 모두 포함x
		return 0;
	if (l <= start && end <= r) // 모두 포함
		return Segment[idx];
	// 일부만 포함되는 경우
	int mid = (start + end) / 2;

	return GetSum(l, r, start, mid, 2 * idx) + GetSum(l, r, mid + 1, end, 2 * idx + 1);
}


void Sweeping() {
	stack<idx> cont;
	ullt input_sum, tmp_cont = 0, ans = 0;
	idx FirstElement;

	cont.push(make_pair(A[1], A[1]));

	/*
	stack에서 먼저 pop할 수 있는 거는 pop해버리고 
	그 다음에 push를 해준다.
	==인 것은 어저피 ==인지 검사를 하는 것이나 stack에서 한 번더 계산을 하느냐의 차이이므로
	time complexity에는 영향을 미치지 않는다. 그러므로 ==인 것도 그냥 push를 해주면 더 깔끔하게 coding이 된다.
	*/
	for (int i = 2; i <= array_length; i++) {
		if (cont.top().first < A[i])
			cont.push(make_pair(A[i], A[i]));
		else if (cont.top().first == A[i])
			cont.top().second += A[i];
		else {
			input_sum = 0;

			while (1) {
				if (cont.empty()) {
					cont.push(make_pair(A[i], input_sum + A[i]));
					break;
				}

				FirstElement = cont.top();
				if (FirstElement.first < A[i]) { // 큰 element는 pop을 하여서 pop할 것이 없는 case를 걸러준다.
					cont.push(make_pair(A[i], input_sum + A[i]));
					break;
				}
				else if (FirstElement.first == A[i]) {
					cont.top().second += (input_sum + A[i]);
					break;
				}

				cont.pop();
				input_sum += FirstElement.second;
				ans = max(ans, FirstElement.first * input_sum);
			}
		}
	}

	for (int i = 1; i <= array_length; i++) {
		input_sum = 0;
		while (!cont.empty() && A[i] < cont.top().first) {
			//pop

			input_sum += cont.top().second;
			ans = max(ans, cont.top().first * input_sum);
			cont.pop();
		}
		// pop이 진행된 이후에 진행한다.
		input_sum += A[i];
		cont.emplace(A[i], input_sum);
	}


	while (!cont.empty()) {
		FirstElement = cont.top();
		FirstElement.second += tmp_cont;
		ans = max(ans, FirstElement.first * FirstElement.second);
		tmp_cont = FirstElement.second;
		cont.pop();
	}

	cout << ans;
}

// 최대 범위를 갖는 영역이 어디에 위치하고 있는지를 파악을 하는 것이다.
ullt UsingDivConq(int start, int end) {
	if (start == end)
		return A[start] * A[start];

	int mid = (start + end) / 2;
	ullt left_max = UsingDivConq(start, mid);
	ullt right_max = UsingDivConq(mid + 1, end);
	ullt ans = max(left_max, right_max);
	
	int left = mid;
	int right = mid + 1;
	ullt minvalue = min(A[left], A[right]);
	ullt sum = A[left] + A[right];
	ans = max(ans, minvalue * sum);

	// while문에서 무조건 모든 조건을 거르는 것이 아니라 일부는 whlie문 안에서도 값을 구별 시킨다.
	// whlie문의 조건 range를 rough하게 함으로써 도 코드를 간단하게 만들었다.
	// left의 element와 right의 element중 큰 값을 추가 시킨다.
	// 둘 중에서 큰 값을 추가시켜주면 쓸모없는 연산을 피하게 해준다.
	while (start < left && right < end) {
		if (right < end && (left == start || A[left - 1] < A[right + 1])) {
			sum += A[++right];
			minvalue = min(minvalue, A[right]);
		}
		else {
			sum += A[--left];
			minvalue = min(minvalue, A[left]);
		}

		ans = max(ans, sum * minvalue);
	}

	return ans;
}

/*
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ar[100001];
int n;

vector<int> seg_idx;

inline int mid(int s, int e) { return s + (e - s) / 2; }

int cmpidx(int a, int b)
{
	if (a == -1) return b;
	if (b == -1) return a;
	if (ar[a] < ar[b]) return a;
	return b;
}

// start에서 end까지 중에서 가장 작은 값의 index를 seg_idx에 저장 시킨다.
int init_min(int node, int start, int end)
{
	if (start == end) return seg_idx[node] = end;
	int m = mid(start, end);
	int l = init_min(node * 2, start, m);
	int r = init_min(node * 2 + 1, m + 1, end);
	return seg_idx[node] = cmpidx(l, r);
}

//
int query_min(int node, int start, int end, int l, int r)
{	
	// 범위 벗어나는 예외 경우 -> 속하는 index가 없는 경우이다.
	if (start > r || end < l) return -1;
	// 찾으려는 범위가 seg_idx에 속해져 있는 범위에 속해져 있는 경우 -> 이 구간에서 최소인 값의 index를 추출해서 비교를 한다.
	if (l <= start && end <= r) return seg_idx[node];
	int m = mid(start, end);
	return cmpidx(
		query_min(node * 2, start, m, l, r),
		query_min(node * 2 + 1, m + 1, end, l, r)
	);
}

// segment tree를 만드는 과정
ll init_sum(vector<ll> &tree, int node, int start, int end)
{
	if (start == end) return tree[node] = ar[end];
	int m = mid(start, end);
	return tree[node] = init_sum(tree, node * 2, start, m) + init_sum(tree, node * 2 + 1, m + 1, end);
}

// segment tree에서 원하는 구간 합을 구하는 함수
ll query_sum(vector<ll> &tree, int node, int start, int end, int l, int r)
{
	if (start > r || l > end) return 0;
	if (l <= start && end <= r) return tree[node];
	int m = mid(start, end);
	return query_sum(tree, node * 2, start, m, l, r) + query_sum(tree, node * 2 + 1, m + 1, end, l, r);
}

// 이 범위에 최댓값을 만족하는 부분배열이 있을 것이다라고 가정을 하고 진행하는 것이다.
ll query(vector<ll> &tree, int start, int end)
{
	if (start == end) return (ll)ar[end] * ar[end];
	int idx = query_min(1, 1, n, start, end);
	// 그러니깐 idx에 대해서는 최대로 구했으므로 idx를 update를 시켜서 그 idx에 대해서 부분배열의 최댓값을 구해서 비교를 진행을 하면된다.
	ll res = ar[idx] * query_sum(tree, 1, 1, n, start, end);
	if (start < idx) res = max(res, query(tree, start, idx - 1));
	if (idx < end) res = max(res, query(tree, idx + 1, end));
	return res;
}

// 어떤 구간에 대해서 recursion function을 이용을 해서 최솟값과 합을 구하고 
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> n;

	seg_idx.resize(n * 4);
	vector<ll> sum_tree(n * 4);

	for (int i = 1; i <= n; ++i)
		cin >> ar[i];
	init_min(1, 1, n);
	init_sum(sum_tree, 1, 1, n);
	cout << query(sum_tree, 1, n);
}*/