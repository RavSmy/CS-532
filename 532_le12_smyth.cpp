//  532_le12_smyth.cpp
//
//  Smyth, Ravela
//  CS532 Lab Exercise #12 "Huffman Exercise"

#include<iostream>
#include<string>
#include<algorithm>
#include<set>

using namespace std;
typedef pair<char, string>  p;
typedef set<p>sp;

sp code = {{ 'A',"0" },{ 'B',"11001" },{ 'C',"10" },{ 'D',"1101" },{ 'E',"1111" },
	         { 'F',"110000" },{ 'G',"11101" },{ 'H',"11100" },{ '.',"110001" }};

string huffman(const string & msg);
string namffuh(const string & bitString);

int main() {
	cout << namffuh(huffman("BAG."));
}

string huffman(const string & msg) {
	string ret;
	for (char c : msg)
		for (p test : code) 
			if (c == test.first)
				ret += test.second;	
		
	return ret;
}

string namffuh(const string & bitString) {
	string ret, holder;
	for (char c : bitString) {
		holder += c;
		for (p P : code)
			if (holder == P.second)
			{
				ret += P.first;
				holder="";
			}
	}
	return ret;
}
