//  532_le4_smyth.cpp
//
//  Smyth, Ravela
//  CS532 Lab Exercise #4 "vectors, iterators, sort, count"


#include <iostream>
#include <vector>
#include <algorithm>
#include <string> 
using namespace std;

ostream & operator<<(ostream & out, const vector<int> & v);
ostream & operator<<(ostream & out, const vector<string> & v);
ostream & operator<<(ostream & out, const vector<vector<int>> & v);
void g(vector<int> & v, int sought); 

int main() {
	vector<string> a; 
	a.push_back("hello"); a.push_back("my"); a.push_back("name");
	vector<int> b {8,4,6,1};
	cout << a; 
	cout <<vector<vector<int>>{{1,2},{3,4},{5,6,7}};
	g(b, 2);
}

ostream & operator<<(ostream & out, const vector<int> & v){
	for(int n: v)
		out <<"  " <<n;
	return out <<endl;
}



ostream & operator<<(ostream & out, const vector<string> & v){
	for(string a : v)
		out <<a<<" ";
	return out <<endl;
}

ostream & operator<<(ostream & out, const vector<vector<int>> & v){
	for(vector<int> a : v)
		out << a;
	return out <<endl;
}

void g(vector<int> & v, int sought) {

	cout << "\n'sought' appears " << count(v.begin(), v.end(), sought) << " times in 'v'"
	     << "\nAre all #s even? " << all_of(v.begin(), v.end(), [](int i){return !(i%2);})
	     << "\nAre any #s even? " << any_of(v.begin(), v.end(), [](int i){return !(i%2);})
	     << "\nForward sorting: "; 
	    sort(v.begin(), v.end());
	cout << v << "Backward sorting: ";
	    sort(v.begin(), v.end(), [](int i, int j){return i > j;});
	cout << v << "Double all values: ";
	    transform(v.begin(), v.end(), v.begin(), [](int i){return 2*i;}); 
	cout << v; 

}
