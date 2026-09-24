#include <iostream>
#include "Tokenizer.h"

using namespace std;

int main() {

    Tokenizer tokenizer;

    string text = "Machine Learning is Powerful!";

    vector<string> tokens = tokenizer.tokenize(text);

    for (string token : tokens) {

        cout << token << endl;
    }

    return 0;
}