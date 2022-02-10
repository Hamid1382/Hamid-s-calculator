#include <iostream>
#include "BigNum.h"
#include "MyMath.h"
#include "Exception.h"
#include "Node.h"
#include "LinkedList.h"
#include "TokenIndicator.h"
#include "Token.h"
#include "TokenId.h"
#include "Interpreter.h"
/**
 * program main function.
 * controls program settings.
 * @return
 */

int main() {
    while (true) {
        auto* interpreter = new Interpreter();
        string input;
        while (true) {
            getline(cin, input);
            if (input == "Debug True") {
                interpreter->debug = true;
            }
            else if (input == "Debug False") {
                interpreter->debug = false;
            }
            else {
                break;
            }
            if (input == "Exit")
                break;
        }
        if (input == "Exit")
            break;
        interpreter->input = input;
        interpreter->start();
        delete interpreter;
    }
}
