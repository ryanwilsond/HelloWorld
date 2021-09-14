#include "nsstring"

const char * string::c_str() {
    return (const char *)this->strValue;
}

char string::operator[](int i) {
    return this->strValue[i];
}

bool string::operator==(string n) {
    if (this->strValue == n.c_str()) return true;
    return false;
}

bool string::operator==(const char * n) {
    if (this->strValue == (char *)n) return true;
    return false;
}

bool string::operator==(char n) {
    string ns = n;
    if (this->strValue == ns.strValue) return true;
    return false;
}

bool string::operator!=(string n) {
    if (this->strValue != n.c_str()) return true;
    return false;
}

bool string::operator!=(const char * n) {
    if (this->strValue != (char *)n) return true;
    return false;
}

bool string::operator!=(char n) {
    string ns = n;
    if (this->strValue != ns.strValue) return true;
    return false;
}

void string::operator+=(string n) {
    vector<char> q;
    for (int i=0; i<strlen(this->strValue); i++) {
        q.append(this->strValue[i]);
    }
    for (int i=0; i<strlen(n.c_str()); i++) {
        q.append(n.c_str()[i]);
    }
    this->strValue = q.toArray();
}

void string::operator+=(const char * n) {
    vector<char> q;
    for (int i=0; i<strlen(this->strValue); i++) {
        q.append(this->strValue[i]);
    }
    for (int i=0; i<strlen(n); i++) {
        q.append(n[i]);
    }
    this->strValue = q.toArray();
}

void string::operator+=(char n) {
    vector<char> q;

    for (int i=0; i<strlen(this->strValue); i++) {
        q.append(this->strValue[i]);
    }

    q.append(n);
    q.append('\00');

    this->strValue = (char *)string(q.toArray()).c_str();
}

string string::operator+(string n) {
    string ret = this->strValue;
    ret += n;
    return ret;
}

string string::operator+(const char * n) {
    string ret = this->strValue;
    ret += n;
    return ret;
}

string string::operator+(char n) {
    string ret = this->strValue;
    ret += n;
    return ret;
}

vector<string> string::split(string delim) {
    vector<string> ret;
    return ret;
}

vector<string> string::split(const char * delim) {
    vector<string> ret;
    return ret;
}

vector<string> string::split(char delim) {
    vector<string> ret;
    string cur;
    for (int i=0; i<strlen(this->strValue); i++) {
        if (this->strValue[i] == delim) {
            ret.append(cur);
            cur = "";
        } else {
            cur += this->strValue[i];
        }
    }
    ret.append(cur);
    return ret;
}

bool string::startswith(string n) {
    return false;
}

bool string::startswith(const char * n) {
    return false;
}

bool string::startswith(char n) {
    if (this->strValue[0] == n) return true;
    else return false;
}
