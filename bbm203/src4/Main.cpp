#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <string.h>
#define R 128

using namespace std;

vector<string> split(const string& s, char d) // split string
{
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, d))
    {
        tokens.push_back(token);
    }
    return tokens;
}

string convertToString(char* a, int size)
{
    int i;
    string s = "";
    for (i = 0; i < size; i++) {
        if ((int)a[i] > 0 && (int)a[i] < 129)
        {
            s = s + a[i];
        }
    }
    return s;
}

class Node
{
    public:
        string value;  // value
        vector<Node*> next;  // vector for store next nodes
        Node* prev;  // previous node
        Node() {
            next.reserve(R); // reserve R slot
            prev = NULL;
        }
};

Node* getNode() {  // create new node
    Node* pNode = new Node;
    if (pNode) {
        for (int i = 0; i < R; i++) {
            pNode->next.push_back(NULL);
        }
    }
    return pNode;
}

void insert(Node*& x, string key, string val, string &total,int d = 0)  // root ,  key , value, counter //insert new key to trie
{

    if (x == NULL || x->next.size() ==0) // if end of way add new node
        x = getNode();
    if (d == key.size()) { // if key added to trie
        if (x->value == val)
        {
            total += "\"" + key + "\"" + " already exist" + "\n";
            return;
        }
        else {
            if (x->value == "")
            {
                total += "\"" + key + "\"" + " was added" + "\n";
            }
            else {
                total += "\"" + key + "\"" + " was updated" + "\n";
            }
            x->value = val;
            return;
        }
        
    }
    char c = key[d];
    int a = (int)c;
    
    insert(x->next.at(a), key, val,total, d + 1); 

    if (x->next.at(a) != NULL)  // set prev node
    {
        x->next.at(a)->prev = x;
    }
}

string search(Node* x, string key,string& total, int d =0 ) // root , searching key , counter  // search for specific key and return value
{
    if (x == nullptr) {
        if (d == 1)
        {
            total += "\"no record\"\n" ;
        }else{
            total += "\"incorrect Dothraki word\"\n";
        }
        return ""; 
    }
   
    if (d == key.size())
    {
        if (x->value =="" )
        {
            total += "\"not enough Dothraki word\"\n";
        }
        else {
            total += "\"The English equivalent is " + x->value + "\"\n";
        }
        return x->value;
    }
        
    char c = key[d];
    return search(x->next.at((int)c), key,total, d + 1);
}

bool isParent(Node* node) {  // check if node in leaf
    if (node ==NULL)
    {
        return false;
    }
    for (int i = 0; i < R; i++)
    {
        if (node->next.at(i) !=NULL)
        {
            return true;
        }
    }
    return false;
}

void deleteWord(Node* node, string key, bool* startdelete ,string& total,unsigned int count =0) { // node , key , returnin back? , counter // delete specific key from trie
    if (node == NULL)
    {
        if (count == 1)
        {
            total += "\"no record\"\n" ;
        }
        else {
            total += "\"incorrect Dothraki word\"\n";
        }
        return;
    }
    if (count == key.size()&& node->value != "") // if end of key and have value return back
    {
        *startdelete = true;
    }

    char c = key[count];
    int d = (int)c;

    if (count < key.size())
    {
        deleteWord(node->next.at(d), key, startdelete, total,count + 1);

    }

    if (*startdelete && !isParent(node)) // delete node
    {
        node->prev->next.at(key[count-1]) = NULL;
        delete node;
        node = NULL;
        if (count == key.size()) {
            total += "\"" + key + "\" deletion is successful\n";
        }
    }
    else {
        if (count == key.size())
        {
            if (node->value == "") {
                total += "\"not enough Dothraki word\"\n";
            }
            else {
                total += "\"" + key + "\" deletion is successful\n"; //delete value not node
                node->value = "";
            }
        }
    }
}

int howManyNotNull(Node* x) {  // count of not null child nodes
    int count = 0;
    for (int i = 0; i < R; i++) {
        if (x->next.at(i) != NULL) {
            count++;
        }
    }
    return count;
}


void listAll(Node* node ,  char* str,int *tabcount ,string& total,int len = 0) { // list all keys and values
    bool write = true; // if have value but dont need to \tab then false
    char* newStr = new char[len+2];
    memcpy(newStr,str,len);
    if (*newStr != -51) // -51 invalid character 
    {
        if ( len ==1 ) // if current str len is 1 
        {
            if (howManyNotNull(node) > 1) { // if have more than 1 child node
                (*tabcount) = 0;
                if (str != NULL)
                {
                    total += "-" + convertToString(str, len) + "\n";
                }
                (*tabcount)++;
            }
            else {
                (*tabcount) = 0;
            }
        }
        else if (howManyNotNull(node) > 1) { // if have more than 1 child node and len is higher than 1
            if (len == 2)
            {
                if (*tabcount >= 2)
                {
                    (*tabcount)--;
                }
            }
            if (len == 3)
            {
                if (*tabcount >= 3)
                {
                    (*tabcount)--;
                }
            }
            if (node->value == "") // if dont have value print str 
            {
                for (int i = 0; i < *tabcount; i++) // 
                {
                    total += "\t";//
                }
                if (str != NULL)
                {
                    total += "-" + convertToString(str, len) + "\n";//
                }
            }
            else { // have value then print key value
                if (str != NULL)
                {
                    total += "-" + convertToString(str, len) + "(" + node->value + ")" + "\n";
                }
                write = false;
            }
            (*tabcount)++;
        }
        if (node->value != "") 
        {
            if (*tabcount >0 && write)
            {
                for (int i = 0; i < *tabcount; i++)
                {
                    total += "\t";
                }
            }
            if (write) // if key value is already printed then pass
            {
                if (str != NULL)
                {
                    total += "-" + convertToString(str, len) + "(" + node->value + ")" + "\n";
                }
            }
        }
    }
    for (int i = 0; i < R; i++) // go to next nodes
    {
        if (node->next.at(i) != NULL)
        {
            newStr[len] = i;
            listAll(node->next.at((int)i), newStr, tabcount,total,len + 1);
        }
    }
    delete[] newStr;

}

void list(Node* root,string& total) { // help to recurse listall function
    if (root ==NULL)
    {
        cout << "empty" <<endl;
        return;
    }
    int s = 0;
    listAll(root,NULL,&s,total,0);
}

int main(int argc, char** argv)
{
	string inputName = argv[1];
	string outName = argv[2];
    Node* root = new Node(); // initialize root
    ofstream outFile;
    ifstream inputFile;
    string data;
    string total;

    inputFile.open(inputName); // input file
    while (getline(inputFile, data)) { // read data from file and put into string
        if (data == "list") { // list command 
            list(root,total);
        }
        else {
            vector<string> vect = split(data,'(');
            string command = vect[0];
            if (command == "insert") // insert command
            {
                vector<string> vect2 = split(vect[1], ',');
                string dothrakiWord = vect2[0];
                vect2[1].pop_back();
                string engWord = vect2[1];
                insert(root, dothrakiWord, engWord,total);
            } 
            else if (command == "search"){ // search command
                vect[1].pop_back();
                search(root, vect[1],total);
            }
            else { // delete command 
                vect[1].pop_back();
                bool start =false;
                deleteWord(root,vect[1],&start,total);
            }
        }
    }

    inputFile.close();

    outFile.open(outName); // print to txt
    outFile << total;
    outFile.close();
}