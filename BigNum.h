#pragma once
#include <string>
#include <exception>
#include <iostream>
#include <algorithm>
using std::cin;
using std::cout;
using std::getline;
using std::endl;
using std::min;
using std::max;
using std::string;
using std::exception;
using std::reverse;
using std::to_string;

class BigNum {
public:
    const int maxPrecision = 7;
    std::string digits;
    long long precision;
    bool Negative;
    /**
     * base constructor.
     */
    BigNum();
    /**
     * constructor, initials number.
     * @param s string that contains the number.
     */
    BigNum(std::string s);
    /**
     * constructor, initials number.
     * @param ld long double that contains the number.
     */
    BigNum(long double ld);
    /**
     * constructor, initials number.
     * @param ll long long that contains the number.
     */
    BigNum(long long ll);
    /**
     * constructor, initials number.
     * @param ull unsigned long long that contains the number.
     */
    BigNum(unsigned long ull);
    /**
     * constructor, initials number.
     * @param i int unsigned long long that contains the number.
     */
    BigNum(int i);
    /**
     * constructor, initials number.
     * @param i unsigned int unsigned long long that contains the number.
     */
    BigNum(unsigned int i);
    /**
     * constructor, initials number.
     * @param i unsigned short unsigned long long that contains the number.
     */
    BigNum(unsigned short i);
    /**
     * constructor, initials number.
     * @param i short unsigned long long that contains the number.
     */
    BigNum(short i);
    /**
     * changes the value
     * @param s strings that contains the number.
     */
    void setValue(std::string& s);
    /**
     * converts the number to string.
     * @param newPrecision count of digits come after dot(-1 means all, default value)
     * @return string that contains the number.
     */
    std::string getString(int newPrecision = -1);
    /**
     * function to overload = operator
     * @param other BigNum on the Right
     * @return reference for multi-assign situation
     */
    BigNum& operator= (BigNum other);
    /**
     * function to overload = operator
     * @param other long long int on the Right
     * @return reference for multi-assign situation
     */
    BigNum& operator= (long long other);
    /**
     * function to overload = operator
     * @param other long double on the Right
     * @return reference for multi-assign situation
     */
    BigNum& operator= (long double other);
    /**
     * function to overload = operator
     * @param other int on the Right
     * @return reference for multi-assign situation
     */
    BigNum& operator= (int other);
    /**
     * function to overload = operator
     * @param other short int on the Right
     * @return reference for multi-assign situation
     */
    BigNum& operator= (short other);
    /**
     * function to overload = operator
     * @param other unsigned long long int on the Right
     * @return reference for multi-assign situation
     */
    BigNum& operator= (unsigned long long other);
    /**
     * function to overload = operator
     * @param other unsigned int on the Right
     * @return reference for multi-assign situation
     */
    BigNum& operator= (unsigned int other);
    /**
     * function to overload = operator
     * @param other unsigned short int on the Right
     * @return reference for multi-assign situation
     */
    BigNum& operator= (unsigned short other);
    /**
     * increases digits with zero for internal jobs.
     * @param newPrecision must be bigger than original.
     */
    void convertPrecision(long long newPrecision);
    /**
     * function to overload + operation(sum)
     * @param Other BigNum on right
     * @return result
     */
    BigNum& operator+ (BigNum Other);
    /**
     * compares this big number to another
     * @return
     */
    short compare(BigNum other);
    /**
     * removes additional zeroes after floating point.
     */
    void trim();
    /**
     * function to overload - operator
     * @param other BigNum on right
     * @return result
     */
    BigNum operator- (BigNum other);
    /**
     * a function to overload * operator
     * @param other BigNum on right
     * @return BigNum
     */
    BigNum operator* (BigNum other);
    /**
     * @return absolute value of the number;
     */
    BigNum abs();
    /**
     * a function to overload / operator
     * @param other BigNum on right
     * @return result
     */
    BigNum operator/ (BigNum other);
    /**
     * checks if the number is zero
     * @return true if it is zero false if it isn't
     */
    bool isZero();
    void operator++ ();
};

