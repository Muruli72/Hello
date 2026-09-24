#include "TFIDF.h"

#include <cmath>
#include <unordered_set>
#include <algorithm>

using namespace std;


void TFIDF::addDocument(
    const string& filename,
    const vector<string>& tokens
) {

    totalDocuments++;

    documentWordCount[filename] = tokens.size();

    unordered_set<string> uniqueWords;

    for (const string& token : tokens) {

        // Count how many times this word appears
        wordFrequency[filename][token]++;

        // Keep track of unique words
        uniqueWords.insert(token);
    }

    // Count how many documents contain each word
    for (const string& word : uniqueWords) {

        documentFrequency[word]++;
    }
}


double TFIDF::calculateTF(
    const string& filename,
    const string& word
) {

    // Check whether the document exists
    if (documentWordCount.find(filename)
        == documentWordCount.end()) {

        return 0.0;
    }

    // Get frequency of word in document
    int frequency =
        wordFrequency[filename][word];

    // Total words in document
    int totalWords =
        documentWordCount[filename];

    if (totalWords == 0) {

        return 0.0;
    }

    return static_cast<double>(frequency)
           / totalWords;
}


double TFIDF::calculateIDF(
    const string& word
) {

    int documentsContainingWord =
        documentFrequency[word];

    if (documentsContainingWord == 0) {

        return 0.0;
    }

    return log(
        static_cast<double>(totalDocuments)
        / documentsContainingWord
    );
}


double TFIDF::calculateTFIDF(
    const string& filename,
    const string& word
) {

    double tf =
        calculateTF(filename, word);

    double idf =
        calculateIDF(word);

    return tf * idf;
}vector<pair<string, double>> TFIDF::rankDocuments(
    const vector<string>& documents,
    const vector<string>& queryWords
) {

    vector<pair<string, double>> rankedResults;

    // Calculate a score for every document
    for (const string& document : documents) {

        double score = 0.0;

        // Add TF-IDF score for every query word
        for (const string& word : queryWords) {

            score += calculateTFIDF(
                document,
                word
            );
        }

        rankedResults.push_back(
            {document, score}
        );
    }

    // Sort highest score first
    sort(
        rankedResults.begin(),
        rankedResults.end(),
        [](const pair<string, double>& a,
           const pair<string, double>& b) {

            return a.second > b.second;
        }
    );

    return rankedResults;
}