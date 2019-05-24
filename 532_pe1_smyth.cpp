//  532_pe1_smyth.cpp
//  CS 542 - Discrete Structures
//  Practice Exam Prob #1 

#include <iostream>
using namespace std;

unsigned nonHeapPos(const unsigned a[], unsigned els);

int main()
{

	unsigned a[] = { 0, 9, 15, 10, 7, 12, 11 }, b[] = { 0, 90, 15, 10, 7, 12, 11 };

	cout << nonHeapPos(a, 7) << " , " << nonHeapPos(b, 7) << endl;
}


unsigned nonHeapPos(const unsigned a[], unsigned els) {

	int invalid = 0;

	for (int i = 1; i <= 1 + ((els - 2) / 2); i++)
	{
		if (a[2 * i] > a[i])
			invalid = i;

		if (2 * i + 1 < els && a[2 * i + 1] > a[i])
			invalid = i;
	}

	return invalid;
}

