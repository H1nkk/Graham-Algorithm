#include <iostream>
#include "dheap.h"

using namespace std;

void arrCopy(vector<int>& src, vector<int>& dist, int start, int end) {
	for (int i = start; i < end; i++) {
		dist[i] = src[i];
	}
}

void merge(vector<int>& a, vector<int>& b, int start, int mid,  int end) {
	int i = start, j = mid;

	for (int k = start; k < end; k++) {
		if (i < mid && (j >= end || b[i] <= b[j])) {
			a[k] = b[i];
			i++;
		}
		else {
			a[k] = b[j];
			j++;
		}
	}
}

void splitMerge(vector<int>& a, vector<int>& b, int start, int end) {
	if (end - start <= 1) return;
	int mid = (start + end) / 2;

	splitMerge(b, a, start, mid);
	splitMerge(b, a, mid, end);

	merge(a, b, start, mid, end);

}

void mergeSort(vector<int>& a, vector<int>& b) {
	arrCopy(a, b, 0, a.size());
	splitMerge(a, b, 0, a.size());
}

int main() {
	dheap<int> heap(5);
	for (int i = 0; i < 10; i++)
		heap.insert(123 * i % 544);
	vector<int> a;

	for (int i = 0; i < 10; i++) {
		a.push_back(123 * i % 544);

	}
	vector<int> b(a.size());

	void (*func)(vector<int>&, vector<int>&) = mergeSort;
	func(a, b);
	for (auto x : a) {
		cout << x << ' ';
	}
	return 0;
}