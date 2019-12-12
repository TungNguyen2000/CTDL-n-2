#pragma once
#include<iostream>
#include"compressfile.h"
#include"compressfolder.h"
#include <Windows.h>
#include<conio.h> 

using namespace std;

/*cau hinh cho app */
int App();
void gotoxy(int x, int y);
int Intro();
int BangChon(int chon, int choncu);
void filecompression();