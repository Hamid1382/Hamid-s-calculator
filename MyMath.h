#pragma once
#include "BigNum.h"
class MyMath {
public:
    static const long long maxSteps = 330;
    static BigNum sin(BigNum radians);
    static BigNum cos(BigNum radians);
    static BigNum tan(BigNum radians);
    static BigNum cot(BigNum radians);
    static BigNum sec(BigNum radians);
    static BigNum csc(BigNum radians);
    static BigNum abs(BigNum x);
    static BigNum degree(BigNum degrees);
    static BigNum grad(BigNum grads);
    static BigNum factorial(BigNum x);
    static BigNum toDegree(BigNum radian);
    static BigNum toGrad(BigNum radian);
    static BigNum ePowerTo(BigNum x);
    static BigNum ln(BigNum x);
    static BigNum power(BigNum paye, BigNum nama);
    static BigNum sinh(BigNum radians);
    static BigNum cosh(BigNum radians);
    static BigNum tanh(BigNum radians);
    static BigNum coth(BigNum radian);
    static BigNum sech(BigNum radian);
    static BigNum csch(BigNum radian);
    static BigNum arcsin(BigNum x);
    static BigNum arccos(BigNum x);
    static BigNum arctan(BigNum x);
    static BigNum arccot(BigNum x);
    static BigNum arcsec(BigNum x);
    static BigNum arccsc(BigNum radian);
    static BigNum arcsinh(BigNum radian);
    static BigNum arccosh(BigNum radian);
    static BigNum arctanh(BigNum x);
    static BigNum arccoth(BigNum x);
    static BigNum arccsch(BigNum x);
    static BigNum arcsech(BigNum x);
};

