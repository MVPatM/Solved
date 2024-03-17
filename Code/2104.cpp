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

// �迭�߿��� �� ���� �ּڰ��̶��.....

// ���� ���� ���� ���� Ǯ�̴� �� �����ȿ� �κй迭�� �ִ��� �ִ� ���� Ȯ���ϴ� ���̴�.
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
	if (r < start || end < l) // ��� ����x
		return 0;
	if (l <= start && end <= r) // ��� ����
		return Segment[idx];
	// �Ϻθ� ���ԵǴ� ���
	int mid = (start + end) / 2;

	return GetSum(l, r, start, mid, 2 * idx) + GetSum(l, r, mid + 1, end, 2 * idx + 1);
}


void Sweeping() {
	stack<idx> cont;
	ullt input_sum, tmp_cont = 0, ans = 0;
	idx FirstElement;

	cont.push(make_pair(A[1], A[1]));

	/*
	stack���� ���� pop�� �� �ִ� �Ŵ� pop�ع����� 
	�� ������ push�� ���ش�.
	==�� ���� ������ ==���� �˻縦 �ϴ� ���̳� stack���� �� ���� ����� �ϴ����� �����̹Ƿ�
	time complexity���� ������ ��ġ�� �ʴ´�. �׷��Ƿ� ==�� �͵� �׳� push�� ���ָ� �� ����ϰ� coding�� �ȴ�.
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
				if (FirstElement.first < A[i]) { // ū element�� pop�� �Ͽ��� pop�� ���� ���� case�� �ɷ��ش�.
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
		// pop�� ����� ���Ŀ� �����Ѵ�.
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

// �ִ� ������ ���� ������ ��� ��ġ�ϰ� �ִ����� �ľ��� �ϴ� ���̴�.
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

	// while������ ������ ��� ������ �Ÿ��� ���� �ƴ϶� �Ϻδ� whlie�� �ȿ����� ���� ���� ��Ų��.
	// whlie���� ���� range�� rough�ϰ� �����ν� �� �ڵ带 �����ϰ� �������.
	// left�� element�� right�� element�� ū ���� �߰� ��Ų��.
	// �� �߿��� ū ���� �߰������ָ� ������� ������ ���ϰ� ���ش�.
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

// start���� end���� �߿��� ���� ���� ���� index�� seg_idx�� ���� ��Ų��.
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
	// ���� ����� ���� ��� -> ���ϴ� index�� ���� ����̴�.
	if (start > r || end < l) return -1;
	// ã������ ������ seg_idx�� ������ �ִ� ������ ������ �ִ� ��� -> �� �������� �ּ��� ���� index�� �����ؼ� �񱳸� �Ѵ�.
	if (l <= start && end <= r) return seg_idx[node];
	int m = mid(start, end);
	return cmpidx(
		query_min(node * 2, start, m, l, r),
		query_min(node * 2 + 1, m + 1, end, l, r)
	);
}

// segment tree�� ����� ����
ll init_sum(vector<ll> &tree, int node, int start, int end)
{
	if (start == end) return tree[node] = ar[end];
	int m = mid(start, end);
	return tree[node] = init_sum(tree, node * 2, start, m) + init_sum(tree, node * 2 + 1, m + 1, end);
}

// segment tree���� ���ϴ� ���� ���� ���ϴ� �Լ�
ll query_sum(vector<ll> &tree, int node, int start, int end, int l, int r)
{
	if (start > r || l > end) return 0;
	if (l <= start && end <= r) return tree[node];
	int m = mid(start, end);
	return query_sum(tree, node * 2, start, m, l, r) + query_sum(tree, node * 2 + 1, m + 1, end, l, r);
}

// �� ������ �ִ��� �����ϴ� �κй迭�� ���� ���̴ٶ�� ������ �ϰ� �����ϴ� ���̴�.
ll query(vector<ll> &tree, int start, int end)
{
	if (start == end) return (ll)ar[end] * ar[end];
	int idx = query_min(1, 1, n, start, end);
	// �׷��ϱ� idx�� ���ؼ��� �ִ�� �������Ƿ� idx�� update�� ���Ѽ� �� idx�� ���ؼ� �κй迭�� �ִ��� ���ؼ� �񱳸� ������ �ϸ�ȴ�.
	ll res = ar[idx] * query_sum(tree, 1, 1, n, start, end);
	if (start < idx) res = max(res, query(tree, start, idx - 1));
	if (idx < end) res = max(res, query(tree, idx + 1, end));
	return res;
}

// � ������ ���ؼ� recursion function�� �̿��� �ؼ� �ּڰ��� ���� ���ϰ� 
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