#include "Tokenizer.h"

#include <sstream>
#include <cctype>
#include <algorithm>

using namespace std;

vector<string> Tokenizer::tokenize(const string& text) {

    vector<string> tokens;

    stringstream ss(text);

    string word;

    while (ss >> word) {

        for (char &c : word) {

            c = tolower(c);

        }

        word.erase(remove_if(word.begin(), word.end(), ::ispunct), word.end());

        tokens.push_back(word);
    }

    return tokens;
}