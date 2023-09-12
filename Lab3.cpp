#include <iostream>
#include <cmath>
#include <list>

using namespace std;

enum Colour { red, black };

struct Node {
public:											// структура узла графа
	int key;
	Colour col;
	Node* left_child;
	Node* right_child;
	Node* parent;
};

class RBT {
private:
	Node* root;
	int black_hight = 0;
public:
	RBT(int r) {							// Конструктор дерева, на вход подается значение корня
		root = new Node;

		root->key = r;
		root->left_child = NULL;
		root->right_child = NULL;
		root->parent = NULL;
	}

	void insert(int keys[][2]) {			// метод заполнения графа по двум детям
		Node* cur = root;
		for (int i = 0; i < 10; i++){
			int lck = keys[i][0], rck = keys[i][1];
			if ((lck == 0) && (rck == 0)) continue;
			if ((cur->left_child == NULL) && (cur->right_child == NULL)) {
				if (rck == 0) {
					if (lck < cur->key) {
						Node* lc = new Node;

						lc->key = lck;
						lc->left_child = NULL;
						lc->right_child = NULL;
						lc->parent = cur;

						cur->left_child = lc;
						keys[i][0] = 0;
						i = -1;
						cout << "node " << cur->key << " left_child " << cur->left_child->key << " right_child " << cur->right_child << endl;
						cur = root;
					}
				}

				else if (lck == 0) {
					if (rck > cur->key) {
						Node* rc = new Node;

						rc->key = rck;
						rc->left_child = NULL;
						rc->right_child = NULL;
						rc->parent = cur;

						cur->right_child = rc;
						keys[i][1] = 0;
						i = -1;
						cout << "node " << cur->key << " left_child " << cur->left_child << " right_child " << cur->right_child->key << endl;
						cur = root;

					}
				}

				else if ((lck < cur->key) && (rck > cur->key)) {
					Node* lc = new Node;

						lc->key = lck;
						lc->left_child = NULL;
						lc->right_child = NULL;
						lc->parent = cur;

					Node* rc = new Node;

						rc->key = rck;
						rc->left_child = NULL;
						rc->right_child = NULL;
						rc->parent = cur;

					cur->left_child = lc;
					cur->right_child = rc;
					keys[i][0] = 0;
					keys[i][1] = 0;
					i = -1;
					cout << "node " << cur->key << " left_child " << cur->left_child->key << " right_child " << cur->right_child->key << endl;
					cur = root;
				}
			} else { 
				if (rck == 0) {
					if (lck < cur->key) {
						if (cur->left_child) cur = cur->left_child;
						i--;
					}
					else {
						if (cur->right_child) cur = cur->right_child;
						i--;
					}
				}

				else if (lck == 0) {
					if (rck < cur->key) {
						if (cur->left_child) cur = cur->left_child;
						i--;
					}
					else {
						if (cur->right_child) cur = cur->right_child;
						i--;
					}
				}

				else if ((lck < cur->key) && (rck < cur->key)) {
					if (cur->left_child) cur = cur->left_child;
					i--;
				}

				else if ((lck > cur->key) && (rck > cur->key)) {
					if (cur->right_child) cur = cur->right_child;
					i--;
				}
			}
		}
	}

	void paint(int mask, int n) {				// раскраска графа по битовой маске
		list<Node*> queue;
		queue.push_back(root);

		while (!queue.empty()) {
			Node* cur = queue.front();
			if (((int)pow(2, n-1) & mask) != 0) cur->col = black;
			else cur->col = red;
			//cout << cur->key << " " << cur->col << endl;
			queue.pop_front();
			if (cur->left_child) queue.push_back(cur->left_child);
			if (cur->right_child) queue.push_back(cur->right_child);

			n--;
		}
		//cout << "\n\n\n";
	}

	int RB_check() {							// проверка, является ли дерево красно-черным с помощью алгоритма обхода в ширину
		list<Node*> queue;
		queue.push_back(root);

		while (!queue.empty()) {
			Node* cur = queue.front();
			if (cur->parent) 
				if ((cur->parent->col == red) && (cur->col == red)) 
					return 0;
			queue.pop_front();
			if (cur->left_child) {
				if ((cur->left_child->col == red) && (cur->col == red)) 
					return 0;
				queue.push_back(cur->left_child);
			}
			if (cur->right_child) {
				if ((cur->right_child->col == red) && (cur->col == red))
					return 0;
				queue.push_back(cur->right_child);
			}

			if ((cur->left_child == NULL) || (cur->right_child == NULL)) {
				int b_count = 0;
				if (cur->col == black) b_count++;
				Node* cur_path = cur;
				while (cur_path->parent) {
					if (cur_path->parent->col == black) b_count++;
				//	cout << cur_path->key << " col " << cur_path->col  << " b_count " << b_count << "\n/\\\n|" << endl;
					cur_path = cur_path->parent; 
				}
				//cout << cur_path->key << " col " << cur_path->col << " b_count " << b_count << " black_hight " << black_hight << endl;
				if (!black_hight) black_hight = b_count;
				if (black_hight != b_count) return 0;
				//cout << "\n\n";
			}
		}
		return 1;	
	}

	int paint_count(int n) {				// подсчет побитовой маски и количества подходящих деревьев
		int count = 0;
		int mask;
		mask = pow(2, n) - 1;
		//cout << mask << endl;
		while (mask >= 0) {
			paint(mask, n);
			count += RB_check();
			//cout << "\n\n\n";
			black_hight = 0;
			mask--;
		}

		return count;
	}
};

int main() {

	int n, r, i1 = 0, i2=9;
	int mas[10][2] = {0, 0};				// массив для хранения пар детей
	cin >> n;
	cin >> r;
	RBT tree = r;
	for (int i = 0; i < n; i++) {
		int lc, rc;
		cin >> lc >> rc;
		if ((lc != 0) && (rc != 0)) {
			mas[i1][0] = lc;
			mas[i1][1] = rc;
			i1++;
		}
		else if ((lc != 0) || (rc != 0)) {
			mas[i2][0] = lc;
			mas[i2][1] = rc;
			i2--;
		}
	}

	tree.insert(mas);

	cout << tree.paint_count(n) << endl;

	return 0;
}