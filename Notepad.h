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
#include "CurrentFile.h"
#include "Tree.h"
using namespace std;

class NotePad {
    friend class Dos;
    friend class File;
    friend class CurrentFile;
private:
    std::list<CurrentFile *> NotePadFiles;

public:
    NotePad() {
        NotePadFiles = list<CurrentFile*>();
    }
    CurrentFile CF;

    CurrentFile *findFile(const std::string& _name) {
        for (auto& File : NotePadFiles) {
            if (File->name == _name) {
                return File;
            }
        }
        return nullptr;
    }

    void deleteAllFiles() {
        for (auto& file : NotePadFiles) {
            std::string fileName = file->name + ".txt";
            std::ofstream fileStream(fileName);
            fileStream.close();
            std::remove(fileName.c_str());
        }
    }
};
