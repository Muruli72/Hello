#include "FileManager.h"
#include <iostream>
#include <filesystem>
#include <fstream>

using namespace std;

void FileManager::showFiles() {

    for (const auto& entry : std::filesystem::directory_iterator("documents")) {

        if (entry.path().extension() == ".txt") {
            cout << entry.path() << endl;
        }
    }
}

vector<Document> FileManager::loadDocuments() {
    vector<Document> documents;
    for (const auto& entry : std::filesystem::directory_iterator("documents")) {
        if (entry.path().extension() == ".txt") {
            ifstream file(entry.path());
            string content;
            string line;
             while (getline(file, line)) {
                content += line + "\n";
            }
            Document document;
            document.filename = entry.path().filename().string();
            document.content = content;
            documents.push_back(document);
        }

    }
     return documents;
}