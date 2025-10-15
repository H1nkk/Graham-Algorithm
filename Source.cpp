#include <iostream>
#include <random>
#include "dheap.h"
#include "point.h"
#include "mergeSort.h"

using namespace std;

void pyramidSort(vector<Point>& a) {
	dheap<Point> heap(3);
	heap.pyramidSort(a);
}

int convSort(vector<Point>& a, void (*sortFunc)(vector<Point>& a)) { // returns size of convex hull
	Point c = a[0];
	int m = 0;
	
	for (int i = 1; i < a.size(); i++) {
		if ((a[i].x < c.x) || ((a[i].x == c.x) && (a[i].y < c.y))) {
			c = a[i];
			m = i;
		}
	}
	swap(a[0], a[m]);
	m = 0;
	for (int i = 0; i < a.size(); i++) {
		a[i] = a[i] - c;
	}
	sortFunc(a);
	for (int i = 1; i < a.size(); i++) {
		if (a[i] != a[m]) {
			if (m >= 1)
				while ((m >= 1) && det(a[m] - a[m - 1], a[i] - a[m]) <= 0) // тут изменил a[i] - a[m] >= 0 на a[i] - a[m]) <= 0, т.к. в методичке ошибка
					--m;

			++m;
			swap(a[m], a[i]);
		}

	}
	++m;
	for (int i = 0; i < m; i++) {
		a[i] = a[i] + c;
	}
	return m;
}

void doExperiments(const vector<Point>& a) {

}

void inputExperiments() {
	int n;
	cout << "Input point count: ";
	cin >> n;

	int q, w;
	cout << "Input grid length: ";
	cin >> q;
	cout << "Input grid width: ";
	cin >> w;

	int mode;
	cout << "Choose point placement mode.\n1 - in a rectangle with length of q and width of w\n2 - on this rectangle sides\nInput: ";
	cin >> mode;

	vector<Point> a(n);
	if (mode == 1) {
		/*
		заполнение массива
		*/

		doExperiments(a);
	}
	else if (mode == 2) {

	}
}

int main() {
	inputExperiments();
	return 0;
}