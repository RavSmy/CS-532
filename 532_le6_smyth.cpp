//  532_le6_smyth.cpp
//
//  Smyth, Ravela
//  CS532 Lab Exercise #6 "pair and set"



#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <array>
#include <set>
using namespace std;
typedef pair<int, int> OP; 
typedef set<pair<int, int>> SOP;

ostream & operator<<(ostream &out, const OP &p);
ostream & operator<<(ostream &out, const SOP &p);

int main()
{
	OP oph[100];
	OP total = { 0,0 };
	for (int i = 0; i < 100; i++) {
		oph[i].first = i; 
		oph[i].second = i * i;
		total.first += i; 
		total.second += oph[i].second; 
	}


	

	SOP myset(begin(oph), end(oph));
	myset.insert(total); 

	int i = 0;
	
	for (SOP::iterator itr = myset.begin(); itr != myset.end(); ++itr, i++) {
		if (i == 7) {
			i = 0;
			total = *itr;
			--itr; 
			myset.erase(total);
		}
	}
	myset.erase(OP{ 0,0 });
	for (int i = 0; i < 100; i++)
		cout << oph[i] << endl;

	cout << "\n\n+++ SET +++: \n\n" << myset;
	
}

ostream & operator<<(ostream &out, const SOP &p) {
	SOP::iterator itr;

	for (itr = begin(p); itr != end(p); ++itr)
		out << *itr << endl;

	return out; 
}


ostream & operator<<(ostream &out, const OP &p) {
	return out << "(" << p.first << ", " << p.second << ")";
}

