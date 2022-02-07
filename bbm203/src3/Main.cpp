#pragma warning ( disable : 4018 )

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>


using namespace std;

struct node {
    string currState;
    string input;
    string pop;
    string nextState;
    string push;
};

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

void pop_front(vector<string>& v) // pop from front of queue
{
    if (v.size() > 0) {
        v.erase(v.begin());
    }
} 

bool contains(vector<string> vec, string elem) // check if vector contains item
{
    char p[sizeof(elem)];
    for (int i = 0; i < sizeof(p); i++) {
        p[i] = elem[i];
    }

    return std::find(vec.begin(), vec.end(), p) != vec.end();
}

void popAndPush(vector<string>& stack,string pop, string push) { // pop or push to stack
    if (!(push == "e"))
    {
        stack.push_back(push);
    }
    if (!(pop == "e"))
    {
        stack.pop_back();
    }
}

void writeToFile(node nod, vector<string> vect  , string& outString) { // write to file
    outString += nod.currState + "," + nod.input + "," + nod.pop + " => " + nod.nextState + "," + nod.push + " [STACK]:";

    for (int i = 0; i < vect.size(); i++) // print stack
    {
        outString += vect[i];
        if (!(i == vect.size() - 1))
        {
            outString += ",";
        }
        else {
            outString += "\n";
        }
    }
    if (vect.size() == 0)
    {
        outString += "\n";
    }
}

bool searchNode(vector<node>& nodes , vector<string>& stack, string &currState , string input, string& outString) { 
    // find node in nodes and return false if input is == e
    for (int i = 0; i < nodes.size(); i++)
    {
        if (nodes[i].currState == currState) // compare current state
        {
            if (nodes[i].input == input || nodes[i].input == "e") // compare input
            {
                bool isPopAble = false; // if input != e than pop it
                if (contains(stack,nodes[i].pop) || nodes[i].pop == "e") // check for if output include item that is going to be popped
                {
                    popAndPush(stack, nodes[i].pop, nodes[i].push);
                    writeToFile(nodes[i], stack, outString);
                    isPopAble = true;
                    currState = nodes[i].nextState; // change current state
                }
                if (nodes[i].input == "e")
                {
                    return false;
                }
                if (isPopAble)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

string clearString(string str,char a, char b) { // delete specific char from string
    str.erase(remove(str.begin(), str.end(), a), str.end());
    str.erase(remove(str.begin(), str.end(), b), str.end());
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    return str;
}

int main(int argc, char** argv)
{
    //cout << argv[0] << "   " << argv[1] << argv[2] <<argv[3];
    string outputfile = argv[3];//3
    string outString = "";
    ofstream outFile;

    ifstream inputFile;
    string dpdaFile = argv[1];//1
    string inpFile = argv[2];//2

    string data;
    string startState;
    string currentState;
    vector<string> allStates; // contain all states
    vector<string> finalStates; // contain final states
    vector<string> inputAlphabet; // contains input alphabet
    vector<string> stackAlphabet; // contains stack alphabet
    vector<node> nodes; // contains nodes
    vector<string> stack; // contain outputs
    
    



    inputFile.open(dpdaFile); // first file
    while (getline(inputFile, data)) { //read data from file and put into string
        vector<string> splitByColon = split(data, ':');
        string operationCode = splitByColon[0];
        
        if (operationCode == "Q")
        {
            vector<string> splitByArrow = split(splitByColon[1], '>');
            vector<string> everyState = split(splitByArrow[0], ','); // all states
            vector<string> sfStates = split(splitByArrow[1], ','); // start and final states
            for (int i = 0; i < sfStates.size(); i++)
            {
                if (sfStates[i].find('(') != std::string::npos) {
                    startState = clearString(sfStates[i],'(',')'); // delete unnecessary strings
                }
                else if (sfStates[i].find('[') != std::string::npos) {
                    finalStates.push_back(clearString(sfStates[i], '[', ']')); // push final states
                }
            }
            for (int i = 0; i < everyState.size(); i++)
            {
                allStates.push_back(clearString(everyState[i],'=',' ')); // push all states
            }
        }
        else if (operationCode == "A") {
            vector<string> letters = split(splitByColon[1], ','); // elements of input alphabet
            for (int i = 0; i < letters.size(); i++)
            {
                inputAlphabet.push_back(letters[i]);
            }
        }
        else if (operationCode == "Z") {
            vector<string> letters = split(splitByColon[1], ','); // elements of output alphabet
            for (int i = 0; i < letters.size(); i++)
            {
                stackAlphabet.push_back(letters[i]);
            }
        }
        else { // T
            vector<string> vect = split(splitByColon[1], ','); // statements elements
            bool isValid = false; // check if statement is valid
            if (contains(allStates, vect[0])) // compare current state if valid
            {
                if (contains(inputAlphabet, vect[1]) || vect[1] == "e") // compare input if valid
                {
                    if (contains(stackAlphabet, vect[2]) || vect[2] == "e") // compare pop if valid
                    {
                        if (contains(allStates, vect[3])) // compare next state if valid
                        {
                            if (contains(stackAlphabet, vect[4]) || vect[4] == "e") // compare push if valid
                            {
                                isValid = true;
                            }
                        }
                    }
                }
            }
            if (isValid) // if statement is valid then create new node
            {
                nodes.push_back(node{ vect[0],vect[1],vect[2],vect[3],vect[4]});
            }
            else {
                outString += "Error [1]:DPDA description is invalid!"; // invalid statement
                outFile.open(outputfile);
                outFile << outString;
                outFile.close();
                exit(0);
            }
        }
    }
    inputFile.close();
    inputFile.open(inpFile); // input file
    while (getline(inputFile, data)) {
        currentState = startState;
        vector<string> inputQueue = split(data, ',');
        if (inputQueue.empty()) // check if there is no input then end statement
        {
            if (contains(finalStates, currentState)) {
                outString += "ACCEPT\n\n";
                continue;
            }
            else {
                outString += "REJECT\n\n";
                continue;
            }
            
        }
        int count = 0; // if stuck in loop helps to end statement
        bool isFinished = false; // if stuck in loop helps to end statement
        while (!inputQueue.empty()) // loop over inputs
        {
            count++;
            if (searchNode(nodes, stack, currentState, inputQueue[0],outString)) // if input is different than e , pop input
            {
                pop_front(inputQueue);
            }
            if (count >= 50) // if stuck in loop end statement
            {
                isFinished = true;
                break;
            }
        }
        if (!isFinished)
        {
            searchNode(nodes, stack, currentState, "e", outString); // check for if final state have e connection
            if (contains(finalStates, currentState)) // if last state is one of final states then accept else reject
            {
                outString += "ACCEPT\n\n";
            }
            else {
                outString += "REJECT\n\n";
            }
        }
        else // if stuck in loop and can not finish input string than reject
            outString += "REJECT\n\n";
        inputQueue.clear(); // clear both inputs and outputs
        stack.clear();
    }
    inputFile.close();

    outFile.open(outputfile);
    outFile << outString;
    outFile.close();
}


