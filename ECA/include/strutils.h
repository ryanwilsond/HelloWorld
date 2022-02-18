#ifndef STRUTILS_H
#define STRUTILS_H

#include <vector>
#include <string>

using std::string;
using std::vector;

/// Converts a std::string to all lowercase letters
/// @param str  input string
/// @return copy of string (not in place)
inline string ToLower(const string& str) {
    string n_str;

    for (char c : str) {
        if (c <= 'Z' && c >= 'A') {
            n_str += c - ('Z' - 'z');
        }
    }

    return n_str;
}

/// Splits a string by delimeter
/// @param str      input string
/// @param delim    delimeter to split on (exclusive)
/// @return vector of chunks
inline vector<string> SplitStr(const string& str, const string& delim) {
    vector<string> chunks;
    string n_str = str;

    size_t pos = 0;
    while ((pos = n_str.find(delim)) != string::npos) {
        string tok = n_str.substr(0, pos);
        chunks.push_back(tok);
        n_str.erase(0, pos + delim.length());
    }

    return chunks;
}

/// Splits a string by " " delim
/// @param str      input string
/// @return vector of chunks
inline vector<string> SplitStr(const string& str) {
    return SplitStr(str, " ");
}

/// Returns if string starts with substring
/// @param str  target string
/// @param sub  sub string to check for
/// @return if found
inline bool StartswithStr(const string& str, const string& sub) {
    if (str.rfind(sub, 0) == 0) return true;
    return false;
}

/// Returns if string ends with substring
/// @param str  target string
/// @param sub  sub string to check for
/// @return if found
inline bool EndswithStr(const string& str, const string& sub) {
    if (str.length() >= sub.length()) {
        if (str.compare(str.length() - sub.length(), sub.length(), sub) == 0)
            return true;
    }

    return false;
}

/// Removes whitespace from string
/// @param str  str to copy
/// @return new str with no whitespace
inline string StripStr(const string& str) {
    string n_str = str;
    n_str = StripStr(n_str, " ");
    n_str = StripStr(n_str, "\t");
    n_str = StripStr(n_str, "\n");
    n_str = StripStr(n_str, "\r");
    return n_str;
}

/// Removes string string target string
/// @param str  str to copy
/// @param sub  substring to remove
/// @return new string
inline string StripStr(const string& str, const string& sub) {
    string n_str = str;

    while (n_str.find(sub) != string::npos) {
        n_str.erase(n_str.find(sub), sub.length());
    }

    return n_str;
}

/// Joins vector with seperator
/// @param chunks   string chunks
/// @param sep      seperator to insert in between every chunk
/// @return new string with joines elements
inline string JoinVec(const vector<string>& chunks, const string& sep) {
    string n_str;

    for (int i=0; i<chunks.size()-1; i++) {
        n_str += chunks[i];
        n_str += sep;
    }

    n_str += chunks[chunks.size()-1];

    return n_str;
}

#endif
