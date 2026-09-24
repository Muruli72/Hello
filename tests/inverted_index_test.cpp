#include <iostream>
#include "InvertedIndex.h"

using namespace std;

int main() {

    InvertedIndex index;

    vector<string> machineLearningTokens = {
        "machine",
        "learning",
        "machine",
        "data"
    };

    vector<string> dataScienceTokens = {
        "data",
        "science",
        "machine",
        "data"
    };

    index.addDocument(
        "machine_learning.txt",
        machineLearningTokens
    );

    index.addDocument(
        "data_science.txt",
        dataScienceTokens
    );

    cout << "Search results for: machine" << endl;

    vector<string> results = index.search("machine");

    for (const string& document : results) {

        cout << document << endl;
    }
    cout << endl;

cout << "Search results for: quantum" << endl;

results = index.search("quantum");

if (results.empty()) {

    cout << "No documents found." << endl;

} else {

    for (const string& document : results) {

        cout << document << endl;
    }
}

    return 0;
}