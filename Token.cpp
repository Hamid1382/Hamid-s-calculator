#include "Token.h"
Token::Token(TokenIndicator id, string text) {
    this->id = id;
    this->text = text;
}

bool Token::operator==(const Token& other) const {
    return this->id == other.id;
}