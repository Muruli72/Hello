#include <iostream>
#include "FileManager.h"

using namespace std;

int main() {

    FileManager manager;

    vector<Document> documents = manager.loadDocuments();

    for (Document document : documents) {

        cout << "File: " << document.filename << endl;
        cout << "Content:" << endl;
        cout << document.content << endl;

        cout << "------------------------" << endl;
    }

    return 0;
}