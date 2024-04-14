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
double version = 1.0;
string starting_root = "V:\\";
char ending_root = '>';

class Dos {
	friend class File;
	friend class Tree;
	friend class Folder;

private:
    Tree T;
    Folder F;
    NotePad np;
    File file;
    string command;
    File* copiedFile;

public:
    Folder* FD;
    Dos()
    {
        command = "";
    }
    void color(int k)
    {
        if (k > 255)
        {
            k = 1;
        }
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, k);
    }

    void profile()
    {
        Folder *FD;
        FD->storeVersion(version + 0.1);
        FD->gotoxy(0, 72);
        color(9);
        cout << "Muhammad Ahmar Shahid    "
            << "2022-CS-206\n";
    }
    bool IsMakeDirectory()
    {
        string ChangedDirectory = command.substr(0, 5);
        if (ChangedDirectory == "mkdir")
        {
            string File_Name = command.substr(6, command.length());
            T.CurrentFolder->SubFolderInsertion(File_Name);
            return true;
        }
        return false;
    }

    bool IsPrintDirectory()
    {
        if (command == "dir")
        {
            T.CurrentFolder->PrintFolders();
            T.CurrentFolder->PrintFiles();
            return true;            
        }
        return false;
    }

    bool IsChangeDirectory()
    {
        string ChangeDirectory = command.substr(0, 2);
        if (ChangeDirectory == "cd")
        {
            ChangeDirectory = command.substr(3, command.length());
            Folder* F = T.CurrentFolder->Find_Folder(ChangeDirectory);
            T.CurrentFolder = F;
            return true;
        }
        return false;
    }
    bool printTree()
    {
        if (command == "tree")
        {
            T.PrintTree();
            return true;
        }
        return false;
    }

    bool printVersion()
    {
        if (command == "ver")
        {
            cout << "Version is: " << version;
            return true;
        }
        return false;
    }
    bool IsClearScreen()
    {
        if (command == "cls")
        {
            system("cls");
            FD->gotoxy(0, 72);
            color(4);
            cout << "Muhammad Ahmar Shahid"
                << " | "
                << "2022-CS-206\n";
            return true;
        }
        return false;
    }

    bool IsGoToParent()
    {
        if (command == "cd..")
        {
            T.CurrentFolder = T.root;
            return true;
        }
        return false;
    }
    bool IsCreateFile()
    {
        string CreateFile = command.substr(0, 6);
        if (CreateFile == "create")
        {
            CreateFile = command.substr(7, command.length());
            T.CurrentFolder->SubFilesInsertion(CreateFile);
            np.NotePadFiles.push_back(T.CurrentFolder->Files.back()->CF);
            return true;
        }
        return false;
    }

    bool IsGotoRoot()
    {
        if (command == "cd\\")
        {
            T.CurrentFolder = T.CurrentFolder->parent;
            return true;
        }
        return false;
    }
    bool IsEditFile()
    {
        string name = command.substr(0, 4);
        if (name == "edit")
        {
            name = command.substr(5, command.length());
            if (T.CurrentFolder->findFile(name))
                file.navigateAndEditFile(name + ".txt");
            else
                cout << "dfs";
            return true;
        }
        return false;
    }
    bool IsExit()
    {
        if (command == "exit")
        {
            np.deleteAllFiles();
        }
        return false;
    }

    bool SaveTree()
    {
        if (command == "save")
        {
            T.SavingTreetoSYS();
            return true;
        }
        return false;
    }
    bool isLoadTree()
    {
        if (command == "load")
        {
            T.loadTree();
            return true;
        }
        return false;
    }
    bool isRemoveFile()
    {
        string name = command.substr(0, 3);
        if (name == "del")
        {
            string namee = command.substr(4, command.length());
            T.CurrentFolder->RemoveSubFile(namee);
            return true;
        }
        return false;
    }

    bool isRemoveFile()
    {
        string name = command.substr(0, 3);
        if (name == "del")
        {
            string namee = command.substr(4, command.length());
            T.CurrentFolder->RemoveSubFile(namee);
            return true;
        }
        return false;
    }
    bool isFindFile()
    {
        string name = command.substr(0, 4);
        if (name == "search")
        {
            name = command.substr(5, command.length());
            File* foundFile = T.CurrentFolder->Find_File(name);
            if (foundFile != nullptr)
            {
                cout << "Found: " << foundFile->Name << endl;
            }
            else
            {
                cout << "Not found" << endl;
            }
            return true;
        }
        return false;
    }

    void ToLower()
    {
        for (int ri = 0; ri < command.size(); ri++)
        {
            if (65 <= command[ri] && command[ri] <= 90)
            {
                command[ri] = command[ri] + 32;
            }
        }
    }
    bool isDeleteDirectory()
    {
        string name = command.substr(0, 5);
        if (name == "rmdir")
        {
            T.CurrentFolder->DeleteFolder();
            T.CurrentFolder = T.root;
            cout << "Deleted";
            return true;
        }
        return false;
    }
    bool isCopy()
    {
        string name = command.substr(0, 4);
        if (name == "copy")
        {
            string namee = command.substr(5, command.length());
            copiedFile = T.CurrentFolder->Find_File(namee);
            if (copiedFile == nullptr)
            {
                cout << "File not found";
                return false;
            }
            else
            {
                cout << "File copied" << endl;
                return true;
            }
        }
        return false;
    }
    bool isMove()
    {
        string name = command.substr(0, 4);
        if (name == "move")
        {
            string namee = command.substr(5, command.length());
            copiedFile = T.CurrentFolder->Find_File(namee);
            if (copiedFile == nullptr)
            {
                cout << "File not found";
                return false;
            }
            else
            {
                cout << "File deleted from here" << endl;
                T.CurrentFolder->RemoveSubFile(namee);
                return true;
            }
        }
        return false;
    }

    bool paste()
    {
        if (command == "paste")
        {
            T.CurrentFolder->SubFilesInsertion((*copiedFile).Name);
            np.NotePadFiles.push_back(T.CurrentFolder->Files.back()->CF);
        }
    }
    bool isFormatDirectory()
    {
        if (command == "format")
        {
            string namee = T.CurrentFolder->name;
            cout << namee;
            Folder* foundFolder = T.CurrentFolder->parent;
            if (foundFolder)
            {
                foundFolder->RemoveSubFolder(namee);
                T.CurrentFolder = foundFolder;
            }
            else
            {
                cout << "Such directory don't exist";
            }
        }
    }
    bool isChangeExtension()
    {
        string extension1, extension2;
        if (command == "convert")
        {
            cout << "Enter first extension: ";
            cin >> extension1;
            extension1 = "." + extension1;
            cout << "Enter second extension: ";
            cin >> extension2;
            extension2 = "." + extension2;
            T.CurrentFolder->Extension_Changer(extension1, extension2);
            return true;
        }
        return false;
    }

    bool isHelp()
    {
        if (command == "help")
        {
            F.Help();
            cout << "Enter any key to enter doss";
            getch();
            system("cls");
            cout << endl;
            InputCommand();
        }
        return false;
    }
    bool isPrintPWD()
    {
        if (command == "pwd")
        {
            cout << "Current working directory is: " << T.CurrentFolder->name;
            return true;
        }
        return false;
    }
    bool isRename()
    {
        string re;
        string name = command.substr(0, 6);
        if (name == "rename")
        {
            name = command.substr(7, command.length());
            cout << "Enter new name of file: ";
            cin >> re;
            if (T.CurrentFolder->findFile(name))
            {
               // T.CurrentFolder->renameFile(name, re);
                return true;
            }
            else
                cout << "Such file don't exist";
        }
        return false;
    }

    bool isPrompt()
    {
        char sym;
        if (command == "prompt")
        {
            cout << "Enter a sybmbol for prompt: ";
            cin >> sym;
            F.ChangePrompt(sym);
            system("cls");
            InputCommand();
        }
    }
    bool isSearchInFile()
    {
        string s_name, f_name;
        if (command == "findf")
        {
            cout << "Enter the string you want to seach: ";
            getline(cin, s_name);
            cout << "Enter the name of file in which you want to search: ";
            cin >> f_name;
            if (file.searchInFile(s_name, f_name + ".txt"))
            {
                cout << "String found";
                return true;
            }
            else
                return false;
        }
        return false;
    }

    bool isSearchInAllFiles()
    {
        string s_name;
        if (command == "findstr")
        {
            cout << "Enter the string you want to search: ";
            getline(cin, s_name);
            for (auto file : T.CurrentFolder->Files)
            {
                if (file->searchInFile(s_name, file->Name + file->extension))
                {
                    cout << "String found in file: " << file->Name << file->extension << endl;
                    return true;
                }
            }
            cout << "String not found in any file in the current directory." << endl;
            return false;
        }

        return false;
    }
    bool isAddtoPriorityQueue()
    {
        string name = command.substr(0, 6);
        if (name == "pprint")
        {
            name = command.substr(7, command.length());
            T.CurrentFolder->AddtoPriorityQueue(name);
            return true;
        }
        return false;
    }
    bool isAddtoPrintQueue()
    {
        string name = command.substr(0, 5);
        if (name == "print")
        {
            name = command.substr(6, command.length());
            T.CurrentFolder->AddToPrintQueue(name);
            T.CurrentFolder->DisplayPrintQueue();
            return true;
        }
        return false;
    }

    bool isPrintQueue()
    {
        if (command == "pqueue")
        {
            T.CurrentFolder->PrintingPriorityQueueTime();
            return true;
        }
        return false;
    }
    bool isPrintQueue2()
    {
        if (command == "queue")
        {
            T.CurrentFolder->PrintingPriorityQueueTime();
            return true;
        }
        return false;
    }


    void InputCommand()
    {
        cout << T.CurrentFolder->path << ending_root;
        getline(cin, command);
        if (IsExit())
        {
        }
        else if (SaveTree())
        {
        }
        else if (IsCreateFile())
        {
        }
        else if (IsPrintDirectory())
        {
        }
        else if (IsMakeDirectory())
        {
        }
        else if (IsGotoRoot())
        {
        }
        else if (IsGoToParent())
        {
        }
        else if (IsChangeDirectory())
        {
        }
        else if (IsClearScreen())
        {
        }
        else if (IsEditFile())
        {
        }
        else if (printTree())
        {
        }
        else if (isRemoveFile())
        {
        }
        else if (isFindFile())
        {
        }
        else if (printVersion())
        {
        }
        else if (isDeleteDirectory())
        {
        }
        else if (isCopy())
        {
        }
        else if (isMove())
        {
        }
        else if (paste())
        {
        }
        else if (isFormatDirectory())
        {
        }
        else if (isChangeExtension())
        {
        }
        else if (isHelp())
        {
        }
        else if (isPrintPWD())
        {
        }
        else if (isRename())
        {
        }
        else if (isPrompt())
        {
        }
        else if (isSearchInFile())
        {
        }
        else if (isSearchInAllFiles())
        {
        }
        else if (isAddtoPriorityQueue())
        {
        }
        else if (isAddtoPrintQueue())
        {
        }
        else if (isPrintQueue())
        {
        }
        else if (isPrintQueue2())
        {
        }
        else if (isLoadTree())
        {
        }
        cout << endl;
    }


};