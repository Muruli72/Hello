#include <iostream>

#include "FileManager.h"
#include "Tokenizer.h"
#include "InvertedIndex.h"
#include "TFIDF.h"

using namespace std;

int main() {

    FileManager manager;
    Tokenizer tokenizer;
    InvertedIndex index;
    TFIDF tfidf;

    // Load all documents
    vector<Document> documents = manager.loadDocuments();

    // Tokenize and index every document
    for (const Document& document : documents) {

        vector<string> tokens =
            tokenizer.tokenize(document.content);

        // Add document to inverted index
        index.addDocument(
            document.filename,
            tokens
        );

        // Add document to TF-IDF system
        tfidf.addDocument(
            document.filename,
            tokens
        );
    }

    // Get search query
    string query;

    cout << "Enter search query: ";

    getline(cin >> ws, query);

    // Convert query into words
    vector<string> queryTokens =
        tokenizer.tokenize(query);

    // Check for empty query
    if (queryTokens.empty()) {

        cout << "No valid search words entered." << endl;

        return 0;
    }

    // Store search results
    vector<string> results;

    bool hasOR = false;
    bool hasNOT = false;

    // Check which Boolean operators are present
    for (const string& word : queryTokens) {

        if (word == "or") {

            hasOR = true;
        }

        if (word == "not") {

            hasNOT = true;
        }
    }

    // ==========================================
    // NOT SEARCH
    // Example:
    // machine NOT data
    // ==========================================

    if (hasNOT) {

        // Find the position of NOT
        int notPosition = -1;

        for (int i = 0; i < queryTokens.size(); i++) {

            if (queryTokens[i] == "not") {

                notPosition = i;

                break;
            }
        }

        // Make sure there is a word before and
        // after NOT
        if (notPosition > 0 &&
            notPosition < queryTokens.size() - 1) {

            string includeWord =
                queryTokens[notPosition - 1];

            string excludeWord =
                queryTokens[notPosition + 1];

            results =
                index.searchNot(
                    includeWord,
                    excludeWord
                );

        } else {

            cout << "Invalid NOT query." << endl;

            return 0;
        }
    }

    // ==========================================
    // OR SEARCH
    // Example:
    // machine OR algorithms
    // ==========================================

    else if (hasOR) {

        vector<string> searchWords;

        // Remove the word "or"
        for (const string& word : queryTokens) {

            if (word != "or") {

                searchWords.push_back(word);
            }
        }

        results =
            index.searchAny(searchWords);
    }

    // ==========================================
    // NORMAL AND SEARCH
    // Example:
    // machine learning
    // ==========================================

    else {

        results =
            index.searchAll(queryTokens);
    }

    // ==========================================
    // DISPLAY RESULTS
    // ==========================================

if (results.empty()) {

    cout << "No documents found." << endl;

} else {

    // Rank matching documents using TF-IDF
    vector<pair<string, double>> rankedResults =
        tfidf.rankDocuments(
            results,
            queryTokens
        );

    cout << endl;

    cout << "Search results for: "
         << query << endl;

    for (const auto& result : rankedResults) {

        cout << result.first
             << "  Score: "
             << result.second
             << endl;
    }
}

    return 0;
}