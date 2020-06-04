#include "math.h"
#include <iostream>
#include <sstream>

using namespace std;

Parser::Parser(std::string line):error(false) {
    string lineNoSpace = extractSpaces(line); //Extract spaces in line
    isValidSyntax(lineNoSpace); //Check syntax and sets error if necessary
    stream = stringstream(lineNoSpace); //Create stream from string
    lookahead = stream.get(); //Set first char of stream to lookahead
}

void Parser::parse() {
    if(!error){ //If no error found with isValidSyntax() we continue to the parsing
        double d = term(); //First call to term
        !error && cout << "answer :" << d << endl; //If no error were encountered display the result
    }
};

double Parser::number() {
    double number(0);
    while (lookahead >= '0' && lookahead <= '9') { //If lookahead is a number from 1 to 9
        number *= 10; //Ex: 123 = (((0)*10+1)*10+2)*10+3)
        number += lookahead - '0'; //Substract ASCII code to get a value between 1 and 9
        lookahead = stream.get(); //Then we go to the next char
    }
    if (lookahead == '.') { //If we have a floating point value
        lookahead = stream.get(); //We skip the . and move to the next char
        double weight = 1;
        while (lookahead >= '0' && lookahead <= '9') {
            weight /= 10; //Every new char gets added with a weight
            double scaled = (lookahead - '0') * weight; //Ex: .123 = 1*(1/10)+2*(1/100)+3*(1/1000)
            number += scaled; //Add decimals to the numbre
            lookahead = stream.get(); //Continue until the next char is not in 1-9
        }
    } else if (lookahead == '(') { //If the next number is an expression between ()
        lookahead = stream.get(); //Skip the (
        double sum = term(); //Call term to evaluate the expression
        error = !match(')'); //Expect that the expression is enclosed in () otherwise it's an error
        return sum; //Return the result of the expression that's in between ()
    }
    return number; //Return the number, note that if the char (lookahead) is not in the range 1-9 zero is returned
};

double Parser::factor() {
    double fac1 = number(); //Find the first number
    while (lookahead == '*' || lookahead == '/') { //Continue as long as there is a multiplication or division
        char multOrDiv = lookahead; //Weather it is a division or multiplication
        lookahead = stream.get(); //Skip the * or / char
        double fac2 = number(); // Get the second factor of the * or /
        switch (multOrDiv) {
            case '*':
                fac1 *= fac2; // Compute the result of the multiplication
                break;
            case '/':
                if(fac2 != 0 ){ // Compute the result of the division, give an error when division by zero
                    fac1 /= fac2;
                }else{
                    error = true;
                    displayError();
                }
                break;
            default:
                break;
        }
    }
    return fac1; //Return the result of the successive * or /
}

double Parser::term() {
    double term1 = factor(); // Compute the first term
    while (lookahead == '+' || lookahead == '-') { //Continue as long as there is an addition or subtraction
        char addOrSubstr = lookahead; //Weather it is an addition or subtraction
        lookahead = stream.get(); //Skip the + or - char
        double term2 = factor(); // Get the second term of the + or -
        switch (addOrSubstr) {
            case '+':
                term1 += term2; // Compute the result of the addition
                break;
            case '-':
                term1 -= term2; // Compute the result of the subtraction
                break;
            default:
                break;
        }
    }
    return term1; //Return the result of the successive + or -
}

bool Parser::match(char c) { //Check if current char (lookahead) is equal to char passed as parameter
    if (c == lookahead) {
        lookahead = stream.get();
        return true;
    } else {
        displayError();
        return false;
    }
}

void Parser::displayError() {
    cout << "Syntax error. " << endl;
}

string Parser::extractSpaces(string expr) {

    string exprNoSpaces; // Get Rid of Spaces
    for (int i = 0; i < expr.length(); i++) { //Loop through the string and create a new one without spaces
        if (expr[i] != ' ') {
            exprNoSpaces += expr[i];
        }
    }

    return exprNoSpaces;
}

void Parser::isValidSyntax(const string &s) {

    bool op(false); //Is current char an operator (+ - * /)

    for (auto it = s.cbegin(); it != s.cend(); ++it) { //Iterate through the line
        //If the char before wasn't an operator but the current one is
        if (!op && (*it == '*' || *it == '/' || *it == '+' || *it == '-' || *it == '.')) {
            op=true;
        }//If the char before an operator and the current one is (ex: ++, *- )
        else if (op && (*it == '*' || *it == '/' || *it == '+' || *it == '-'|| *it == '.')){
            displayError();
            error = true;
        }//If the char is none of the allowed char 1-9 . () +-*/
        else if(!((*it >= '0' && *it <= '9') || *it == '.' || *it == '(' || *it == ')' )){
            displayError();
            error = true;
        }else{
            op = false;
        }
    }
}

