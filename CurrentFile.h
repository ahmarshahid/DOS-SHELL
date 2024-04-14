#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <iomanip>
#include <list>
#include <wtypes.h>
#include <stack>
#include <queue>
#include <vector>

using namespace std;

class CurrentFile
{
	friend class Dos;
	friend class Notepad;
	friend class Folder;
	friend class File;

public:
    int currentRow, currentCol;
    string name;
    int size = 0;
    list<list<char>> text;
    list<char>::iterator c;
    list<list<char>>::iterator r;

public:
    CurrentFile(){}
    CurrentFile(string _name)
    {
        currentRow = 0;
        currentCol = 0;
        name = _name;
        text.push_back(list<char>());
        r = text.begin();
        (*r).push_back(' ');
        c = (*r).begin();
    }

};
