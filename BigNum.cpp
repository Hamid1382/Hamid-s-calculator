#include "BigNum.h"
BigNum::BigNum() {
    this->digits = "0";
    this->precision = 0;
    this->Negative = false;
}

void BigNum::setValue(string& s) {
    if (s.empty())
        s = "0";
    while (s[0] == '0')
        s.erase(0, 1);
    if (s[0] == '-') {
        this->Negative = true;
        s.erase(0, 1);
    }
    else if (s[0] == '+') {
        this->Negative = false;
        s.erase(0, 1);
    }
    else {
        this->Negative = false;
    }
    reverse(s.begin(), s.end());
    size_t tmp = s.find('.');
    if (tmp == -1)
        this->precision = 0;
    else {
        this->precision = tmp;
        s.erase(tmp, 1);
    }
    for (char& i : s) {
        if (!(i >= '0' && i <= '9'))
            throw exception();
        i -= '0';
    }
    this->digits = s;
}

string BigNum::getString(int newPrecision) {
    if (this->isZero()) {
        string s = "0";
        return s;
    }
    this->trim();
    if (newPrecision == -1)
        newPrecision = this->maxPrecision;
    string s = this->digits;
    for (char& i : s)
        i += '0';
    while (s.length() <= this->precision)
        s += "0";
    if (this->precision) {
        s.insert(s.begin() + this->precision, '.');
    }
    if (this->Negative)
        s += '-';
    if (this->precision > newPrecision)
        s.erase(0, this->precision - newPrecision);
    if (newPrecision == 0 && this->precision != 0)
        s.erase(0, 1);
    reverse(s.begin(), s.end());
    if (s == "")
        s = "0";
    return s;
}

BigNum& BigNum::operator=(BigNum other) {
    if (this != &other) {
        this->digits = other.digits;
        this->Negative = other.Negative;
        this->precision = other.precision;
    }
    return *this;
}

BigNum& BigNum::operator=(long long int other) {
    string s = to_string(other);
    this->setValue(s);
    return *this;
}

BigNum& BigNum::operator=(long double other) {
    string s = to_string(other);
    this->setValue(s);
    return *this;
}

BigNum& BigNum::operator=(int other) {
    string s = to_string(other);
    this->setValue(s);
    return *this;
}

BigNum& BigNum::operator=(short other) {
    string s = to_string(other);
    this->setValue(s);
    return *this;
}

BigNum& BigNum::operator=(unsigned long long int other) {
    string s = to_string(other);
    this->setValue(s);
    return *this;
}

BigNum& BigNum::operator=(unsigned int other) {
    string s = to_string(other);
    this->setValue(s);
    return *this;
}

BigNum& BigNum::operator=(unsigned short other) {
    string s = to_string(other);
    this->setValue(s);
    return *this;
}

void BigNum::convertPrecision(long long newPrecision) {
    if (newPrecision <= this->precision)
        return;
    for (long long i = 0; i < newPrecision - this->precision; ++i) {
        this->digits.insert(this->digits.begin(), '0');
        this->digits[0] -= '0';
    }
    this->precision = newPrecision;
}

BigNum::BigNum(short i) {
    string s = to_string(i);
    this->setValue(s);
}

BigNum::BigNum(unsigned short i) {
    string s = to_string(i);
    this->setValue(s);
}

BigNum::BigNum(unsigned int i) {
    string s = to_string(i);
    this->setValue(s);
}

BigNum::BigNum(int i) {
    string s = to_string(i);
    this->setValue(s);
}

BigNum::BigNum(unsigned long ull) {
    string s = to_string(ull);
    this->setValue(s);
}

BigNum::BigNum(long long int ll) {
    string s = to_string(ll);
    this->setValue(s);
}

BigNum::BigNum(long double ld) {
    string s = to_string(ld);
    this->setValue(s);
}

BigNum::BigNum(string s) {
    this->setValue(s);
}

void BigNum::trim() {
    while (digits[0] == 0 && precision > 0 && digits.length() > 1) {
        digits.erase(0, 1);
        precision--;
    }
    short tmp, tmp2;
    while (precision > maxPrecision) {
        tmp = digits[0];
        digits.erase(0, 1);
        if (tmp > 5) {
            tmp = 1 + digits[0];
            digits[0] = tmp % 10;
            digits[1] += tmp / 10;
        }
        precision--;
    }
    while (digits[digits.length() - 1] == 0)
        digits.erase(digits.length() - 1, 1);
}

short BigNum::compare(BigNum other) {
    if (this == &other)
        return 0;
    if (this->Negative ^ other.Negative) {
        if (other.Negative)
            return 1;
        return -1;
    }
    if (this->digits.length() - this->precision > other.digits.length() - other.precision)
        return 1;
    if (this->digits.length() - this->precision < other.digits.length() - other.precision)
        return -1;
    this->precision > other.precision ? other.convertPrecision(this->precision) :
        this->convertPrecision(other.precision);
    for (int i = 0; i < this->digits.length(); i++) {
        if (this->digits[i] > other.digits[i])
            return 1;
        if (this->digits[i] < other.digits[i])
            return -1;
    }
    return 0;
}

BigNum& BigNum::operator+(BigNum Other) {
    this->precision > Other.precision ? Other.convertPrecision(this->precision) :
        this->convertPrecision(Other.precision);
    static BigNum result;
    result.precision = Other.precision;
    result.digits = "";
    int holder = 0;
    if (this->Negative ^ Other.Negative) {
        short situation = this->abs().compare(Other.abs());
        result.Negative = (this->abs().compare(Other.abs()) == 1) ^ (!this->Negative);
        if (situation == 0) {
            result.digits = "0";
            result.Negative = false;
            result.precision = 0;
        }
        else if (situation == 1) {
            int tmp;
            for (int i = 0; i < max(this->digits.length(), Other.digits.length()); i++) {
                if (i < min(this->digits.length(), Other.digits.length())) {
                    tmp = this->digits[i] - Other.digits[i] + holder;
                }
                else {
                    tmp = this->digits[i] + holder;
                }
                if (tmp >= 0) {
                    result.digits += to_string(tmp);
                    holder = 0;
                }
                else {
                    result.digits += to_string(tmp + 10);
                    holder = -1;
                }
            }
        }
        else {
            int tmp;
            for (int i = 0; i < max(this->digits.length(), Other.digits.length()); i++) {
                if (i < min(this->digits.length(), Other.digits.length())) {
                    tmp = Other.digits[i] - this->digits[i] + holder;
                }
                else {
                    tmp = Other.digits[i] + holder;
                }
                if (tmp >= 0) {
                    result.digits += to_string(tmp);
                    holder = 0;
                }
                else {
                    result.digits += to_string(tmp + 10);
                    holder = -1;
                }
            }
        }
    }
    else {
        result.Negative = this->Negative;
        short tmp;
        int n = max(this->digits.length(), Other.digits.length());
        for (int i = 0; i < n; i++) {
            if (i < min(this->digits.length(), Other.digits.length())) {
                tmp = this->digits[i] + Other.digits[i] + holder;
            }
            else {
                tmp = (this->digits.length() > Other.digits.length() ? this->digits[i] : Other.digits[i]) + holder;
            }
            if (tmp < 10) {
                result.digits += to_string(tmp);
                holder = 0;
            }
            else {
                result.digits += to_string(tmp - 10);
                holder = 1;
            }
        }
    }
    if (holder != 0)
        result.digits += '1';
    for (char& c : result.digits) {
        c -= '0';
    }
    return result;
}

BigNum BigNum::operator-(BigNum other) {
    other.Negative = !other.Negative;
    return *this + other;
}

BigNum BigNum::operator*(BigNum other) {
    if (this->isZero() || other.isZero())
        return BigNum("0");
    if (this->compare(BigNum("1")) == 0)
        return other;
    if (other.compare(BigNum("1")) == 0)
        return *this;
    this->trim();
    other.trim();
    BigNum result;
    result.digits = "";
    result.Negative = this->Negative ^ other.Negative;
    result.precision = this->precision + other.precision;
    const size_t n = this->digits.length() + other.digits.length() + 1;
    short* tmp = new short[n], tmp2;
    for (int c = 0; c < n; c++) {
        tmp[c] = 0;
    }
    for (int i = 0; i < this->digits.length(); i++) {
        for (int j = 0; j < other.digits.length(); j++) {
            tmp[i + j] += (short)this->digits[i] * other.digits[j];
        }
    }
    for (int c = 0; c < n - 1; c++) {
        tmp2 = tmp[c] / 10;
        tmp[c] %= 10;
        tmp[c + 1] += tmp2;
    }
    size_t wasted = 0;
    while (true) {
        if (tmp[n - 1 - wasted] != 0)
            break;
        wasted++;
    }

    for (int c = 0; c < n - wasted; c++) {
        result.digits += (char)tmp[c];
    }
    return result;
}

BigNum BigNum::abs() {
    BigNum result(*this);
    result.Negative = false;
    return result;
}
bool BigNum::isZero() {
    if (this->digits == "" || this->digits == "0")
        return true;
    bool is = true;
    for (char& i : this->digits) {
        if (i != '0') {
            is = false;
            break;
        }
    }
    if (is) {
        string s = "0";
        this->setValue(s);
    }
    return is;
}

void BigNum::operator++() {
    if (this->compare(BigNum("9")) == 0) {
        string s = "10";
        this->setValue(s);
        return;
    }
    if (this->digits.length() == 1) {
        this->digits[0]++;
        return;
    }
    short tmp = this->digits[0];
    tmp++;
    this->digits[0] = tmp % 10;
    this->digits[1] += tmp / 10;
}
BigNum BigNum::operator/ (BigNum other) {
    if (this->isZero())
        return BigNum("0");
    if (other.isZero())
        throw exception();
    size_t n1 = this->digits.length() + maxPrecision;
    short* maqsum = new short[n1];
    int offset = 0;
    for (int i = 0; i < n1; i++) {
        if (this->digits.length() - i >= 0)
            maqsum[i] = this->digits[this->digits.length() - 1 - i];
        else
            maqsum[i] = 0;
    }
    size_t n2 = other.digits.length();
    short* elaih = new short[other.digits.length()];
    for (int i = 0; i < n2; i++) {
        elaih[i] = other.digits[n2 - 1 - i];
    }
    while (maqsum[n1 - 1] == 0 && elaih[n2 - 1] == 0) {
        n1--;
        n2--;
    }
    size_t n3;
    short* result;
    BigNum res;
    res.precision = this->precision - other.precision + maxPrecision;
    if (n1 < n2) {
        result = new short[1];
        n3 = 1;
        result[0] = 0;
    }
    else if (n1 == 1 && n2 == 1) {
        n3 = 1;
        result = new short[1];
        result[0] = maqsum[0] / elaih[0];
    }
    else if (n2 == 1) {
        n3 = n1;
        result = new short[n1];
        int tmp;
        for (int i = 0; i < n1; i++) {
            tmp = maqsum[i];
            result[i] = tmp / elaih[0];
            if (i + 1 < n1)
                maqsum[i + 1] += (tmp % elaih[0]) * 10;
        }
    }
    else if (n1 == n2) {
        n3 = 1;
        result = new short[1];
        bool toBreak;
        while (true) {
            for (int i = 0; i < n1; i++) {
                if (maqsum[i] > elaih[i]) {
                    toBreak = false;
                    break;
                }
                if (maqsum[i] < elaih[i]) {
                    toBreak = true;
                    break;
                }
            }
            if (toBreak)
                break;
            for (int i = 0; i < n1; i++) {
                maqsum[i] -= elaih[i];
            }
            result[0]++;
        }
    }
    else {
        n3 = n1;
        result = new short[n1];
        for (int i = 0; i < n1; i++)
            result[i] = 0;
        bool toBreak;
        while (true) {
            toBreak = true;
            for (int i = offset; i < n1; i++) {
                if (maqsum[i] > 0) {
                    toBreak = false;
                    break;
                }
            }
            if (toBreak)
                break;
        check:
            if (maqsum[offset] < elaih[0]) {
                if (offset + 2 == n1)
                    break;
                else {
                    short tmp = maqsum[offset];
                    maqsum[offset++] = 0;
                    maqsum[offset] += tmp * 10;
                }
            }
            for (int i = 1; i < n2; i++) {
                if (maqsum[i + offset] < elaih[i]) {
                    if (n1 - offset == n2) {
                        toBreak = true;
                        break;
                    }
                    else if (maqsum[i + offset] > elaih[i])
                        break;
                    else {
                        int whereToPeak = 1;
                        while (maqsum[i + offset - whereToPeak] == 0)
                            whereToPeak++;
                        while (whereToPeak >= 0) {
                            maqsum[i + offset - whereToPeak]--;
                            maqsum[i + offset - whereToPeak + 1] += 10;
                        }
                        goto check;
                    }

                }
            }
            for (int i = 0; i < n2; i++) {
                maqsum[i + offset] -= elaih[i];
            }
            result[offset]++;
        }
        res.precision = this->precision - other.precision + maxPrecision + n2 - 1;
    }
    res.digits = "";
    for (int i = n3 - 1; i >= 0; i--)
        res.digits += result[i];
    res.trim();
    delete[] maqsum;
    delete[] elaih;
    return res;
}