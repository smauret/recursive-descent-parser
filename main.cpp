#include <iostream>
#include <fstream>
#include "math.h"

using namespace std;

bool ignoreLine(string expr) {
    int i(0);
    while (expr[i] == ' ') { //Check for spaces at the beginning of line
        i++;
    }
    return expr[i] == '#';
}

int main(int argc, char** argv) {
    ifstream calculusFile(argv[1]);

    if (calculusFile) {
        string line;
        while (getline(calculusFile, line)) {
            if(!ignoreLine(line)){
                cout << "line : " << line << " ";
                Parser(line).parse();
            };
        }
    } else {
        cout << "Error: Failed to open file." << endl;
    }

    return 0;
}
