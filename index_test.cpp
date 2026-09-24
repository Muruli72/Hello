#include "InvertedIndex.h"

#include <iostream>

using namespace std;


// Add one document to the inverted index
void InvertedIndex::addDocument(
    const string& filename,
    const vector<string>& tokens
) {

    for (const string& token : tokens) {

        vector<string>& documents = index[token];

        bool alreadyExists = false;

        for (const string& document : documents) {

            if (document == filename) {

                alreadyExists = true;
                break;
            }
        }

        if (!alreadyExists) {

            documents.push_back(filename);
        }
    }
}


// Display the complete inverted index
void InvertedIndex::showIndex() {

    for (const auto& entry : index) {

        cout << entry.first << " -> ";

        for (const string& document : entry.second) {

            cout << document << " ";
        }

        cout << endl;
    }
}


// Search for one word
vector<string> InvertedIndex::search(
    const string& word
) {

    auto it = index.find(word);

    if (it != index.end()) {

        return it->second;
    }

    return {};
}


// Search for multiple words
// A document must contain ALL the words
vector<string> InvertedIndex::searchAll(
    const vector<string>& words
) {

    if (words.empty()) {

        return {};
    }

    // Start with documents containing the first word
    vector<string> results = search(words[0]);

    // Check every remaining word
    for (int i = 1; i < words.size(); i++) {

        vector<string> currentResults = search(words[i]);

        vector<string> commonDocuments;

        // Find documents common to both lists
        for (const string& document : results) {

            for (const string& currentDocument : currentResults) {

                if (document == currentDocument) {

                    commonDocuments.push_back(document);

                    break;
                }
            }
        }

        // Keep only common documents
        results = commonDocuments;
    }

    return results;
}