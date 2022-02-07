#pragma once
#include <stdio.h>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

void printGrid(vector<vector<int>> arr, int part, ofstream& myfile, int point);


void checkForLink(int row, int col, int oldrow, int oldcol, int type, int& linkCount, vector<string>& found, vector<vector<int>> grid);

vector<string> splitString(string str);

vector<int> splitStringToINT(string str);

void blowUpBalloons(int row, int col, int& point, vector<vector<int>>& grid);

void part1(ofstream& myfile, string inputfile);

void part2(ofstream& myfile, string inputfile);