// Smyth, Ravela -- CS 532 -- Project #5 
// *** Record.cpp ***

#include "Record.h"

Record::Record(int Id, string Name) {
	this.Id = Id;
	for(int i = 0 ; i < NAME_LENGTH ; i++)
		this.Name[i] = (i < Name.size) ? Name[i] : ' ';
}

int Record::getId(){return Id;}

char[] Record::getName(){return Name;}


