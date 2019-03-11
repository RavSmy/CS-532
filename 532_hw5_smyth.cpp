//  532_hw5_smyth.cpp
//
//  Smyth, Ravela
//  CS532 Homework #5 "Heap"

#include <iostream>
#include <ctype.h>

using namespace std; 

struct S{
	double x;
	int n;
	char c;
};

bool sbb0(const S & a, const S & b);
bool sbb1(const S & a, const S & b);
void show(const S ar[], unsigned els);
void heapify(S bt[], unsigned els, bool (*sbb)(const S & a, const S & b));
void heapsort(S bt[], unsigned els, bool (*sbb)(const S & a, const S & b));
void swap (S & a, S & b);


int main() {
	S ar[6] = {{19.5, 3, 'B'},{3.45, 9, 'c'},{90.2, 23, '+'},{12.34, 2, '*'},{2.45, 29, 'z'},{9.2, 14, ')'}};
	cout << "Before heapify \n";	
	show(ar, 6);

	cout <<endl<<endl<<"HeapSort sbb0\n";
	heapsort(ar, 6, sbb0);

	cout <<endl<<endl<<"HeapSort sbb1\n";
	heapsort(ar, 6, sbb1);
}

void heapify(S bt[], unsigned els, bool (*sbb)(const S & a, const S & b)) {
	for (int i = 1; i < els; i++)
	{
		//If parent 'smaller' than childern
		if (sbb(bt[i], bt[(i-1)/2]))
		{
			int j = i;

			//Switch parent and child and trickle down to reheap
			while (sbb(bt[i], bt[(j-1)/2])) 
			{
				swap(bt[i], bt[(j-1)/2]);
				j = (j-1) / 2; 
			}
		}
	}
}

void heapsort(S bt[], unsigned els, bool (*sbb)(const S & a, const S & b)) {
	heapify(bt, els, sbb);
	
	for (int i = els - 1; i > 0 ; i--) {
		//Switch largest to end
		swap(bt[i], bt[0]); 

		cout << bt[i].x <<" " << bt[i].n << " " << bt[i].c << "\n"; 

		//Reheap
		heapify(bt, i, sbb);

	}
}

void swap (S & a, S & b) {
	S c = {a.x, a.n, a.c};
	a.x = b.x; a.n = b.n; a.c = b.c;
	b.x = c.x; b.n = c.n; b.c = c.c;
}

bool sbb0(const S & a, const S & b) { 
	if (a.x > b.x) return true;
	return false; 
}

bool sbb1(const S & a, const S & b) {
	if ((isalpha(a.c) && isalpha(b.c)) && (tolower(a.c) > tolower(b.c))||a.c > b.c) return true;
	return false;
}

void show(const S ar[], unsigned els) {
	for (int i = 0 ; i < els ; i++)
		cout << i << ": " << ar[i].x <<" " << ar[i].n << " " << ar[i].c << "\n";

}
