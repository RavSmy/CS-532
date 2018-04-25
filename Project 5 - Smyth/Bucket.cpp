// Smyth, Ravela -- CS 532 -- Project #5 
// *** Bucket.cpp ***

#include "Bucket.h"

Bucket::Bucket(int capacity){
	this.capacity = capacity;
	records = new *Record[capacity];
}

void Bucket::setRecord(int pos, Record r){*records[pos] = new Record(r);}

Record Bucket::getRecord(int pos){return *records[pos]; }
