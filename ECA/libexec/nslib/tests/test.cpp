/* less formal test file */
// #define _TESTING

#ifdef _TESTING
#include <string>
#include <vector>

using std::string;
using std::vector;
#else
#include "nsstring"
#include "nsvector"
#endif

#include <stdio.h>

int main() {
    // vector<string> test;
    // test.assign(0, string("Hello, world!"));
        // cant do this because [] operator returns a value, not a pointer
        // test[0] = string("Hello, world!");
    // printf("strres: %i, strsize: %i, strval: %s\n", (int)test[0]._Myres(), (int)test[0]._Mysize(), test[0].c_str());

    // vector<int> test;
    // test.assign(0, 10);
    // test.append(11);
    // printf("value: %i, value: %i\n", test[0], test[1]);

    vector<string> test;
    unsigned int testit = 0;
    // vector<string>::iterator testit;
    // testit = test.begin();
    test.assign(testit, string("Hello, world!"));
    test.append(string("another string"));
    printf("value: %s, value: %s\n", test[0].c_str(), test[1].c_str());

    return 0;
}
