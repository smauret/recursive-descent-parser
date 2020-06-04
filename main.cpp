#include <iostream>
#include <fstream>
#include "math.h"

using namespace std;

bool ignoreLine(string expr) {
    int i(0);
    while (expr[i] == ' ') { //Check for spaces at the beginning of line
        i++;
    }
    return expr[i] == '#'; //Check if first char after spaces is # and in this case returns true
}

int main(int argc, char** argv) {
    ifstream calculusFile(argv[1]); //Open stream to text file path given in argument

    if (calculusFile) { //Check if file opened
        string line;
        while (getline(calculusFile, line)) { //Loop over all lines in file
            if(!ignoreLine(line)){ //Ignore lines starting with #
                cout << "line : " << line << " ";
                Parser(line).parse(); //Call parser on line
            };
        }
    } else {
        cout << "Error: Failed to open file." << endl;
    }

    return 0;
}
