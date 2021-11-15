#include "nsstring"
#include "nsvector"

#include <stdio.h>

int main() {
    vector<string> test;
    test.assign(0, string("Hello, world!"));
    // test[0] = string("Hello, world!");
    printf("strres: %i, strsize: %i, strval: %s\n", (int)test[0]._Myres(), (int)test[0]._Mysize(), test[0].c_str());

    return 0;
}
