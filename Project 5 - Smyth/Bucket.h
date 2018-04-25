// Smyth, Ravela -- CS 532 -- Project #5 
// *** Bucket.h ***

#ifndef BUCKET_H

	#define BUCKET_H
	#include <iostream>
	#include "Record.h" 
	using namespace std;

	class Bucket {
		private:
			int capacity;
			Record *records;
		public:
			Bucket(int capacity);
			void setRecord(int pos, Record r);
			Record getRecord(int pos);
	}

#endif
