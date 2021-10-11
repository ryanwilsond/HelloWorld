/*
This code is not meant to be used, nor is it written well.
This is purely a quick way to test the functionality of functions.
*/

#include <nsstring>
#include <nsvector>
#include <stdio.h>

string testPrints() {
    string test1 = "Hello, world!";
    string test2 = (string)'H';
    string test3 = test1;

    printf("test1: %s\ntest2: %s\ntest3: %s\n", test1.c_str(), test2.c_str(), test3.c_str());

    return test3;
}

// tests nsstring & nsvector operators and functions
int main() {
    printf("before\n");
    vector<int> testvec = {1, 2, 3};
    testvec.append(4);
    printf("exit?\n");
    for (int i=0; i<testvec.count(); i++)
        {
            printf("%i\n", testvec[i]);
        }
    // return 0;
    string test = testPrints();

    printf("test: %s\n", test.c_str());

    string test2 = "Hello, world2?";

    test = test2;
    printf("test: %s\n", test.c_str());
    test += "..";
    printf("test: %s\n", test.c_str());
    test = test2 + "??";
    test += ';';
    printf("test: %s\n", test.c_str());

    if (test.startswith('H')) {
        printf("test starts with H\n");
    }
    if (test.startswith('e')) {
        printf("test starts with e\n");
    }
    if (test.startswith("Hello")) {
        printf("test starts with Hello\n");
    }
    if (test.startswith("World")) {
        printf("test starts with World\n");
    }
    if (test.endswith("???")) {
        printf("test ends with ???\n");
    }
    if (test.endswith('?')) {
        printf("test ends with ?\n");
    }
    if (test.endswith("asdf")) {
        printf("test ends with asdf\n");
    }
    if (test.endswith('a')) {
        printf("test ends with a\n");
    }

    test = test.substring(1);
    printf("test: %s\n", test.c_str());

    if (test.contains("lo, ")) {
        printf("test contains 'lo, '\n");
    }
    if (test.contains("Hello")) {
        printf("test contains 'Hello'\n");
    }

    // return 0;
    vector<string> splitted = test.split(", ");

    for (int i=0; i<splitted.count(); i++) {
        printf(", %s", splitted[i].c_str());
    }printf("\n\n");

    string joined = string::join(", ", splitted);
    printf("%s\n", joined.c_str());

    joined = string(", ").join(splitted);
    printf("%s\n", joined.c_str());

    splitted.append("asdf");
    joined = string::join(", ", splitted);
    printf("%s\n", joined.c_str());
    splitted.pop(1);
    joined = string::join(", ", splitted);
    printf("%s\n", joined.c_str());

    return 0;
}
