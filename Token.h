#pragma once
#include "TokenIndicator.h"
#include <string>
#include "BigNum.h"
using std::string;
/**
 * Token class, holds needed info.
 */
class Token {
public:
    TokenIndicator id;
    string text;
    short int pos;
    BigNum number; //only for numbers
    Token() = default;
    Token(TokenIndicator id, string text);
    bool operator== (const Token& other) const;
};
