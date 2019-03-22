//  532_le7_smyth.cpp
//
//  Smyth, Ravela
//  CS532 Lab Exercise #7 " Concordance with map"



#include "stdafx.h"
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <fstream>
using namespace std; 


int main()
{
	//file open
	string fileName, word;
	cin >> fileName;

	ifstream fin;
	fin.open(fileName);

	if (!fin) { cout << "Bad file!\n";  return 0; }


	//make map
	map<string, int>  myMap;

	while (fin >> word) {
		if (!myMap.count(word)) myMap.insert({ word, 1 });
		else myMap.find(word)->second++; 
	}

	//output map
	map<string, int>::iterator itr; 

	for (itr = begin(myMap); itr != end(myMap); ++itr)
		cout << itr->first << " : " << itr->second << endl;

}
