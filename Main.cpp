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
#include "CurrentFile.h"
#include "Dos.h"
#include "File.h"
#include "Folder.h"
#include "Notepad.h"
#include "Tree.h"
using namespace std;



int main()
{
	Folder FD;
	FD.loadVersion();
	system("cls");
	Dos D;
	Tree T;
	D.profile();
	while (true)
	{
		D.InputCommand();
	}
}



