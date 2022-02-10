#pragma once
#include <string>
#include <exception>
using std::string;
using std::exception;

/**
 * provides easy way to throw own exceptions.
 */
class Exception : public exception
{
public:
    explicit Exception(const char* message);
    explicit Exception(const string& message);
protected:
    string msg_;
};