//
// Created by Hamid on 24/01/2022.
//

#include "Interpreter.h"
#include "LinkedList.cpp"
#include "MyMath.h"
Interpreter::Interpreter() {
    debug = false;
    tokensId[0].token = Plus, tokensId[0].Id = "+";
    tokensId[1].token = Minus, tokensId[1].Id = "-";
    tokensId[2].token = Multiply, tokensId[2].Id = "*";
    tokensId[3].token = Divide, tokensId[3].Id = "/";
    tokensId[4].token = P, tokensId[4].Id = "p";
    tokensId[5].token = E, tokensId[5].Id = "e";
    tokensId[6].token = OpenParentheses, tokensId[6].Id = "(";
    tokensId[7].token = CloseParentheses, tokensId[7].Id = ")";
    tokensId[8].token = power, tokensId[8].Id = "^";
    tokensId[9].token = TokenIndicator::sin, tokensId[8].Id = "sin";
    tokensId[10].token = TokenIndicator::cos, tokensId[10].Id = "cos";
    tokensId[11].token = cot, tokensId[11].Id = "cot";
    tokensId[12].token = TokenIndicator::tan, tokensId[12].Id = "tan";
    tokensId[13].token = sec, tokensId[13].Id = "sec";
    tokensId[14].token = csc, tokensId[14].Id = "csc";
    tokensId[15].token = csc, tokensId[15].Id = "csc";
    tokensId[16].token = TokenIndicator::sinh, tokensId[16].Id = "sinh";
    tokensId[17].token = TokenIndicator::cosh, tokensId[17].Id = "cosh";
    tokensId[18].token = coth, tokensId[18].Id = "coth";
    tokensId[19].token = TokenIndicator::tanh, tokensId[19].Id = "tanh";
    tokensId[20].token = sech, tokensId[20].Id = "sech";
    tokensId[21].token = csch, tokensId[21].Id = "csch";
    tokensId[22].token = csch, tokensId[22].Id = "csch";
    tokensId[23].token = arcsin, tokensId[23].Id = "arcsin";
    tokensId[24].token = arcos, tokensId[24].Id = "arccos";
    tokensId[25].token = arccot, tokensId[25].Id = "arccot";
    tokensId[26].token = arctan, tokensId[26].Id = "arctan";
    tokensId[27].token = arcsec, tokensId[27].Id = "arcsec";
    tokensId[28].token = arccsc, tokensId[28].Id = "arccsc";
    tokensId[29].token = arccsc, tokensId[29].Id = "arccsc";
    tokensId[30].token = arcsinh, tokensId[30].Id = "arcsinh";
    tokensId[31].token = arccosh, tokensId[31].Id = "arccosh";
    tokensId[32].token = arccoth, tokensId[32].Id = "arccoth";
    tokensId[33].token = arctanh, tokensId[33].Id = "arctanh";
    tokensId[34].token = arcsech, tokensId[34].Id = "arcsech";
    tokensId[35].token = arccsch, tokensId[35].Id = "arccsch";
    tokensId[36].token = arccsch, tokensId[36].Id = "arccsch";
}

TokenIndicator Interpreter::findTokenId(const char* c) {
    for (auto& i : tokensId) {
        if (*c == ' ')
            continue;
        if (*c == i.Id[0]) {
            return i.token;
        }
    }
    if ((*c >= '0' && *c <= '9') || *c == '.') {
        return Number;
    }
    cout << *c;
    throw Exception("Unknown token.");
}

void Interpreter::Parser() {
    Token tmp;
    bool isPreviousNumber = false;
    TokenIndicator tmp2;
    short pos = 0;
    for (int i = 0; i < input.length(); i++) {
        char& c = input[i];
        tmp.pos = pos;
        tmp2 = findTokenId(&c);
        long long j;
        for (j = 0; i < 1; i++) {
            if (tokensId[j].token == tmp2)
                break;
        }
        i += tokensId[j].Id.length() - 1;
        if (tmp2 == Number) {
            isPreviousNumber = true;
            tmp.text += c;
        }
        else {
            if (isPreviousNumber) {
                tmp.id = Number;
                tokens.push(tmp);
                pos++;
                tmp.text.clear();
            }
            tmp.text = c;
            tmp.id = tmp2;
            tokens.push(tmp);
            pos++;
            tmp.text.clear();
            isPreviousNumber = false;
        }
    }
    if (!tmp.text.empty()) {
        tmp.id = Number;
        tmp.pos = pos;
        tokens.push(tmp);
    }
}

void Interpreter::printTokens() {
    for (int i = 0; i < tokens.Size(); i++) {
        cout << i + 1 << ".\t";
        switch (tokens.at(i).id) {
        case Plus:
            cout << "Plus";
            break;
        case Minus:
            cout << "Minus";
            break;
        case Multiply:
            cout << "Multiply";
            break;
        case Divide:
            cout << "Divide";
            break;
        case Number:
            cout << "Number: " << tokens.at(i).number.getString();
            break;
        case OpenParentheses:
            cout << "Open Parentheses";
            break;
        case CloseParentheses:
            cout << "Close Parentheses";
            break;
        case P:
            cout << "p";
            break;
        case E:
            cout << "e";
            break;
        case power:
            cout << '^';
            break;
        default:
            cout << "Unknown Token Id";
        }
        cout << endl;
    }
}

void Interpreter::NumberConversion() {
    for (int i = 0; i < tokens.Size(); i++) {
        if (tokens.at(i).id == Number) {
            tokens.at(i).number = BigNum(tokens.at(i).text);
        }
        else if (tokens.at(i).id == P) {
            tokens.at(i).number = BigNum("3.141592654");
        }
        else if (tokens.at(i).id == E) {
            tokens.at(i).number = BigNum("2.718281828");
        }
    }
}

void Interpreter::checkTokenChain() {
    Token minus1(Number, "-1");
    minus1.number = BigNum("-1");
    for (int i = 0; i < tokens.Size() - 1; i++) {
        if (tokens.at(i).id == Minus && tokens.at(i + 1).id == Number) {
            if (i == 0) {
                tokens.remove(0);
                tokens.at(0).number.Negative = !tokens.at(0).number.Negative;
            }
            else if (tokenTypeIndicator(tokens.at(i - 1).id) == oper || tokenTypeIndicator(tokens.at(i - 1).id) == openPar || tokenTypeIndicator(tokens.at(i - 1).id) == func) {
                tokens.remove(0);
                tokens.at(0).number.Negative = !tokens.at(0).number.Negative;
            }
        }
        else if (tokens.at(i).id == Plus && tokens.at(i + 1).id == Number) {
            if (i == 0) {
                tokens.remove(0);
            }
            else if (tokenTypeIndicator(tokens.at(i - 1).id) == oper || tokenTypeIndicator(tokens.at(i - 1).id) == openPar || tokenTypeIndicator(tokens.at(i - 1).id) == func) {
                tokens.remove(0);
            }
        }
    }
redo:
    switch (tokenTypeIndicator(tokens.at(0).id)) {
    case oper:
        throw Exception("Invalid operator placement at start");
    case closePar:
        throw Exception("Invalid operator placement at start");
    }
    for (int i = 1; i < tokens.Size(); i++) {
        switch ((tokenTypeIndicator(tokens.at(i).id))) {
        case oper:
            if ((tokenTypeIndicator(tokens.at(i - 1).id) != num && tokenTypeIndicator(tokens.at(i - 1).id) != closePar) ||
                tokenTypeIndicator(tokens.at(i + 1).id) != num && tokenTypeIndicator(tokens.at(i - 1).id) != closePar)
                throw Exception("Invalid operator placement at " + to_string(i + 1));
        case func:
            if (tokenTypeIndicator(tokens.at(i + 1).id) != num || tokenTypeIndicator(tokens.at(i + 1).id) != func || tokenTypeIndicator(tokens.at(i + 1).id) != openPar)
                throw Exception("Invalid operator placement at " + to_string(i + 1));
        case openPar:
            if (tokenTypeIndicator(tokens.at(i - 1).id) == closePar || tokenTypeIndicator(tokens.at(i - 1).id) == num)
                throw Exception("Invalid operator placement at " + to_string(i + 1));
        case closePar:
            if (tokenTypeIndicator(tokens.at(i - 1).id) == oper)
                throw Exception("Invalid operator placement at " + to_string(i + 1));
            break;
        }
    }
}

int Interpreter::findNext() {
    for (int i = 0; i < tokens.Size() - 2; i++) {
        if (tokens.at(i).id == OpenParentheses && tokens.at(i + 1).id == Number && tokens.at(i + 2).id == CloseParentheses)
            return i;
    }
    int start1 = 0, end1 = tokens.Size() - 1;
    for (int i = 0; i < tokens.Size(); i++) {
        if (tokens.at(i).id == OpenParentheses)
            start1 = i;
        else if (tokens.at(i).id == CloseParentheses) {
            end1 = i;
            break;
        }

    }
    for (int i = end1; i >= start1; i++) {
        if (tokenTypeIndicator(tokens.at(i).id) == func)
            return i;
    }
    int iter;
    TokenIndicator found = Number;
    for (int i = start1; i <= end1; i++) {
        if ((tokens.at(i).id == Plus || tokens.at(i).id == Minus) && found == Number) {
            found = Plus;
            iter = i;
        }
        else if ((tokens.at(i).id == Multiply || tokens.at(i).id == Divide) && (found == Plus || found == Number)) {
            found = Multiply;
            iter = i;
        }
        else if ((tokens.at(i).id == power) && (found == Plus || found == Number || found == Multiply)) {
            found = power;
            iter = i;
        }
    }
    return iter;
}

bool Interpreter::beforeAfterNumber(int n) {
    return !(tokens.at(n - 1).id != Number &&
        tokens.at(n - 1).id != P &&
        tokens.at(n - 1).id != E &&
        tokens.at(n + 1).id != Number &&
        tokens.at(n + 1).id != P &&
        tokens.at(n + 1).id != E);
}

void Interpreter::checkParentheses() {
    int deepness = 0;
    for (int i = 0; i < tokens.Size(); i++) {
        if (debug) {
            cout << i << '\t';
        }
        if (tokens.at(i).id == OpenParentheses)
            deepness++;
        else if (tokens.at(i).id == CloseParentheses)
            deepness--;
        if (deepness < 0)
            throw Exception("Invalid Parentheses placement at i");
    }
    if (deepness != 0)
        throw Exception("something wrong about parentheses");
}

void Interpreter::solver() {
    int next;
    while (tokens.Size() > 1) {
        next = findNext();
        if (debug) {
            printTokens();
            cout << "To do " << next << endl;
        }
        switch (tokens.at(next).id) {
        case Plus:
            if (!beforeAfterNumber(next))
                throw Exception("Can't solve operator at " + to_string(tokens.at(next).pos + 1) + " ErrNo.12");
            tokens.at(next - 1).number = tokens.at(next - 1).number + tokens.at(next + 1).number;
            tokens.remove(next), tokens.remove(next);
            break;
        case Minus:
            if (!beforeAfterNumber(next))
                throw Exception("Can't solve operator at " + to_string(tokens.at(next).pos + 1) + " ErrNo.12");
            tokens.at(next - 1).number = tokens.at(next - 1).number - tokens.at(next + 1).number;
            tokens.remove(next), tokens.remove(next);
            break;
        case Multiply:
            if (!beforeAfterNumber(next))
                throw Exception("Can't solve operator at " + to_string(tokens.at(next).pos + 1) + " ErrNo.12");
            tokens.at(next - 1).number = tokens.at(next - 1).number * tokens.at(next + 1).number;
            tokens.remove(next), tokens.remove(next);
            break;
        case Divide:
            if (!beforeAfterNumber(next))
                throw Exception("Can't solve operator at " + to_string(tokens.at(next).pos + 1) + " ErrNo.12");
            if (tokens.at(next + 1).number.isZero())
                throw Exception("Divide by zero ErrNo.13");
            tokens.at(next - 1).number = tokens.at(next - 1).number / tokens.at(next + 1).number;
            tokens.remove(next), tokens.remove(next);
            break;
        case OpenParentheses:
            if (!(tokens.at(next + 1).id == Number && tokens.at(next + 2).id == CloseParentheses))
                throw Exception("Can't solve operator at " + to_string(tokens.at(next).pos + 1) + " ErrNo.14");
            tokens.remove(next + 2), tokens.remove(next);
            break;
        case TokenIndicator::sin:
            tokens.at(next + 1).number = MyMath::sin(tokens.at(next + 1).number);
            tokens.remove(next);
            break;
        case TokenIndicator::cos:
            tokens.at(next + 1).number = MyMath::cos(tokens.at(next + 1).number);
            tokens.remove(next);
            break;
        case TokenIndicator::tan:
            tokens.at(next + 1).number = MyMath::tan(tokens.at(next + 1).number);
            tokens.remove(next);
            break;
        case cot:
            tokens.at(next + 1).number = MyMath::cot(tokens.at(next + 1).number);
            tokens.remove(next);
            break;
        case sec:
            tokens.at(next + 1).number = MyMath::sec(tokens.at(next + 1).number);
            tokens.remove(next);
            break;
        case csc:
            tokens.at(next + 1).number = MyMath::csc(tokens.at(next + 1).number);
            tokens.remove(next);
            break;
        case abs1:
            tokens.at(next + 1).number = MyMath::abs(tokens.at(next + 1).number);
            tokens.remove(next);
            break;
        case degree:
            tokens.at(next + 1).number = MyMath::degree(tokens.at(next + 1).number);
            tokens.remove(next);
            break;
        case grad:
            tokens.at(next + 1).number = MyMath::grad(tokens.at(next + 1).number);
            tokens.remove(next);
            break;
        case factorial:
            tokens.at(next + 1).number = MyMath::factorial(tokens.at(next + 1).number);
            tokens.remove(next);
            break;
        case toDegree:
            tokens.at(next + 1).number = MyMath::toDegree(tokens.at(next + 1).number);
            tokens.remove(next);
            break;
        case ToGrad:
            tokens.at(next + 1).number = MyMath::toGrad(tokens.at(next + 1).number);
            tokens.remove(next);
            break;
        case ePowerTo:
            tokens.at(next + 1).number = MyMath::ePowerTo(tokens.at(next + 1).number);
            tokens.remove(next);
            break;
        case ln:
            tokens.at(next + 1).number = MyMath::ln(tokens.at(next + 1).number);
            tokens.remove(next);
            break;
        case power:
            tokens.at(next + 1).number = MyMath::power(tokens.at(next - 1).number, tokens.at(next + 1).number);
            tokens.remove(next);
            break;
        case TokenIndicator::sinh:
            tokens.at(next + 1).number = MyMath::sinh(tokens.at(next + 1).number);
            tokens.remove(next);
            break;
        case TokenIndicator::cosh:
            tokens.at(next + 1).number = MyMath::cosh(tokens.at(next + 1).number);
            tokens.remove(next);
            break;
        case TokenIndicator::tanh:
            tokens.at(next + 1).number = MyMath::tanh(tokens.at(next + 1).number);
            tokens.remove(next);
            break;
        case coth:
            tokens.at(next + 1).number = MyMath::coth(tokens.at(next + 1).number);
            tokens.remove(next);
            break;
        case sech:
            tokens.at(next + 1).number = MyMath::sech(tokens.at(next + 1).number);
            tokens.remove(next);
            break;
        case csch:
            tokens.at(next + 1).number = MyMath::csch(tokens.at(next + 1).number);
            tokens.remove(next);
            break;
        case arcsin:
            tokens.at(next + 1).number = MyMath::arcsin(tokens.at(next + 1).number);
            tokens.remove(next);
            break;
        case arcos:
            tokens.at(next + 1).number = MyMath::arccos(tokens.at(next + 1).number);
            tokens.remove(next);
            break;
        case arctan:
            tokens.at(next + 1).number = MyMath::arctan(tokens.at(next + 1).number);
            tokens.remove(next);
            break;
        case arccot:
            tokens.at(next + 1).number = MyMath::arccot(tokens.at(next + 1).number);
            tokens.remove(next);
            break;
        case arcsec:
            tokens.at(next + 1).number = MyMath::arcsec(tokens.at(next + 1).number);
            tokens.remove(next);
            break;
        case arccsc:
            tokens.at(next + 1).number = MyMath::arccsc(tokens.at(next + 1).number);
            tokens.remove(next);
            break;
        case arcsinh:
            tokens.at(next + 1).number = MyMath::arcsinh(tokens.at(next + 1).number);
            tokens.remove(next);
            break;
        case arccosh:
            tokens.at(next + 1).number = MyMath::arccosh(tokens.at(next + 1).number);
            tokens.remove(next);
            break;
        case arctanh:
            tokens.at(next + 1).number = MyMath::arctanh(tokens.at(next + 1).number);
            tokens.remove(next);
            break;
        case arccoth:
            tokens.at(next + 1).number = MyMath::arccoth(tokens.at(next + 1).number);
            tokens.remove(next);
            break;
        case arccsch:
            tokens.at(next + 1).number = MyMath::arccsch(tokens.at(next + 1).number);
            tokens.remove(next);
            break;
        case arcsech:
            tokens.at(next + 1).number = MyMath::arcsech(tokens.at(next + 1).number);
            tokens.remove(next);
            break;
        }
    }
}

void Interpreter::start() {
    try {
        Parser();
        NumberConversion();
        checkParentheses();
        checkTokenChain();
        if (debug) {
            printTokens();
            cout << endl;
        }
        solver();
        cout << tokens.at(0).number.getString(5);
    }
    catch (Exception& e) {
        cout << "Syntax Error\n";
        if (debug)
            cout << e.what() << endl;
    }
}

TokenType Interpreter::tokenTypeIndicator(TokenIndicator id) {
    switch (id) {
    case power:
    case Plus:
    case Minus:
    case Multiply:
    case Divide:
        return oper;
    case P:
    case E:
    case Number:
        return num;
    case OpenParentheses:
        return openPar;
    case CloseParentheses:
        return closePar;
    default:
        return func;
    }
}

