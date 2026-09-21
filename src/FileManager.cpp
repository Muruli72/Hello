#include "FileManager.h"
#include <iostream>
#include <filesystem>

using namespace std;

void FileManager::showFiles() {

    for (const auto& entry : std::filesystem::directory_iterator("documents")) {

        if (entry.path().extension() == ".txt") {
            cout << entry.path() << endl;
        }
    }
}