#pragma once
#include <string>
using std::string;
#include "TokenIndicator.h"
/**
 * A class to hold needed info to findFirst token identity.
 */
class TokenId {
public:
    TokenIndicator token;
    string Id;
    TokenId() = default;
    TokenId(TokenIndicator token, char Id);
};

