#include "math.h"
#include <iostream>
#include <sstream>

using namespace std;

Parser::Parser(std::string line):error(false) {
    string lineNoSpace = extractSpaces(line);
    isValidSyntax(lineNoSpace);
    stream = stringstream(lineNoSpace);
    lookahead = stream.get();
}

void Parser::parse() {
    if(!error){
        double d = term();
        !error && cout << "answer :" << d << endl;
    }
};

double Parser::number() {
    double number(0);
    while (lookahead >= '0' && lookahead <= '9') {
        number *= 10;
        number += lookahead - '0';
        lookahead = stream.get();
    }
    if (lookahead == '.') {
        lookahead = stream.get();
        double weight = 1;
        while (lookahead >= '0' && lookahead <= '9') {
            weight /= 10;
            double scaled = (lookahead - '0') * weight;
            number += scaled;
            lookahead = stream.get();
        }
    } else if (lookahead == '(') {
        lookahead = stream.get();
        double sum = term();
        error = !match(')');
        return sum;
    }
    return number;
};

double Parser::factor() {
    double fac1 = number();
    while (lookahead == '*' || lookahead == '/') {
        char multOrDiv = lookahead;
        lookahead = stream.get();
        double fac2 = number();
        switch (multOrDiv) {
            case '*':
                fac1 *= fac2;
                break;
            case '/':
                fac1 /= fac2;
                break;
            default:
                break;
        }
    }
    return fac1;
}

double Parser::term() {
    double term1 = factor();
    while (lookahead == '+' || lookahead == '-') {
        char addOrSubstr = lookahead;
        lookahead = stream.get();
        double term2 = factor();
        switch (addOrSubstr) {
            case '+':
                term1 += term2;
                break;
            case '-':
                term1 -= term2;
                break;
            default:
                break;
        }
    }
    return term1;
}

bool Parser::match(char c) {
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
    for (int i = 0; i < expr.length(); i++) {
        if (expr[i] != ' ') {
            exprNoSpaces += expr[i];
        }
    }

    return exprNoSpaces;
}

void Parser::isValidSyntax(const string &s) {

    bool op(false);
    for (auto it = s.cbegin(); it != s.cend(); ++it) {

        if (!op && (*it == '*' || *it == '/' || *it == '+' || *it == '-')) {
            op=true;
        }else if (op && (*it == '*' || *it == '/' || *it == '+' || *it == '-')){
            displayError();
            error = true;
        }else if(!((*it >= '0' && *it <= '9') || *it == '.' || *it == '(' || *it == ')' )){
            displayError();
            error = true;
        }else{
            op = false;
        }
    }
}

