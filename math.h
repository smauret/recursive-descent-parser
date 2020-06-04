#ifndef CALCULATOR_MATH_H
#define CALCULATOR_MATH_H

#include <string>
#include <sstream>

//This class implements a recursive descent parser for parsing simple math formulas (+ - * /)

class Parser {
public:
    explicit Parser(std::string line);
    void parse();


private:
    char lookahead; //Current char that's being evaluated, lookahead will take the value (one by one) of all chars in the line
    std::stringstream stream; //Stream from the line
    bool error;

    double number(); //Evaluates a number which is a double
    double factor(); //Evaluates a factor which is a number on either side of * or /
    double term(); //Evaluates a term which is a number or a (factor *|/ factor) expression on either side of + or -
    bool match(char c); //Evaluate if lookahead is equal to c
    static void displayError (); //Display an error message
    void isValidSyntax (const std::string &s); //Check syntax of the line
    static std::string extractSpaces(std::string basicString); //Extract spaces of the line

};

#endif //CALCULATOR_MATH_H
