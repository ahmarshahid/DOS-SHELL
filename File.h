#pragma once
#include <list>
#include <string>
#include <iostream>
#include <ctime>
#include <vector>
#include "Folder.h"
#include <conio.h>
#include "Notepad.h"
#include "CurrentFile.h"

class File
{
	friend class Folder;
	friend class Tree;
	friend class Dos;
    friend class CurrentFile;

public:
    string Name;
    time_t Creation_Time;
    string Path;
    string Time;

    CurrentFile* CF;
    string extension;
    bool Hidden;
    void creationOfFile()
    {
        ofstream FileCreator(Name + extension);
        if (FileCreator.is_open())
        {
            cout << "File Created";
            FileCreator.close();
        }
        else
            cout << "File not created";
    }
public:
    File(){}
    Folder FD;

    File(string _Name, time_t _Creation_Time = time(0), bool _Hiddden = false, string _Extension = ".txt")
    {
        Name = _Name;
        extension = _Extension;
        Creation_Time = _Creation_Time;
        Time = ctime(&Creation_Time);
        FD.ConvertTime(Time);
        Hidden = _Hiddden;
        creationOfFile();
    }

    void saveToFile(const string filename, const string& content)
    {
        ofstream file(filename);
        if (file.is_open())
        {
            file << content;
            file.close();
        }
        else
        {
            cout << "Unable to open file for saving: " << filename << "\n";
        }
    }
    void setCursorPosition(int x, int y, int color)
    {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    }

    int getArrowKey()
    {
        int ch = _getch();
        if (ch == 0 || ch == 0xE0)
        {
            return _getch();
        }
        else
        {
            return ch;
        }
    }

    void navigateAndEditFile(string fileName) // 
    {
        fstream file(fileName);
        if (!file.is_open())
        {
            cout << "File does not exist";
            return;
        }
        string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        file.close();
        int currentPosition = 0;
        int totalCols = 80;
        stack<string> undoStack;
        stack<string> redoStack;
        auto pushToUndoStack = [&undoStack](const string& currentContent)
            {
                undoStack.push(currentContent);
                while (undoStack.size() > 5)
                {
                    undoStack.pop();
                }
            };
        while (true)
        {
            system("cls");
            cout << content;
            int currentRow = 0;
            int currentCol = 0;
            for (int i = 0; i < currentCol; ++i)
            {
                if (content[i] == '\n' || currentCol == totalCols)
                {
                    currentCol = 0;
                    currentRow++;
                }
                else
                {
                    currentCol++;
                }
            }
            setCursorPosition(currentCol, currentRow, 4);
            int key = getArrowKey();
            switch (key)
            {
            case 75: // Left arrow
                currentPosition = max(0, currentPosition - 1);
                break;
            case 77: // Right arrow
                currentPosition = min(static_cast<int>(content.size()), currentPosition + 1);
                break;
            case 80: // Down Key
                while (currentPosition < content.size() && content[currentPosition] != '\n')
                {
                    currentPosition++;
                }
                if (currentPosition < content.size())
                {
                    currentPosition++;
                }
                break;
            case 72: // Up key
                while (currentPosition > 0 && content[currentPosition - 1] != '\n')
                {
                    currentPosition--;
                }
                if (currentPosition > 0)
                {
                    currentPosition--;
                }
                break;
            case 8: // Backspace key
                if (currentPosition > 0)
                {
                    pushToUndoStack(content);
                    content.erase(content.begin() + currentPosition - 1);
                    currentPosition--;
                }
                break;
            case 27:                           // Escape key
                saveToFile(fileName, content); // Save changes before exiting
                return;                        // Exit the function on escape key
            case 26:                           // Ctrl + Z key (undo)
                if (!undoStack.empty())
                {
                    redoStack.push(content);
                    content = undoStack.top();
                    undoStack.pop();
                    currentPosition = min(currentPosition, static_cast<int>(content.size()));
                }
                break;
            case 25: // Ctrl + Y key (redo)
                if (!redoStack.empty())
                {
                    undoStack.push(content);
                    content = redoStack.top();
                    redoStack.pop();
                    currentPosition = min(currentPosition, static_cast<int>(content.size()));
                }
                break;
            default:
                if (isprint(key))
                {
                    pushToUndoStack(content);
                    content.insert(content.begin() + currentPosition, static_cast<char>(key));
                    currentPosition++;
                }
                break;
            }
        }
    }

    bool searchInFile(string searchString, string fileName)
    {
        ifstream file(fileName);
        if (!file.is_open())
        {
            cout << "File does not exist\n";
            return false;
        }
        string line;
        while (getline(file, line))
        {
            if (line.find(searchString) != string::npos)
            {
                file.close();
                return true;
            }
        }
        cout << "String not found in file: " << Name << extension << "\n";
        file.close();
        return false;
    }
};