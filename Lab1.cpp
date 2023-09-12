#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <unordered_set>

using namespace std;


struct Node {
	int data;
	Node* prev;
	Node* next;
};

class List {
	private:
		Node* head;
		Node* tail;
	public:
		List() {
			head = nullptr;
			tail = nullptr;
		}

		void append(int num) {
			Node* n = new Node;

			n->data = num;
			n->next = nullptr;
			tail = n;

			if (head == nullptr)
				head = n;
      else {
      	Node *cur = head;
				Node *pr = tail;
        while(cur->next != nullptr) {
						cur = cur->next;
				}
				n->prev = cur;
        cur->next = n;
      }
		}

		void kFromEnd(int k) {
			Node* cur = tail;
			for (int i = 1; i < k; i++)
				cur = cur->prev;
			cout << cur->data << endl;

		}

		void deleteDubs() {
			unordered_set <int> uniqs;
			Node* cur = head;
			while(cur->next != nullptr){
				if (uniqs.find(cur->data) == uniqs.end()) {
					uniqs.insert(cur->data);
				//	cout << "	now: " << cur->data << endl;
					cur = cur->next;
			} else {
				//	cout << "hi " << cur->data << endl;
					Node* pr = cur->prev;
					Node* n = cur->next;
					pr->next = n;
					n->prev = pr;
				//	cout << "	b: " << pr->data << endl;
					cur = n;
				//	cout << "	e: " << n->data << endl;
				}
			}
			if (uniqs.find(cur->data) != uniqs.end()) {
				cur->prev->next = nullptr;
			}
		}

		void printList()
    {
        Node *cur = head;
        cout << "NULL <- ";
        while(cur != NULL)
        {
            cout << "| " << cur->data << " |<-->";
            cur = cur->next;
        }
				cout << "NULL" << endl;
    }
};


int main() {

	List list;
	string nums, n;
	getline(cin, nums);
	stringstream X(nums);
	while (getline(X, n, ' ')) {
		int ni = stoi(n);
		list.append(ni);
	}

	int k;
	cin >> k;
	cout << endl;

	list.printList();
	list.kFromEnd(k);
	list.deleteDubs();
	list.printList();

	return 0;
}