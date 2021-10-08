#include <nsstring_new>
#include <stdio.h>

string testPrints() {
    string test1 = "Hello, world!";
    string test2 = (string)'H';
    string test3 = test1;

    printf("test1: %s\ntest2: %s\ntest3: %s\n", test1.c_str(), test2.c_str(), test3.c_str());

    return test3;
}

int main() {
    string test = testPrints();

    printf("test: %s\n", test.c_str());

    string test2 = "Hello, world2?";

    test = test2;
    printf("test: %s\n", test.c_str());
    test += "..";
    printf("test: %s\n", test.c_str());
    test = test2 + "??";
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

    return 0;
}
