#include "MyMath.h"
#include <exception>
using std::exception;
BigNum MyMath::sin(BigNum radians) {
    BigNum Pi("3.141592653589793238462");
    BigNum two("2");
    BigNum minus1(-1);
    while (radians.compare(two * Pi) == 1)
        radians = radians - two * Pi;
    while (radians.compare(minus1 * two * Pi) == -1)
        radians = radians + (two * Pi);
    BigNum result = 0;
    BigNum power = radians;
    BigNum tmp;
    short sign = 1;
    BigNum fact = 1;
    for (int i = 1; i < 1e8; i += 2) {
        tmp = power / fact;
        if (sign == -1)
            tmp.Negative = !tmp.Negative;
        if (tmp.isZero())
            break;
        result = result + tmp;
        power = (power * radians) * radians;
        fact = fact * BigNum((i + 1) * (i + 2));
        sign *= -1;
    }
    return result;
}
BigNum MyMath::cos(BigNum radians) {
    BigNum Pi("3.141592653589793238462");
    BigNum two("2");
    BigNum minus1(-1);
    while (radians.compare(two * Pi) == 1)
        radians = radians - two * Pi;
    while (radians.compare(minus1 * two * Pi) == -1)
        radians = radians + (two * Pi);
    BigNum result = 0;
    BigNum power = 1;
    BigNum tmp;
    short sign = 1;
    BigNum fact = 1;
    for (int i = 0; i < 1e8; i += 2) {
        tmp = power / fact;
        if (sign == -1)
            tmp.Negative = !tmp.Negative;
        if (tmp.isZero())
            break;
        result = result + tmp;
        power = (power * radians) * radians;
        fact = fact * BigNum((i + 1) * (i + 2));
        sign *= -1;
    }
    return result;
}
BigNum MyMath::tan(BigNum radians) {
    BigNum Pi("3.141592653589793238462");
    BigNum minus1(-1);
    while (radians.compare(Pi) == 1)
        radians = radians - Pi;
    while (radians.compare(minus1 * Pi) == -1)
        radians = radians * Pi;
    if (radians.compare(Pi / 2) == 0 || radians.compare(Pi / (-2)) == 0)
        throw exception();
    BigNum result = radians, tmp, Pi2 = Pi * Pi, x2 = radians * radians;
    BigNum last(1000000);
    BigNum two("2"), one("1");
    for (BigNum i = 1; i.compare(last) == -1; i = i + 1) {
        tmp = (two - one / i) * (two - one / i) * ((i * i * Pi2 - x2) / ((two * i - 1) * (two * i - 1) * Pi2 - two * x2));
        if (tmp.isZero())
            break;
        result = result * tmp;
    }
    return result;
}

BigNum MyMath::cot(BigNum radians) {
    BigNum Pi("3.141592653589793238462");
    BigNum minus1(-1);
    while (radians.compare(Pi) == 1)
        radians = radians - Pi;
    while (radians.compare(minus1 * Pi) == -1)
        radians = radians * Pi;
    if (radians.isZero() || radians.compare(Pi) == 0)
        throw exception();
    BigNum last(1000000);
    BigNum two("2"), one("1"), four("4");
    BigNum result = one / radians, tmp, Pi2 = Pi * Pi, x2 = radians * radians;
    for (BigNum d = 1; d.compare(last) == -1; d = d + 1) {
        tmp = d * d / ((two * d - one) * (two * d - one)) * (Pi2 * (two * d - one) * (two * d - one) - four * x2) / (Pi2 * d * d - x2);
        result = result * tmp;
    }
    return result;

}
BigNum MyMath::sec(BigNum radians) {
    BigNum Pi("3.141592653589793238462");
    BigNum two("2");
    BigNum minus1(-1);
    BigNum one("1");
    while (radians.compare(two * Pi) == 1)
        radians = radians - two * Pi;
    while (radians.compare(minus1 * two * Pi) == -1)
        radians = radians + (two * Pi);
    if (radians.compare(Pi / 2) == 0)
        throw exception();
    return one / cos(radians);
}

BigNum MyMath::csc(BigNum radians) {
    BigNum Pi("3.141592653589793238462");
    BigNum two("2");
    BigNum minus1(-1);
    BigNum one("1");
    while (radians.compare(two * Pi) == 1)
        radians = radians - two * Pi;
    while (radians.compare(minus1 * two * Pi) == -1)
        radians = radians + (two * Pi);
    if (radians.compare(Pi / 2))
        throw exception();
    return one / sin(radians);
}

BigNum MyMath::abs(BigNum x) {
    x.Negative = false;
    return x;
}

BigNum MyMath::degree(BigNum degrees) {
    BigNum Pi("3.141592653589793238462");
    return degrees * Pi / 180;
}

BigNum MyMath::grad(BigNum grads) {
    BigNum Pi("3.141592653589793238462");
    return grads * Pi / 200;
}

BigNum MyMath::factorial(BigNum x) {
    if (x.precision > 0)
        throw exception();
    BigNum result = 1;
    for (BigNum i = 0; i.compare(x) == -1; i = i + 1)
        result = result * i;
    return result;
}

BigNum MyMath::toDegree(BigNum radian) {
    BigNum Pi("3.141592653589793238462");
    return radian * 180 / Pi;
}

BigNum MyMath::toGrad(BigNum radian) {
    BigNum Pi("3.141592653589793238462");
    return radian * 200 / Pi;
}

BigNum MyMath::ePowerTo(BigNum x) {
    BigNum result = 0;
    BigNum fact = 1, power = 1;
    for (int i = 1; i < 100; i++) {
        result = result + power / fact;
        power = power * x;
        fact = fact * i;
    }
    return result;
}

BigNum MyMath::ln(BigNum x) {
    if (x.Negative || x.isZero())
        throw exception();
    BigNum x2 = (x - 1) / (x + 1);
    BigNum power = x2;
    BigNum sum = 0;
    for (int i = 1; i < 10000; i += 2) {
        sum = sum + power / i;
        power = power * x2 * x2;
    }
    BigNum two("2");
    return two * sum;
}

BigNum MyMath::power(BigNum paye, BigNum nama) {
    return ePowerTo(nama * ln(paye));
}
BigNum MyMath::sinh(BigNum radians) {
    BigNum result = 0;
    BigNum power = radians;
    BigNum tmp;
    BigNum fact = 1;
    for (int i = 1; i < 1e8; i += 2) {
        tmp = power / fact;
        if (tmp.isZero())
            break;
        result = result + tmp;
        power = (power * radians) * radians;
        fact = fact * (i + 1) * (i + 2);
    }
    return result;
}
BigNum MyMath::cosh(BigNum radians) {
    BigNum result = 0;
    BigNum power = 1;
    BigNum tmp;
    BigNum fact = 1;
    for (int i = 0; i < 1e8; i += 2) {
        tmp = power / fact;
        if (tmp.isZero())
            break;
        result = result + tmp;
        power = (power * radians) * radians;
        fact = fact * (i + 1) * (i + 2);
    }
    return result;
}

BigNum MyMath::tanh(BigNum radians) {
    BigNum two("2");
    BigNum tmp = ePowerTo(two * radians);
    return (tmp - 1) / (tmp + 1);
}
BigNum MyMath::coth(BigNum radians) {
    BigNum two("2");
    BigNum tmp = ePowerTo(two * radians);
    return (tmp + 1) / (tmp - 1);
}

BigNum MyMath::sech(BigNum radian) {
    BigNum one("1");
    return one / cosh(radian);
}

BigNum MyMath::csch(BigNum radian) {
    BigNum one("1");
    return one / sinh(radian);
}

BigNum MyMath::arcsin(BigNum x) {
    BigNum one("1");
    BigNum minus1("-1");
    if (x.compare(one) == 1 || x.compare(minus1) == 1)
        throw exception();
    BigNum x2 = x * x, power = x2 * x, zarib = 1, sum = x;
    for (int i = 1; i < 100; i += 2) {
        zarib = zarib * i;
        zarib = zarib / (i + 1);
        sum = sum + zarib * power / (i + 2);
        power = power * x2;
    }
    return sum;
}

BigNum MyMath::arccos(BigNum x) {
    BigNum Pi("3.141592653589793238462");
    return Pi / 2 - arcsin(x);
}

BigNum MyMath::arctan(BigNum x) {
    BigNum power = x, x2 = x * x, sum = 0;
    for (int i = 1; i < 1000; i += 2) {
        sum = sum + power / i;
        power = power * x2;
    }
    return sum;
}
BigNum MyMath::arccot(BigNum x) {
    BigNum Pi("3.141592653589793238462");
    return Pi / 2 - arctan(x);
}

BigNum MyMath::arcsec(BigNum x) {
    BigNum one("1");
    return arccos(one / x);
}
BigNum MyMath::arccsc(BigNum x) {
    BigNum one("1");
    return arcsin(one / x);
}
BigNum MyMath::arcsinh(BigNum x) {
    BigNum one("1");
    BigNum x2 = x * x, power = x2 * x, zarib = -1, sum = x;
    if (abs(x).compare(one) == -1) {
        for (int i = 1; i < 100; i += 2) {
            zarib = zarib * i;
            zarib = zarib / (i + 1);
            sum = sum + zarib * power / (i + 2);
            power = power * x2;
            zarib = zarib * -1;
        }
        return sum;
    }
    else {
        BigNum two("2");
        sum = x + ln(abs(two * x));
        for (int i = 1; i < 100; i += 2) {
            zarib = zarib * i;
            zarib = zarib / (i + 1);
            sum = sum + zarib * power / (i + 1);
            power = power * x2;
            zarib = zarib * -1;
        }
        BigNum minus1("-1");
        if (x.compare(minus1) == -1)
            sum = sum * -1;
    }
    return sum;
}
BigNum MyMath::arccosh(BigNum x) {
    BigNum one("1");
    if (abs(x).compare(one) == 1)
        return ln(x + power(x * x - 1, BigNum("0.5")));
    throw exception();
}
BigNum MyMath::arctanh(BigNum x) {
    BigNum one("1");
    if (abs(x).compare(1) == 1)
        throw exception();
    BigNum x2 = x * x, sum = 0, power = x;
    for (int i = 1; i < 1000; i += 2) {
        sum = sum + power / i;
        power = power * x2;
    }
    return sum;
}
BigNum MyMath::arccoth(BigNum x) {
    BigNum one("1");
    return arctanh(one / x);
}
BigNum MyMath::arcsech(BigNum x) {
    BigNum one("1");
    return arccosh(one / x);
}

BigNum MyMath::arccsch(BigNum x) {
    BigNum one("1");
    return arcsinh(one / x);
}