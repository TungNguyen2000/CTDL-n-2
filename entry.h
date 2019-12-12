#pragma once
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<string>
#include<vector>
#include<Windows.h>

using namespace std;
struct entry
{
	string filename;
	entry();
	entry(const entry &in);
	entry(string in);
};

