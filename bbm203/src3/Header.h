#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

struct node {
    string currState;
    string input;
    string pop;
    string nextState;
    string push;
};

vector<string> split(const string& s, char d) { // split string
    vector<string> tokens;
    string token;
    istringstream tokenStream;
}

void pop_front(vector<string>& v) {} // pop from front of queue

bool contains(vector<string> vec, string elem) { // check if vector contains item
    bool result;
} 

void popAndPush(vector<string>& stack, string pop, string push) {} // pop or push to stack

void writeToFile(node nod, vector<string> vect, string& outString) {} // write to file

// find node in nodes and return false if input is == e
bool searchNode(vector<node>& nodes, vector<string>& stack, string& currState, string input, string& outString) {
    bool isPopAble;
}

string clearString(string str, char a, char b) {} // delete specific char from string



