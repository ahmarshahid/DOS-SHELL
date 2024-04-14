#pragma once
#include <iostream>
#include <list>
#include <string>
#include <iostream>
#include <ctime>
#include <vector>
#include <wtypes.h>
#include <iomanip>
#include "File.h"
#include "Dos.h";

double version = 1.0;
string starting_root = "V:\\";
char ending_root = '>';
using namespace std;

class Tree
{
	friend class Dos;
	friend class Folder;

private:
	void PrintTree(Folder* CurrentFolder, int depthOfTree)
	{
		if (CurrentFolder == nullptr)
		{
			return;
		}
		cout << setw(depthOfTree * 4) << "" << CurrentFolder->name;
		for (auto subfolder : CurrentFolder->Folders)
		{
			PrintTree(subfolder, depthOfTree + 1);
		}
		for (auto file : CurrentFolder->Files)
		{
			cout << setw((depthOfTree + 1) * 4) << "" << file->Name << file->extension << endl;
		}
	}

public:
	Folder* root;
	Folder* CurrentFolder;
	Tree()
	{
		root = CurrentFolder;
		CurrentFolder = new Folder("V:", nullptr, starting_root);
		CurrentFolder->SubFolderInsertion("LUMS");
		Folder* MyFolder = CurrentFolder->Folders.front();
		MyFolder->SubFolderInsertion("Computer Sciences");
		MyFolder->SubFolderInsertion("Information Technology");
		MyFolder->SubFolderInsertion("Software Engineering");
		MyFolder->SubFolderInsertion("Data Science");
	}

	void PrintTree()
	{
		PrintTree(root, 0);
	}

	void saveTreeToFile(Folder* currentFolder, ofstream& outFile)
	{
		if (currentFolder == nullptr)
			return;

		outFile << currentFolder->name << endl;

		for (auto subfolder : currentFolder->Folders)
		{
			saveTreeToFile(subfolder, outFile);
		}

		for (auto file : currentFolder->Files)
		{
			outFile << file->Name << file->extension << endl;
		}
	}

	void loadTreeFromFile(Folder* parentFolder, ifstream& inFile)
	{
		while (!inFile.eof())
		{
			string entry;
			getline(inFile, entry);

			if (entry.empty())
				break;

			if (entry.find("Dir") != string::npos)
			{
				// It's a subfolder
				string folderName = entry.substr(3);
				Folder* subFolder = new Folder(folderName, parentFolder, parentFolder->path + "\\" + folderName);
				parentFolder->Folders.push_back(subFolder);
				loadTreeFromFile(subFolder, inFile);
			}
			else
			{
				// It's a file
				File* newFile = new File(entry, time(0));
				parentFolder->Files.push_back(newFile);
			}
		}
	}

	void SavingTreetoSYS()
	{
		ofstream outFile("Tree.txt");
		saveTreeToFile(root, outFile);
		outFile.close();

	}

	void loadTree()
	{
		ifstream inFile("Tree.txt");
		loadTreeFromFile(root, inFile);
		inFile.close();
	}
};