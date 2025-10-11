#include <iostream>
#include "dheap.h"

#define STEPS 5

using namespace std;

struct Point {
	int x;
	int y;

};

bool operator<=(Point a, Point b) {
	int det = a.x * b.y - b.x * a.y;
	return (det > 0 || ((det == 0) && ((a.x * a.x + a.y * a.y) < (b.x * b.x + b.y * b.y))));
}

//struct Node {
//	Node* left;
//	Node* right;
//	T value;
//	T loser;
//	Node(Node* left, Node* right, T value, T loser) : left(left), right(right), value(value), loser(loser) {}
//};
//
//class Tree {
//	vector<Node> memory;
//	Node* start;
//
//	Node* buildTree(const vector<Node*>& v) {
//		/*memory.resize(sz);
//		sz *= 2;
//		height++;*/
//		vector<Node*> nextLayer;
//		for (int i = 0; i < v.size(); i += 2) {
//			T el1 = v[i]->value;
//			Node* parent;
//			if (i + 1 < v.size()) {
//				T el2 = v[i + 1]->value;
//				T loser = max(el1, el2);
//				T winner = min(el1, el2);
//				parent = new Node(v[i], v[i + 1], winner, loser);
//			}
//			else {
//				parent = new Node(v[i], new Node{ nullptr,nullptr, INT_MAX, INT_MAX }, v[i]->value, INT_MAX); // ьс int_MIN
//			}
//			nextLayer.push_back(parent);
//		}
//		if (nextLayer.size() == 1) {
//			return nextLayer[0];
//		}
//		else {
//			return buildTree(nextLayer);
//		}
//	}
//
//	void replayGames(Node*& p, Node*& nw) {
//		Node* loser;
//		Node* winner;
//		if (p->value > nw->value) {
//			loser = p;
//			winner = nw;
//		}
//		else {
//			loser = nw;
//			winner = p;
//		}
//		p->value = loser->value;
//	}
//
//public:
//	Tree(const vector<Node*>& v) {
//		start = buildTree(v);
//	}
//	
//	T getWinner() {
//		return start->value;
//	}
//};

void arrCopy(vector<int>& src, vector<int>& dist, int start, int end) {
	for (int i = start; i < end; i++) {
		dist[i] = src[i];
	}
}

int getMin(vector<int>& b, vector<int>& splits, int start, int end) {

	int minimum = INT_MAX, splitsMinIndex = -1;
	for (int i = 0; i < STEPS + 1; i++) {
		if (splits[i] >= start + (i + 1) * (end - start) / STEPS || splits[i] >= end) continue;
		if (b[splits[i]] < minimum) {
			minimum = b[splits[i]];
			//minIndex = splits[i];
			splitsMinIndex = i;
		}
	}

	splits[splitsMinIndex]++;
	return minimum;
}

void merge(vector<int>& a, vector<int>& b, int start, int end) {
	vector<int> splits(STEPS + 1);
	splits[0] = start;
	for (int i = 1; i < STEPS; i++) {
		splits[i] = start + i * (end - start) / STEPS;
	}
	splits[STEPS] = end;

	for (int k = start; k < end; k++) {
		a[k] = getMin(b, splits, start, end);
	}

}

void splitMerge(vector<int>& a, vector<int>& b, int start, int end) {
	if (end - start <= 1) return;
	vector<int> splits(STEPS + 1);
	splits[0] = start;
	for (int i = 1; i < STEPS; i++) {
		splits[i] = start + i * (end - start) / STEPS;
	}
	splits[STEPS] = end;
	for (int i = 0; i < STEPS; i++) {
		splitMerge(b, a, splits[i], splits[i + 1]);
	}

	merge(a, b, start, end);
}

void mergeSort(vector<int>& a) {
	vector<int> b = a;
	//arrCopy(a, b, 0, a.size());
	splitMerge(a, b, 0, a.size());
}

void pyramidSort(vector<int>& a) {
	dheap<int> heap(3);
}

int main() {
	vector<int> a = { 1,7,5,3,9,2,-8,4, 2 };
	for (int i = 0; i < 50; i++) {
		a.push_back((i * 123123 + 54) % 1432);
	}
	mergeSort(a);
	for (auto x : a) {
		cout << x << ' ';
	}
	return 0;
}