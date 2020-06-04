#ifndef CALCULATOR_MATH_H
#define CALCULATOR_MATH_H

#include <string>
#include <sstream>

class Parser {
public:
    explicit Parser(std::string line);
    void parse();
    double number();
    double factor();
    double term();
    bool match(char c);
    static void displayError ();
    void isValidSyntax (const std::string &s);

private:
    char lookahead;
    std::stringstream stream;
    bool error;

    static std::string extractSpaces(std::string basicString);

};

#endif //CALCULATOR_MATH_H
