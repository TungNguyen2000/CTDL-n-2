#pragma once
#include "Node.h"
#include "entry.h"
#include<sstream>


using namespace std;

string ChartoBinaryString(int c);


char GetaChar(string &s);


void AnalysisFile(string filename);

Node* CreateTree();

void SortNodeArr();

void createNodeArr();

void readFile(string filename);

void Decompress(string  filename);

int findinNodeArr(char c);

void ExportEncodeFile(string filename, string fileoutname);

void EncodeNode(Node* p);

int BintoDec(int n);

void ReCreateNodeArr(Node* p, int flag = 0);

