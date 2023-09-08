/*
   <char연산>
   1. char c = 'z' - 'a' 
     이 경우에는 연산의 결과가 char형을 저장 되어 진다.
   
   2. int n = 'z' - 'a'
      이 경우에는 ascii code에서의 값 차이를 int형 값으로 저장을 한다.

    class에서 객체 배열을 만들 때에는 생성자를 통해서 객체 배열을 초기화 시켜줘야 한다.
*/

#include <iostream>

using namespace std;

void play_traversal();

class tree_node {
private:
	int left, right;
	char self;
public:
	tree_node():left(-1), right(-1), self('.') {}
	tree_node(char c, int n1, int n2);
	int access_left() { return left; }
	int access_right() { return right; }
	char access_self() { return self; }
};

class traversal {
private:
	tree_node* nodes;
public:
	traversal();
	void preorder(tree_node n);
	void inorder(tree_node n);
	void postorder(tree_node n);
	tree_node firstnode();
	~traversal();
};

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	play_traversal();

	return 0;
}

tree_node::tree_node(char c, int n1, int n2) {
	left = n1;
	right = n2;
	self = c;
}

traversal::traversal() {
	int node_num;
	cin >> node_num;

	nodes = new tree_node[node_num];

	for (int i = 0; i < node_num; i++) {
		char p, c1, c2;
		cin >> p >> c1 >> c2;
		int n, n1, n2;
		n = p - 'A';
		
		if (c1 == '.')
			n1 = -1;
		else
			n1 = c1 - 'A';

		if (c2 == '.')
			n2 = -1;
		else
			n2 = c2 - 'A';

		nodes[n] = tree_node(p, n1, n2);
	}
}

void traversal::preorder(tree_node n) {
	cout << n.access_self();
	if (n.access_left() != -1)
		preorder(nodes[n.access_left()]);
	if (n.access_right() != -1)
		preorder(nodes[n.access_right()]);
}

void traversal::inorder(tree_node n) {
	if (n.access_left() != -1)
		inorder(nodes[n.access_left()]);
	cout << n.access_self();
	if (n.access_right() != -1)
		inorder(nodes[n.access_right()]);
}

void traversal::postorder(tree_node n) {
	if (n.access_left() != -1)
		postorder(nodes[n.access_left()]);
	if (n.access_right() != -1)
		postorder(nodes[n.access_right()]);
	cout << n.access_self();
}

tree_node traversal::firstnode() {
	return nodes[0];
}

traversal::~traversal() {
	delete nodes;
}

void play_traversal() {
	traversal tr = traversal();
	tree_node first = tr.firstnode();
	tr.preorder(first);
	cout << "\n";
	tr.inorder(first);
	cout << "\n";
	tr.postorder(first);
	cout << "\n";
}