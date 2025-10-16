#include <iostream>
#include <iomanip>
#include <random>
#include <chrono>
#include <utility>
#include <time.h>
#include <fstream>
#include "dheap.h"
#include "point.h"
#include "mergeSort.h"

const int EXPCOUNT = 100;

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

vector<Point> generatePoints(int n, int q, int w, int mode) {
	vector<Point> a(n);
	if (mode == 1) {
		for (int i = 0; i < n; i++) {
			double x = double(rand()) / double(RAND_MAX) * q; // rectangle sides are included
			double y = double(rand()) / double(RAND_MAX) * w; // rectangle sides are included
			a[i] = Point(x, y);
		}
	}
	else if (mode == 2) {
		for (int i = 0; i < n; i++) {
			int sideId = rand() % 4;
			double x, y;
			enum sides {
				left = 0,
				top = 1,
				right = 2,
				bottom = 3
			};
			switch (sideId)
			{
			case (left):
				x = 0.0;
				y = double(rand()) / double(RAND_MAX) * w;
			case (top):
				x = double(rand()) / double(RAND_MAX) * q;
				y = w;
			case (right):
				x = q;
				y = double(rand()) / double(RAND_MAX) * w;
			case (bottom):
				x = double(rand()) / double(RAND_MAX) * q;
				y = 0.0;
			}
			a[i] = Point(x, y);
		}
	}
	return a;
}

// @return {mergeTime, pyramidTime}
pair<double, double> doExperiments(const vector<Point>& a) {
	vector<Point> b = a;
	auto start = chrono::high_resolution_clock::now();
	convSort(b, mergeSort);
	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
	double mergeTime = double(duration.count()) / 1000000.0;

	b = a;
	start = chrono::high_resolution_clock::now();
	convSort(b, pyramidSort);
	stop = chrono::high_resolution_clock::now();
	duration = chrono::duration_cast<chrono::microseconds>(stop - start);
	double pyramidTime = double(duration.count()) / 1000000.0;

	return { mergeTime, pyramidTime };
}

void doTask31() {
	ofstream outMergeMode1("Task31MergeSortMode1.txt");
	ofstream outMergeMode2("Task31MergeSortMode2.txt");
	ofstream outPyramidMode1("Task31PyramidSortMode1.txt");
	ofstream outPyramidMode2("Task31PyramidSortMode2.txt");
	outMergeMode1.clear(); outMergeMode1 << setprecision(10) << fixed;
	outMergeMode2.clear(); outMergeMode2 << setprecision(10) << fixed;
	outPyramidMode1.clear(); outPyramidMode1 << setprecision(10) << fixed;
	outPyramidMode2.clear(); outPyramidMode2 << setprecision(10) << fixed;

	outMergeMode1 << "n | Time\n";
	outMergeMode2 << "n | Time\n";
	outPyramidMode1 << "n | Time\n";
	outPyramidMode2 << "n | Time\n";

	int q = 1000000, w = 1000000;
	for (int n = 1; n <= 1000000 + 1; n += 10000) {

		int mode = 1;
		double mergeTimeSum = 0.0, pyramidTimeSum = 0.0;
		int experimentCount = 10 + EXPCOUNT / (n / 10000 + 1);
		for (int i = 0; i < experimentCount; i++) {
			vector<Point> a = generatePoints(n, q, w, mode);
			pair<double, double> res = doExperiments(a);
			mergeTimeSum += res.first;
			pyramidTimeSum += res.second;
		}
		double mergeTime = mergeTimeSum / experimentCount;
		double pyramidTime = pyramidTimeSum / experimentCount;
		outMergeMode1 << n << ' ' << mergeTime << '\n';
		outPyramidMode1 << n << ' ' << pyramidTime << '\n';

		mode = 2;
		mergeTimeSum = 0.0, pyramidTimeSum = 0.0;
		for (int i = 0; i < experimentCount; i++) {
			vector<Point> a = generatePoints(n, q, w, mode);
			pair<double, double> res = doExperiments(a);
			mergeTimeSum += res.first;
			pyramidTimeSum += res.second;
		}
		mergeTime = mergeTimeSum / experimentCount;
		pyramidTime = pyramidTimeSum / experimentCount;
		outMergeMode2 << n << ' ' << mergeTime << '\n';
		outPyramidMode2 << n << ' ' << pyramidTime << '\n';
		cout << "Task 3.1: n = " << n << " done\n"; cout << flush;
	}
}

void doTask32() {
	ofstream outMergeMode1("Task32MergeSortMode1.txt");
	ofstream outMergeMode2("Task32MergeSortMode2.txt");
	ofstream outPyramidMode1("Task32PyramidSortMode1.txt");
	ofstream outPyramidMode2("Task32PyramidSortMode2.txt");
	outMergeMode1.clear(); outMergeMode1 << setprecision(10) << fixed;
	outMergeMode2.clear(); outMergeMode2 << setprecision(10) << fixed;
	outPyramidMode1.clear(); outPyramidMode1 << setprecision(10) << fixed;
	outPyramidMode2.clear(); outPyramidMode2 << setprecision(10) << fixed;

	outMergeMode1 << "q | Time\n";
	outMergeMode2 << "q | Time\n";
	outPyramidMode1 << "q | Time\n";
	outPyramidMode2 << "q | Time\n";

	int n = 1000000;
	int w;
	for (int q = 0; q <= 1000000; q += 10000) {
		w = q;
		int mode = 1;
		double mergeTimeSum = 0.0, pyramidTimeSum = 0.0;
		int experimentCount = 10;
		for (int i = 0; i < experimentCount; i++) {
			vector<Point> a = generatePoints(n, q, w, mode);
			pair<double, double> res = doExperiments(a);
			mergeTimeSum += res.first;
			pyramidTimeSum += res.second;
		}
		double mergeTime = mergeTimeSum / experimentCount;
		double pyramidTime = pyramidTimeSum / experimentCount;
		outMergeMode1 << q << ' ' << mergeTime << '\n';
		outPyramidMode1 << q << ' ' << pyramidTime << '\n';

		mode = 2;
		mergeTimeSum = 0.0, pyramidTimeSum = 0.0;
		for (int i = 0; i < experimentCount; i++) {
			vector<Point> a = generatePoints(n, q, w, mode);
			pair<double, double> res = doExperiments(a);
			mergeTimeSum += res.first;
			pyramidTimeSum += res.second;
		}
		mergeTime = mergeTimeSum / experimentCount;
		pyramidTime = pyramidTimeSum / experimentCount;
		outMergeMode2 << q << ' ' << mergeTime << '\n';
		outPyramidMode2 << q << ' ' << pyramidTime << '\n';
		cout << "Task 3.2: q = " << q << " done\n"; cout << flush;
	}
}

bool checkValid(const vector<Point>& a) {
	vector<Point> b = a;
	int sz1 = convSort(b, mergeSort);

	vector<Point> c = a;

	int sz2 = convSort(c, pyramidSort);

	if (sz1 != sz2) return false;
	for (int i = 0; i < sz1; i++) {
		if (c[i] != b[i]) {
			return false;
		}
	}
	return true;
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

	vector<Point> a = generatePoints(n, q, w, mode);
	pair<double, double> res = doExperiments(a);
	cout << "Merge sort time: " << res.first << '\n';
	cout << "Pyramid sort time: " << res.second << '\n';
}

int main() {
	srand(time(0));
	//inputExperiments();
	doTask31();
	doTask32();

	return 0;
}