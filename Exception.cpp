#include "Exception.h"
Exception::Exception(const char* message)
    : msg_(message) {}

Exception::Exception(const string& message)
    : msg_(message) {}