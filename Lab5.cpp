#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct Edge {				// структура ребра графа
public:
	int x, y, w;
    Edge(){}
    Edge(int x, int y, int w): x(x), y(y), w(w) {}
};

vector<int> root;			// вектор для хранения ребер графа

bool comp(Edge a, Edge b) {	// компаратор для сортировки
	return a.w < b.w;
}

int parent(int x) {
    while(root[x] != x)
    {
        root[x] = root[root[x]];
        x = root[x];
    }
    return x;
}

void union_find(int x, int y) {
    int d = parent(x);
    int e = parent(y);
    root[d] = root[e];
}

int Kruskal(vector<Edge> v, int m) {				// алгоритм Краскала для поиска минимального остовного дерева, подсчитывает вес дерева
	int w_sum = 0;
	int x, y;
	for (int i = 0; i < m; i++) {
		x = v[i].x;
		y = v[i].y;
		//cout << "parents " << x << " " << parent(x) << " " << y << " " << parent(y) << endl;
		if (parent(x) != parent(y)) {
			cout << "added " << v[i].x << " -- " << v[i].y << " weight: " << v[i].w << endl;
			w_sum += v[i].w;
			union_find(x, y);
		}
	}
	cout << "MST sum = ";
	return w_sum;
}

//----------------------------------------------------------

vector<int> pi(string s) {					// префикс функция
	vector<int> lenght(s.size());
	//cout << s.size() << endl;
	int j = 0;

	for (int i = 1; i < s.size(); i++) {
		if (s[i] == s[j]) {
			lenght[i] = j + 1;
			j++;
		} else {
			if (j == 0) lenght[i] = 0;
			else j = lenght[j-1];
		}
	}
	return lenght;
}

//----------------------------------------------------------

int main() {

	cout << "Part one:" << endl;
	int n, m;
	cin >> n >> m;

	root.resize(n);
	vector<Edge> vect(m);

	for (int i = 0; i < n; i++) root[i] = i;

	for (int i = 0; i < m; i++) {
		int bi, ei, wi;
		cin >> bi >> ei >> wi;
		vect[i].x = bi;
		vect[i].y = ei;
		vect[i].w = wi;
	}

	sort(vect.begin(), vect.end(), comp);
	//for (int i = 0; i < n; i++) cout << root[i] << " ";
	cout << endl;
	cout << Kruskal(vect, m) << endl; 

//-----------------------------------------------------------
	cout << endl;
	cout << "Part two:" << endl;
	string Str, s;
	cin >> s;
	cin >> Str;

	vector<int> pref(s.size());
	vector<int> answer(0);
	pref = pi(s);
	//for (int i=0; i< s.size();i++) cout << pref[i] << " ";

	int j = 0;
	for (int i = 0; i < Str.size(); i++) {
		if (s[j] == Str[i]) {
			if (j == s.size() - 1) {
				answer.push_back(i-j+1);
				j = 0;
				//i--;
			} else j++;
		} else {
			if (j > 0) {
				j = pref[j-1];
				i--;
			}
		}
	}
	cout << answer.size() << endl;
	for (int i=0; i < answer.size(); i++) cout << answer[i] << " ";
	cout << endl;

	return 0;
}