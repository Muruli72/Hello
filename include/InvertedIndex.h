#ifndef INVERTED_INDEX_H
#define INVERTED_INDEX_H

#include <string>
#include <vector>
#include <unordered_map>

class InvertedIndex {

private:

    std::unordered_map<std::string, std::vector<std::string>> index;

public:

    void addDocument(
        const std::string& filename,
        const std::vector<std::string>& tokens
    );

    void showIndex();

    std::vector<std::string> search(
        const std::string& word
    );

    std::vector<std::string> searchAll(
        const std::vector<std::string>& words
    );
    std::vector<std::string> searchAny(
    const std::vector<std::string>& words
    );
    std::vector<std::string> searchNot(
    const std::string& includeWord,
    const std::string& excludeWord
    );
};

#endif