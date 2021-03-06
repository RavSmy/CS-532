// Smyth, Ravela -- CS 532 -- Project #5 
// *** Record.h ***

#ifndef RECORD_H

	#define RECORD_H
	#define NAME_LENGTH 30 
	#include <iostream>
	using namespace std;

	class Record {
		private:
			int Id;
			char Name[NAME_LENGTH]; 
		public:
			Record();
			Record(int id, string name);
			int getId();
			char[] getName();
	}

#endif
