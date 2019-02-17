//  532_hw1_smyth.cpp
//
//  Smyth, Ravela
//  CS532 Homework #1 "Huffman Trees"

#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <algorithm>
#include <vector>
using namespace std;

struct Node {
    Node *ptr0, *ptr1;
    char c = '\0';
    unsigned long long frequency;
};

void getFreq(unsigned long long freq[256], const string & fileName);
void huffman(string code[256], const unsigned long long freq[256]);
Node getNode (Node * ptr0, Node * ptr1);
vector<Node> freqToPQ(const unsigned long long freq[256]);
Node buildTree(vector<Node> pq);
void decodePQ(string code[], string s, Node *current);
bool freq_sort(const Node & a, const Node & b);
bool die(const string & msg);

int main(int argc, const char * argv[]) {
    unsigned long long freq[256];
    string code[256];
    
    getFreq(freq, "input.txt");
    huffman(code, freq);
    
    //OUTPUT CODE[256]
    for (int i = 0 ; i < 256; i++)
        if (code[i] != "" ) cout << "'"<< (char)i << "' (" << freq[i] << ") : " << code[i] << "\n";
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

void huffman(string code[256], const unsigned long long freq[256]) {
    
    // FREQUENCY TO SORTED PQ
    vector<Node> pq = freqToPQ(freq);
    
    // BUILD TREE (0 - small, 1 -large
    Node *head = new Node( buildTree(pq));

    
    // DECODE TO CHAR
    fill(code, code+256, "");
    decodePQ(code, "", head);
    
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
INPUT.TXT::
Lorem ipsum dolor sit amet, feugiat auctor in, lacus vel ipsam quisque elit et porttitor, nulla amet, porta massa mauris. Aenean sagittis elit aliquet, purus maecenas iaculis, in erat vivamus cras, luctus egestas tristique bibendum, orci tortor vel justo nunc eu. Ut cras ac magna molestie dictum, sit egestas aliquam donec duis sodales. Deserunt lorem luctus dolor consectetuer, porta aptent at, pretium ipsum, quam lacus sed tempus et integer, vulputate nunc magna erat. Blandit semper tortor cursus lacinia at ligula. Ligula adipiscing, odio non luctus dolor arcu ligula at, molestie neque vestibulum. Id urna et dapibus, leo suscipit diam sit. Donec a massa aenean faucibus justo eu, justo suspendisse velit dictumst viverra, pharetra integer vehicula ut. Magna nulla velit magna, mauris mauris quisque turpis vivamus, in mattis sed placerat ac explicabo.

Amet eius justo integer donec molestie. Nam adipiscing sodales, placerat potenti sed, non maecenas consequat dui amet magna neque, egestas nullam ac morbi purus ligula, ornare mus suspendisse sed tortor sodales. Nunc ipsum. Id mollis ut tellus mauris vivamus sapien, quis quam tempor. Pellentesque nullam at adipiscing id, egestas urna sed duis est nec, massa consequat, duis nullam lectus. Habitant sociosqu hac dignissim, nulla elit quis, ultricies mauris urna eros viverra. Risus in scelerisque quam ultricies. Bibendum quia purus risus erat at, id tortor, ligula risus eget vestibulum velit purus, vitae sapien donec nulla quis lectus ornare, eu pellentesque. Sem nullam, rhoncus magna ullamcorper sem in morbi, lorem phasellus scelerisque neque, dui felis augue leo a amet. Ligula sed, cras velit vel dis odio. Fusce ac libero egestas mauris expedita, at turpis blandit accumsan quisque tellus, ultricies commodo porttitor posuere erat. Nunc mollis.

OUTPUT:: 
'
' (2) : 0110111101
' ' (272) : 101
',' (40) : 00101
'.' (21) : 010001
'A' (2) : 0110111001
'B' (2) : 0110111110
'D' (2) : 0110111111
'F' (1) : 01101110110
'H' (1) : 01101110111
'I' (2) : 0110111100
'L' (3) : 010000101
'M' (1) : 01101110100
'N' (3) : 010000100
'P' (1) : 01101110101
'R' (1) : 01000011010
'S' (1) : 01000011011
'U' (1) : 0100001100
'a' (139) : 1101
'b' (13) : 0110110
'c' (59) : 10000
'd' (43) : 01001
'e' (159) : 000
'f' (3) : 010000111
'g' (28) : 011010
'h' (5) : 01000001
'i' (131) : 1001
'j' (4) : 01000000
'l' (92) : 0101
'm' (67) : 10001
'n' (75) : 11101
'o' (69) : 11100
'p' (39) : 00100
'q' (26) : 011001
'r' (82) : 0011
's' (147) : 1111
't' (116) : 0111
'u' (138) : 1100
'v' (22) : 011000
'x' (2) : 0110111000
*/
