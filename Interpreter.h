#pragma once
#include "TokenId.h"
#include <string>
#include "Token.h"
#include "LinkedList.h"
#include <iostream>
using std::string;
using std::to_string;
using std::cout;
using std::endl;
using std::cin;
enum TokenType {
    oper,
    func,
    num,
    openPar,
    closePar
};
/**
 * almost works will do here
 * @attributes 1.tokensId: holds info for parser.
 * @attributes 2.input: holds inputted string.
 * @attributes 3.tokens: list of tokens
 */
class Interpreter {
public:
    TokenId tokensId[37];
    string input;
    LinkedList<Token> tokens;
    bool debug;
    /**
     * base constructor.
     * initials data for parser.
     */
    Interpreter();
    /**
     * Finds related tokenIndicator for given character.
     * @param c: character to findFirst its tokenIndicator.
     * @return tokenIndicator for given character.
     */
    TokenIndicator findTokenId(const char* c);
    /**
     * converts input string to token list
     * and finds tokenIndicator
     */
    void Parser();
    /**
     * Prints token list.
     */
    void printTokens();
    /**
     * provides number attribute for number tokens
     */
    void NumberConversion();
    /**
     * checks token list for errors.
     */
    void checkTokenChain();
    /**
     * Finds next operator to do.
     * @return operator position.
     */
    int findNext();
    /**
     * Checks if there is number before and after a specific operator.
     * @param n token position.
     * @return true if there is else false.
     */
    bool beforeAfterNumber(int n);
    void checkParentheses();
    /**
     * will do operators based on priority.
     */
    void solver();
    /**
     * main function for interpreter.
     */
    void start();
    /**
     * indicatas token id type for easier check;
     * @param id to be checked
     * @return id type
     */
    TokenType tokenTypeIndicator(TokenIndicator id);
};

