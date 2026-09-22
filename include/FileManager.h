#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>
#include <vector>

struct Document {
    std::string filename;
    std::string content;
};

class FileManager {

public:

    void showFiles();

    std::vector<Document> loadDocuments();

};

#endif