//  532_hw3_smyth.cpp
//
//  Smyth, Ravela
//  CS532 Homework #3 "Huffman Trees"

#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <algorithm>
#include <vector>
#include <bitset>

using namespace std;

struct Node {
    Node *ptr0, *ptr1;
    char c = '\0';
    unsigned long long frequency;
}; 

struct extractChar {
	char c='\0';
	int depth=8; 
};

//HUFFMAN TREE
void getFreq(unsigned long long freq[256], const string & fileName);
Node* huffman(string code[256], const unsigned long long freq[256]);
Node getNode (Node * ptr0, Node * ptr1);
vector<Node> freqToPQ(const unsigned long long freq[256]);
Node buildTree(vector<Node> pq);
void decodePQ(string code[], string s, Node *current);
bool freq_sort(const Node & a, const Node & b);

//LITTLE
void little(string code[], const string & finput, const string & flittle) ;

//BIG
void big(string code[], const string & flittle, const string & fbig, Node *head); 

bool die(const string & msg);



int main(int argc, const char * argv[]) {
    unsigned long long freq[256];
    string code[256];
    
    getFreq(freq, "input.txt");
    Node *head = huffman(code, freq);
    
    //OUTPUT CODE[256]
    for (int i = 0 ; i < 256; i++)
        if (code[i] != "" ) cout << "'"<< (char)i << "' (" << freq[i] << ") : " << code[i] << "\n";

    little(code, "input.txt", "little.txt");
    big(code, "little.txt", "big.txt", head);
}

void big(string code[], const string & flittle, const string & fbigg, Node *head) {
	string byte = ""; char c; 	 
	extractChar *current = new extractChar; 
	int k = 0, last; 

	ifstream flit; ofstream fbig;
	flit.open(flittle, ios::binary);
        if(!flit) die("Can't open " + flittle);
	fbig.open(fbigg, ios::binary);
        if (!fbig) die("Can't open " + fbigg);

	flit.get(c); last = c - '0'; 

	while ( k < 1) {
		flit.get(c); 
		
		k++; 	
	}
}


void little(string code[], const string & finput, const string & flittle) {
	string little_code = "0", byte=""; 
	int bitsLeft; char c; 	

	ifstream fin;ofstream flit;
	fin.open(finput, ios::binary);
        if(!fin) die("Can't open " + finput);
	flit.open(flittle, ios::binary);
        if (!flit) die("Can't open " + flittle);

	while (fin.get(c)) {
		byte+=code[c];

		if (byte.length() >= 8) {
			bitset<8> b(byte.substr(0, 8));  
			c = (char) b.to_ulong();
			flit.write(&c,1);

		}
		if (byte.length()>8)
			byte.erase(0,8); 
	} 

	while (byte.length() > 8) {
		bitset<8> b(byte.substr(0, 8));  
		c = (char) b.to_ulong();
		flit.write(&c,1);
		byte.erase(0,8); 
	}
	
	bitsLeft = 8-byte.length();
	for (int i = 0 ; i < bitsLeft; i++)
		byte+="0"; 
	bitset<8> b(byte.substr(0, 8));  
	c = (char) b.to_ulong();
	flit.write(&c,1);
	c = to_string(bitsLeft)[0];
	flit.seekp(0); flit.write(&c,1); 

	flit.close(); fin.close();	
}


void getFreq(unsigned long long freq[256], const string & fileName) {
    ifstream fin;
    char c;
    
    //SET ALL FREQ to 0
    fill(freq, freq+256, 0);
    
    fin.open(fileName, ios::binary);
    if(!fin) die("Can't open " + fileName);
    
    //RECORD FREQS FROM "fileName"
    while (fin.get(c))
        freq[(int)c]++;

    fin.close();
}

Node* huffman(string code[256], const unsigned long long freq[256]) {
    
    // FREQUENCY TO SORTED PQ
    vector<Node> pq = freqToPQ(freq);
    
    // BUILD TREE (0 - small, 1 -large
    Node *head = new Node( buildTree(pq));

    
    // DECODE TO CHAR
    fill(code, code+256, "");
    decodePQ(code, "", head);
    
    return head;
}

Node getNode ( Node * ptr0, Node * ptr1) {
    Node current;
    
    current.ptr0 = ptr0;
    current.ptr1 = ptr1;
    current.frequency = ptr0->frequency + ptr1->frequency;
    return current;
}

vector<Node> freqToPQ(const unsigned long long freq[256]) {
    vector<Node> pq;
    Node *head = new Node;
    
    //COPY NON-ZERO FREQ CHARS DATA TO PQ
    for (int i =0; i < 256; i++) {
        if (freq[i] != 0) {
            head->frequency = freq[i];
            head->c = i;
            pq.push_back(*head);
        }
    }
    
    //SORT PQ
    sort(pq.begin(), pq.end(), freq_sort);
    
    return pq;
}

Node buildTree(vector<Node> pq) {
    Node *current = nullptr, *ptr0, *ptr1;
    
    //BUILD TREE UNTIL ONE NODE
    while (pq.size() > 1) {
        //COMBINE SMALLEST TWO FREQS INTO NEW NODE
        ptr0 = new Node(pq.back());
        pq.pop_back();
        ptr1 = new Node(pq.back());
        pq.pop_back();
        
        current = new Node(getNode(ptr0, ptr1));
        //ADD NEW NODE BACK INTO PQ
        pq.push_back(*current);
        //RESORT INCLUDING NEW NODE
        sort(pq.begin(), pq.end(), freq_sort);
    }
    
    return *current;
}

void decodePQ(string code[], string s, Node *current) {
    //IF CHAR IS PRESENT THEN SET STRING TO CODE[CHAR]
    if (current->c != '\0') code[current->c] = s;
    //ELSE SIFT THROUGH TREE WHILE BUILDING STRING
    else {
        decodePQ(code, s+"0", current->ptr0);
        decodePQ(code, s+"1", current->ptr1);
    }
}

bool freq_sort(const Node & a, const Node & b) {return a.frequency > b.frequency;}


bool die(const string & msg){
    cout <<"Fatal error: " << msg <<endl;
    exit(EXIT_FAILURE);
}

/*

//  532_hw3_smyth.cpp
//
//  Smyth, Ravela
//  CS532 Homework #3 "Huffman Trees"

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <algorithm>
#include <vector>
#include <bitset>

using namespace std;

struct Node {
	Node *ptr0, *ptr1;
	char c = '\0';
	unsigned long long frequency;
};


//HUFFMAN TREE
void getFreq(unsigned long long freq[256], const string & fileName);
Node* huffman(string code[256], const unsigned long long freq[256]);
Node getNode(Node * ptr0, Node * ptr1);
vector<Node> freqToPQ(const unsigned long long freq[256]);
Node buildTree(vector<Node> pq);
void decodePQ(string code[], string s, Node *current);
bool freq_sort(const Node & a, const Node & b);

//LITTLE
void little(string code[], const string & finput, const string & flittle);

//BIG
void big(string code[], const string & flittle, const string & fbig, Node *head);

bool die(const string & msg);



int main(int argc, const char * argv[]) {
	unsigned long long freq[256];
	string code[256];

	getFreq(freq, "input.txt");
	Node *head = huffman(code, freq);

	//OUTPUT CODE[256]
	for (int i = 0; i < 256; i++)
		if (code[i] != "") cout << "'" << (char)i << "' (" << freq[i] << ") : " << code[i] << "\n";

	little(code, "input.txt", "little.txt");
	big(code, "little.txt", "big.txt", head);
}

void big(string code[], const string & flittle, const string & fbigg, Node *head) {
	string byte = ""; char c;
	int last;

	ifstream flit; ofstream fbig;
	flit.open(flittle, ios::binary);
	if (!flit) die("Can't open " + flittle);
	fbig.open(fbigg, ios::binary);
	if (!fbig) die("Can't open " + fbigg);

	//flit.get(c); last = c - '0';

	while (flit.get(c)) {
		//for (int i = 0; i < 8; i++) // or (int i = 0; i < 8; i++)  if you want reverse bit order in bytes
		//	cout << ((c >> i) & 1);
	//	cout << endl;
	}
}


void little(string code[], const string & finput, const string & flittle) {
	string little_code = "0", byte = "";
	int bitsLeft; char c;

	ifstream fin; ofstream flit;
	fin.open(finput, ios::binary);
	if (!fin) die("Can't open " + finput);
	flit.open(flittle, ios::binary);
	if (!flit) die("Can't open " + flittle);

	while (fin.get(c)) {
		byte += code[c];

		if (byte.length() >= 8) {
			bitset<8> b(byte.substr(0, 8));
			c = static_cast<unsigned char>(b.to_ulong());
			cout << "CHAR: " <<  c << " ++\n";
			flit.write(&c, 1);
			
		}
		if (byte.length()>8)
			byte.erase(0, 8);
	}



	while (byte.length() > 8) {
		flit.write(byte.substr(0, 8).c_str(), 1);
		byte.erase(0, 8);
	}

	bitsLeft = 8 - byte.length();
	for (int i = 0; i < bitsLeft; i++)
		byte += "0";
	bitset<8> b(byte.substr(0, 8));
	c = (char)b.to_ulong();
	flit.write(&c, 1);
	c = to_string(bitsLeft)[0];
	flit.seekp(0); flit.write(&c, 1);

	flit.close(); fin.close();
}


void getFreq(unsigned long long freq[256], const string & fileName) {
	ifstream fin;
	char c;

	//SET ALL FREQ to 0
	fill(freq, freq + 256, 0);

	fin.open(fileName, ios::binary);
	if (!fin) die("Can't open " + fileName);

	//RECORD FREQS FROM "fileName"
	while (fin.get(c))
		freq[(int)c]++;

	fin.close();
}

Node* huffman(string code[256], const unsigned long long freq[256]) {

	// FREQUENCY TO SORTED PQ
	vector<Node> pq = freqToPQ(freq);

	// BUILD TREE (0 - small, 1 -large
	Node *head = new Node(buildTree(pq));


	// DECODE TO CHAR
	fill(code, code + 256, "");
	decodePQ(code, "", head);

	return head;
}

Node getNode(Node * ptr0, Node * ptr1) {
	Node current;

	current.ptr0 = ptr0;
	current.ptr1 = ptr1;
	current.frequency = ptr0->frequency + ptr1->frequency;
	return current;
}

vector<Node> freqToPQ(const unsigned long long freq[256]) {
	vector<Node> pq;
	Node *head = new Node;

	//COPY NON-ZERO FREQ CHARS DATA TO PQ
	for (int i = 0; i < 256; i++) {
		if (freq[i] != 0) {
			head->frequency = freq[i];
			head->c = i;
			pq.push_back(*head);
		}
	}

	//SORT PQ
	sort(pq.begin(), pq.end(), freq_sort);

	return pq;
}

Node buildTree(vector<Node> pq) {
	Node *current = nullptr, *ptr0, *ptr1;

	//BUILD TREE UNTIL ONE NODE
	while (pq.size() > 1) {
		//COMBINE SMALLEST TWO FREQS INTO NEW NODE
		ptr0 = new Node(pq.back());
		pq.pop_back();
		ptr1 = new Node(pq.back());
		pq.pop_back();

		current = new Node(getNode(ptr0, ptr1));
		//ADD NEW NODE BACK INTO PQ
		pq.push_back(*current);
		//RESORT INCLUDING NEW NODE
		sort(pq.begin(), pq.end(), freq_sort);
	}

	return *current;
}

void decodePQ(string code[], string s, Node *current) {
	//IF CHAR IS PRESENT THEN SET STRING TO CODE[CHAR]
	if (current->c != '\0') code[current->c] = s;
	//ELSE SIFT THROUGH TREE WHILE BUILDING STRING
	else {
		decodePQ(code, s + "0", current->ptr0);
		decodePQ(code, s + "1", current->ptr1);
	}
}

bool freq_sort(const Node & a, const Node & b) { return a.frequency > b.frequency; }


bool die(const string & msg) {
	cout << "Fatal error: " << msg << endl;
	exit(EXIT_FAILURE);
}

*/
