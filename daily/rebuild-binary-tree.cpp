#include <cstdio>
#include <iostream>

using namespace std;

struct node {
	int value;
	node* left;
	node* right;
};

int f[100], m[100]; // `f` means first root, `m` means middle root

node* rebuild(int l, int r, int pos) {
	/*
	 * `l`: the left bound of array `m`
	 * `r`: the right bound of array `m`
	 * `pos`: the root index of array `f`
	 */
	cout << l << " " << r << " " << pos << endl;
	if (l > r)
		return nullptr;
	node* new_node = new(node);
	(*new_node).value = f[pos];
	for (int i=l; i<=r; i++) {
		if (m[i] == new_node->value) {
			if (i == l) {
				(*new_node).left = nullptr;
				(*new_node).right = rebuild(l+1, r, pos+1);
			} else if (i == r) {
				(*new_node).left = rebuild(l, r-1, pos+1);
				(*new_node).right = nullptr;
			} else {
				(*new_node).left = rebuild(l, i-1, pos+1);
				(*new_node).right = rebuild(i+1, r, pos+i+1-l);
			}
		}
	}
	cout << "(" << new_node->value << "): ";
	if (new_node->left != nullptr) {
		cout << "(" << new_node->left->value << ")";
	} else { cout << "( )"; }
	if (new_node->right != nullptr) {
		cout << "(" << new_node->right->value << ")";
	} else { cout << "( )"; }
	cout << endl;
	return new_node;
}

int main() {
	int n;
	cout << "Please input the number of elements: ";
	cin >> n;
	cout << "Now, input the first root sequence: ";
	for (int i=0; i<n; i++) { cin >> f[i]; }
	cout << "Now, input the middle root sequence: ";
    for (int i=0; i<n; i++) { cin >> m[i]; }

    node* root = rebuild(0, n-1, 0);
	cout << "over..." << endl;
	return 0;
}