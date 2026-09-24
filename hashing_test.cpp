#include <iostream>
#include <unordered_map>

using namespace std;

int main() {

    unordered_map<string, int> wordCount;

    wordCount["machine"] = 5;
    wordCount["learning"] = 3;
    wordCount["data"] = 10;

    cout << wordCount["machine"] << endl;
    cout << wordCount["data"] << endl;

    return 0;
}