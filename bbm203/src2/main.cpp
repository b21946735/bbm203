#include <stdio.h>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include "dsa.h"

using namespace std;




void printGrid(vector<vector<int>> arr, int part, ofstream& myfile,int point) {

	if (part == 1)
	{
		myfile << "PART 1:\n";
	}
	else {
		myfile << "PART 2:\n";

	}

	for (int i = 0; i < arr.size(); i++)
	{
		for (int j = 0; j < arr[i].size(); j++)
		{
			myfile << arr[i][j] << " ";
		}
		myfile << "\n";
	}
	if (part == 1)
	{
		myfile << "\n";
	}
	else {
		myfile << "Final Point: " << point << "p";
	}

}

void checkForLink(int row, int col, int oldrow, int oldcol, int type, int& linkCount, vector<string>& found, vector<vector<int>> grid) {

	int rowLow = row - 1;  // check for upper and lower boundaries
	if (rowLow <= 0) rowLow = 0;
	int rowUp = row + 1;
	if (rowUp >= grid.size()) rowUp = grid.size() - 1;
	int colLow = col - 1;
	if (colLow <= 0) colLow = 0;
	int colUp = col + 1;
	if (colUp >= grid.size()) colUp = grid.size() - 1;

	linkCount++;
	int i = 0;
	int j = 0;
	for (i = rowLow; i <= rowUp; i++) // check for upside and downside of balloon
	{
		if (i == row || i == oldrow) { continue; }
		if (grid[i][col] == type)
		{
			found.push_back(to_string(i) + " " + to_string(col));
			checkForLink(i, col, row, col, type, linkCount, found, grid);
		}
	}
	for (j = colLow; j <= colUp; j++) // check for right and left side of balloon
	{
		if (j == col || j == oldcol) { continue; }
		if (grid[row][j] == type)
		{
			found.push_back(to_string(row) + " " + to_string(j));
			checkForLink(row, j, row, col, type, linkCount, found, grid);
		}
	}
}

vector<string> splitString(string str) { // split string
	istringstream iss(str);
	vector<string> result;
	for (string s; iss >> s;)
		result.push_back(s);
	return result;
}

vector<int> splitStringToINT(string str) { // split string
	istringstream iss(str);
	vector<int> result;
	for (string s; iss >> s;)
		result.push_back(stoi(s));
	return result;
}

void blowUpBalloons(int row, int col, int& point, vector<vector<int>>& grid) {
	int size = grid.size();
	int type = grid[row][col];
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (grid[i][j] == type && (i == row || j == col || i + j == row + col || i - j == row - col))
			{
				grid[i][j] = 0;
				point += type;
			}
		}
	}
}

void part1(ofstream& myfile, string inputfile) {
	ifstream input1TXT(inputfile);
	vector<string> commandspart1;
	string myText;
	getline(input1TXT, myText);
	int size = stoi(myText);
	while (getline(input1TXT, myText)) {
		commandspart1.push_back(myText);
	}

	int linkCount = 0;
	vector<string> found;
	int nonZeroCounter = 0; // non zero number counter for decrease link control
	vector<vector<int>> grid(size, vector<int>(size, 0)); // create 0 vector
	for (int command = 0; command < commandspart1.size(); command++)
	{
		nonZeroCounter++;
		vector<string> result = splitString(commandspart1[command]); // split command
		int row = stoi(result[1]);
		int column = stoi(result[2]);
		int type = stoi(result[0]);

		grid[row][column] = type;


		if (nonZeroCounter >= 3)
		{
			found.push_back(to_string(row) + " " + to_string(column));
			checkForLink(row, column, row, column, type, linkCount, found, grid);
		}
		while (linkCount >= 3)
		{
			int lastItemRow;
			int lastItemCol;
			for (int item = 0; item < found.size(); item++)
			{
				vector<string> result2 = splitString(found[item]);
				row = stoi(result2[0]);
				column = stoi(result2[1]);
				if (item == 0) {
					grid[row][column] = ++type;
					lastItemRow = row;
					lastItemCol = column;
				}
				else {
					grid[row][column] = 0;
				}
			}
			linkCount = 0;
			nonZeroCounter -= found.size() - 1;
			found.clear();
			if (nonZeroCounter >= 3) {
				found.push_back(to_string(lastItemRow) + " " + to_string(lastItemCol));
				checkForLink(lastItemRow, lastItemCol, lastItemRow, lastItemCol, type, linkCount, found, grid);
			}
		}
		found.clear();
		linkCount = 0;



	}

	printGrid(grid, 1, myfile,0);
}

void part2(ofstream& myfile, string inputfile) {
	ifstream input2TXT(inputfile);
	string myText;
	getline(input2TXT, myText);
	int size = stoi(myText);
	int point = 0;
	vector<string> commands;
	vector<vector<int>> grid;
	for (int i = 0; i < size; i++)// get grid from file
	{
		getline(input2TXT, myText);
		grid.push_back(splitStringToINT(myText));
	}
	while (getline(input2TXT, myText)) {
		commands.push_back(myText);
	}
	for (int j = 0; j < commands.size(); j++)
	{
		vector<string> command = splitString(commands[j]);
		int row = stoi(command[0]);
		int col = stoi(command[1]);
		blowUpBalloons(row, col, point, grid);
	}
	input2TXT.close();
	printGrid(grid, 2, myfile, point);

}

int main(int argc, char** argv) {

	string inputfile1 = argv[1];
	string inputfile2 = argv[2];
	string outputfile = argv[3];

	ofstream myfile;
	myfile.open(outputfile);
	part1(myfile, inputfile1);
	part2(myfile, inputfile2);
	myfile.close();
}