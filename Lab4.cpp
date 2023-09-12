#include <iostream>

using namespace std;

void quicksort(int* mas, int start, int end)  // алгоритм быстрой сортировки, в качестве опорнного элемента выбрана середина массива
{
    int i = start;
    int j = end;
    int pivot = mas[(i + j) / 2];

    while (i <= j)
    {
        while (mas[i] < pivot)
            i++;
        while (mas[j] > pivot)
            j--;
        if (i <= j)
        {
            swap(mas[i], mas[j]);
            i++;
            j--;
        }
    }
    if (j > start)
        quicksort(mas, start, j);
    if (i < end)
        quicksort(mas, i, end);
}

int countX(int* mas, int point, int end) {				// подсчет количества начал отрезков, находящихся до точки
	int count = 0;
	for (int i = 0; i < end; i++) {
		if (mas[i] <= point) count++;
		else break;
	}
	return count;
}

int countY(int* mas, int point, int end) {				// подсчет количества концов отрезков, находящихся до точки
	int count = 0;
	for (int i = 0; i < end; i++) {
		if (mas[i] < point) count++;
		else break;
	}
	return count;
}

int main() {
	int n, m;
	cin >> n >> m;
	int* masX = new int[n];
	int* masY = new int[n];
	for (int i = 0; i < n; i++)	cin >> masX[i] >> masY[i];
	quicksort(masX, 0, n-1);
	quicksort(masY, 0, n-1);
	//cout << "masX ";
	//for (int i = 0; i < n; i++)	cout << masX[i] << " ";
	cout << endl;
	//cout << "masY ";
	//for (int i = 0; i < n; i++)	cout << masY[i] << " ";
	//cout << endl;

	int* points = new int[m];

	for (int i = 0; i < m; i++) {
		cin >> points[i];
		cout << countX(masX, points[i], n) - countY(masY, points[i], n) << " ";
	}
	cout << endl;
	delete[] masX;
	delete[] masY;
	delete[] points;

	return 0;
}