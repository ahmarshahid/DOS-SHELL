#pragma once
#include <list>
#include <string>
#include <iostream>
#include <ctime>
#include <vector>
#include <wtypes.h>
#include <iomanip>
#include "File.h"
#include "Dos.h";
#include "Tree.h"
double version = 1.0;
string starting_root = "V:\\";
char ending_root = '>';
using namespace std;

class Folder
{
	friend class File;
	friend class Tree;
	friend class Dos;
public:
	string name;
	string Extension;
	vector<Folder*> Folders;
	vector<File*>Files  ;
	Folder* parent;
	time_t Production_Time;
	string Time;
	string owner;
	bool hidden;
public:
	list <string> pQueue;
	list<string> PrintQueue;
	string path;

	Folder(string Name = "Null", Folder* Parent = nullptr,  string Path = "", vector<Folder*> fs = vector<Folder*>(), vector<File*> FS = vector<File*>() ,bool _Hidden = false, time_t _Creation_Time = time(0))
	{
		name = Name; //
		Folders = fs; //
		Files = FS;//
		hidden = _Hidden;//
		path = Path;//
		parent = Parent;//
		Production_Time = _Creation_Time;
		Time = ctime(&Production_Time);
		ConvertTime(Time);
		
	}
	void ConvertTime(string& Time)
	{
		string Day_Night = "";
		string Date = Time.substr(8, 2);
		string Month = Time.substr(4, 3);
		string Day = Time.substr(0, 3);
		string Hour = Time.substr(11, 2);
		int Hours = stoi(Hour);
		tm timestruct = {};

		if (Hours > 12)
		{
			Hours = Hours - 12;
			Day_Night = "PM";
		}
		else
		{
			Day_Night = "AM";
		}
		Hour = to_string(Hours);
		string Minute = Time.substr(14, 2);
		string Seconds = Time.substr(17, 2);
		string Year = Time.substr(20, 4);
		Time = "";
		Time = Month + " " + Date + " " + Hour + ":" + Seconds + " " + Day_Night;

	}
	void storeVersion(double version)
	{
		fstream gross;
		gross.open("Version.txt", ios::out);
		gross << version << endl;
		gross.close();
	}
	double parsItem(string itemName, int itemRate)
	{
		int commaCount = 1;
		string item = "";
		for (int x = 0; x < itemName.length(); x++)
		{
			if (itemName[x] == ',')
			{
				if (itemName[x] == ',')
				{
					commaCount = commaCount + 1;
				}
				else if (commaCount == itemRate)
				{
					item = item + itemName[x];
				}
			}
		}
		return stod(item);

	}
	void loadVersion()
	{
		fstream gross;
		string word;
		gross.open("version.txt", ios::in);
		while (!gross.eof())
		{
			getline(gross, word);
			if (word == "")
				break;
			version = parsItem(word, 1);
		}
		gross.close();
	}

	void gotoxy(int x, int y)
	{
		COORD scrn;
		HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
		scrn.X = y;
		scrn.Y = x;
		SetConsoleCursorPosition(hOuput, scrn);
	}


	void SubFolderInsertion(string _name)
	{
		string alpha;
		if (name != "V:")
		{
			alpha = "\\";
		}
		Folder* insertion = new Folder(name, this, path + alpha + name);
		Folders.push_back(insertion);
	}

	void SubFilesInsertion(string name)
	{
		File* insertion = new File(name);
		Files.push_back(insertion);
	}

	void RemoveSubFile(string Name)
	{
		for (int i = 0; i < Files.size(); i++)
		{
			if (Files[i]->Name == Name)
			{
				swap(Files[i], Files[Files.size() - 1]);
				Files.pop_back();
			}
		}
	}
	void RemoveSubFolder(string Name)
	{
		for (int i = 0; i < Folders.size(); i++)
		{
			if (Files[i]->Name == Name)
			{
				swap(Folders[i], Folders[Folders.size() - 1]);
				Folders.pop_back();
			}
		}
	}

	void PrintFiles()
	{
		vector<File*> ::iterator x;
		for (x = Files.begin(); x != Files.end(); x++)
		{
			cout << left << setw(31) << (*x)->Time << " <FILE> " << (*x)->Name << (*x)->extension << endl; 
			
		}
	}

	void PrintFolders()
	{
		vector <Folder *>::iterator i;
		cout << "Directory of " << name << "is:\n\n";
		for (i = Folders.begin(); i != Folders.end(); i++)
		{
			cout << left << setw(30) << (*i)->Time << " <DIR> " << (*i)->name << endl ;
		}
	}

	Folder* Find_Folder(string _name)
	{
		vector<Folder*> ::iterator x;
		for (x = Folders.begin(); x != Folders.end(); x++)
		{
			if ((*x)->name == _name)
				return (*x);
		}
	}

	File* Find_File(string _Name)
	{
		vector<File*> ::iterator i;
		for (i = Files.begin(); i != Files.end(); i++)
		{
			if ((*i)->Name == _Name)
			{
				return (*i);
			}
		}
		return nullptr;
	}

	bool findFile(string _name)
	{
		vector<File*> ::iterator i;
		for (i = Files.begin(); i != Files.end(); i++)
		{
			if ((*i)->Name == _name)
			{
				return true;
			}
		}
		return false;
	}

	void DeleteFolder(Folder* Root)
	{
		for (auto it = Folders.begin(); it != Folders.end();)
		{
			if (*it == Root)
			{
				(*it)->DeleteFolder();
				it = Folders.erase(it);
			}
			else
			{
				++it;
			}
		}
	}
	void DeleteFolder()
	{
		DeleteFolder(this);
	}

	void Extension_Changer(string Old_Extension, string New_Extension)
	{
		vector<File*> ::iterator x;
		for (x = Files.begin(); x != Files.end(); x++)
		{
			if ((*x)->extension == Old_Extension)
				(*x)->extension == New_Extension;
			else if ((*x)->extension == New_Extension)
				(*x)->extension = Old_Extension;
		}
	}

	void Help()
	{
		system("cls");
		cout << "Command" << endl << endl;
		cout << "Attrib" << "		"<<	" Displays file(name provided as input) attributes." << endl;
		cout << "CD      "
			<< "                "
			<< "Displays the name of or changes the current directory. See details below. " << endl;
		cout << "CD.     "
			<< "                "
			<< "Prints working directory (i.e. your current directory in your tree structure) " << endl;
		cout << "CD..    "
			<< "                "
			<< "Change directory to previous directory " << endl;
		cout << "CD\\    "
			<< "                "
			<< " Changes directory to root directory (i.e. V:\\>)" << endl;
		cout << "CONVERT "
			<< "                "
			<< "Asks two types and converts extension of all files of one type to another type." << endl;
		cout << "COPY    "
			<< "                "
			<< "Copies one file in the current directory to another location (directory). See details below." << endl;
		cout << "CREATE  "
			<< "                "
			<< "Creates a file with the name provided and allows the user to enter contents of the file." << endl;
		cout << "DEL     "
			<< "                "
			<< "Delete a file whose name is provided in input." << endl;
		cout << "DIR     "
			<< "                "
			<< "Displays a list of files and subdirectories in a directory." << endl;
		cout << "EDIT    "
			<< "                "
			<< "Opens a file (loads into a linked list) and allows the user to edit and save the contents of the file." << endl;
		cout << "EXIT    "
			<< "                "
			<< "Quits the program" << endl;
		cout << "FIND    "
			<< "                "
			<< "Searches for a file in your current virtual directory whose name is provided as input." << endl;
		cout << "FINDF   "
			<< "                "
			<< "Searches for a text string in the currently open file or the file whose name is provided as input." << endl;
		cout << "FINDSTR "
			<< "                "
			<< "Searches for strings in all files of your current virtual directory, prints names of files with the string" << endl;
		cout << "FORMAT  "
			<< "                "
			<< "Formats the current virtual directory i.e. empties the current directory and all subdirectories." << endl;
		cout << "HELP    "
			<< "                "
			<< "Provides Help information for all these commands." << endl;
		cout << "LOADTREE"
			<< "                "
			<< "Load a given tree in your tree structure. Given tree is in a file named tree.txt	" << endl;
		cout << "MKDIR   "
			<< "                "
			<< "Creates a virtual directory." << endl;
		cout << "MOVE    "
			<< "                "
			<< "Moves one file (whose name is provided as input) from one directory to another               directory." << endl;
		cout << "PPRINT  "
			<< "                "
			<< "Adds a text file to the priority based print queue, and displays the current priority queue. " << endl;
		cout << "PROMPT  "
			<< "                "
			<< "Changes the Windows command prompt (for example from V:\\> to V$)." << endl;
		cout << "PRINT   "
			<< "                "
			<< "Adds a text file to the print queue, and displays the current queue. " << endl;
		cout << "PQUEUE  "
			<< "                "
			<< "Shows current state of the priority based print queue, with time left for each element" << endl;
		cout << "PWD     "
			<< "                "
			<< "Prints working directory" << endl;
		cout << "QUEUE   "
			<< "                "
			<< "Shows current state of the print queue, with time left for each element" << endl;
		cout << "RENAME  "
			<< "                "
			<< "Renames a file whose current and new name is provided as input." << endl;
		cout << "RMDIR   "
			<< "                "
			<< "Removes a directory along with its contents. Consider setting the respective sibling links " << endl;
		cout << "SAVE    "
			<< "                "
			<< "Saves the currently open file to disk.TREE Displays the complete directory structure.VER Displays the version of your program." << endl;
		
	}

	/*void renameFile(string name, string rename)
	{
		list<File*>::iterator i;
		for (i = Files.begin(); i != Files.end(); i++)
		{
			if ((*i)->Name == name)
			{
				(*i)->Name = rename;
			}
		}
	}*/

	void AddToQueue(string name)
	{
		pQueue.push_back(name);
	}

	void displayQueue()
	{
		if (pQueue.empty())
		{
			cout << " Queue is Empty " << endl;
		}
		else
		{
			cout << "Printing Queue : " << endl;
			for (const auto& FileName : pQueue)
			{
				cout << FileName << endl;
			}
		}
	}

	void PrintingPriorityQueueTime()
	{
		if (pQueue.empty())
		{
			cout << "Priority Queue is Empty. " << endl;
		}
		else
		{
			cout << "Priority Queue with Time Left: " << endl;
			time_t currentTime = time(nullptr);
			for (const auto& FILENAME : pQueue)
			{
				// Random time left in seconds
				int timeLeft = rand() % 60;
			}
		}
	}

	void AddtoPriorityQueue(string filename)
	{
		if (findFile(filename))
		{
			AddToQueue(filename);
			displayQueue();
			cout << "File " << filename << "added to the priority Queue.\n";
		}
		else
		{
			cout << "File " << filename << "not found in the current directory.\n";
		}
	}

	void AddToPrintQueue(string filename)
	{
		PrintQueue.push_back(filename);
	}

	void DisplayPrintQueue()
	{
		if (PrintQueue.empty())
		{
			cout << "Print Queue is empty. " << endl;
		}
		else
		{
			cout << "Print Queue with Time Left:" << endl;
			time_t currentTime = time(nullptr);
			for (const auto& fileName : PrintQueue)
			{
				int timeLeft = rand() % 60;
				cout << fileName << " - Time Left: " << timeLeft << " seconds" << endl;
			}
		}
	}

	void ChangePrompt(char character)
	{
		ending_root = character;
	}
	void EmpDir()
	{
		Files.resize(0);
		Folders.resize(0);
	}

	
};
