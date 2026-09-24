#include "InvertedIndex.h"
#include <iostream>

using namespace std;

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

void InvertedIndex::showIndex() {

    for (const auto& entry : index) {

        cout << entry.first << " -> ";

        for (const string& document : entry.second) {

            cout << document << " ";
        }

        cout << endl;
    }
}
vector<string> InvertedIndex::search(const string& word) {

    auto it = index.find(word);

    if (it != index.end()) {

        return it->second;
    }

    return {};
}
vector<string> InvertedIndex::searchAll(
    const vector<string>& words
) {

    if (words.empty()) {

        return {};
    }

    // Start with documents containing the first word
    vector<string> results = search(words[0]);

    // Check the remaining words
    for (int i = 1; i < words.size(); i++) {

        vector<string> currentResults = search(words[i]);

        vector<string> commonDocuments;

        // Find documents present in both lists
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
vector<string> InvertedIndex::searchAny(
    const vector<string>& words
) {

    vector<string> results;

    for (const string& word : words) {

        vector<string> currentResults = search(word);

        for (const string& document : currentResults) {

            bool alreadyExists = false;

            for (const string& existingDocument : results) {

                if (existingDocument == document) {

                    alreadyExists = true;
                    break;
                }
            }

            if (!alreadyExists) {

                results.push_back(document);
            }
        }
    }

    return results;
}
vector<string> InvertedIndex::searchNot(
    const string& includeWord,
    const string& excludeWord
) {

    // Get documents containing the word we want
    vector<string> includeDocuments =
        search(includeWord);

    // Get documents containing the word we want to exclude
    vector<string> excludeDocuments =
        search(excludeWord);

    vector<string> results;

    // Check every document containing includeWord
    for (const string& document : includeDocuments) {

        bool shouldExclude = false;

        // Check whether this document also contains excludeWord
        for (const string& excludedDocument : excludeDocuments) {

            if (document == excludedDocument) {

                shouldExclude = true;
                break;
            }
        }

        // Add only documents that should NOT be excluded
        if (!shouldExclude) {

            results.push_back(document);
        }
    }

    return results;
}
