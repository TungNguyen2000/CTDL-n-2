#pragma once
#include "entry.h"
#include "Node.h"
#include<sstream>
#include"compressfile.h"
#include<direct.h>

using namespace std;

string getfoldername(string path);

vector<entry> readfolder(string pathname);

void fo_SortNodeArr();

Node* folder_CreateTree();

void fo_createNodeArr();

void fo_readFile(ifstream &file);

int fo_findinNodeArr(char c);

void fo_ExportEncodeFile(ifstream &fin, ofstream &fout);

void fo_EncodeNode(Node* p);

void fo_ReCreateNodeArr(Node* p, int flag = 0);

void folder_decompression(string filein);
void compressfolder(string filename, string fileout);

