/* Tests for nslist */
#include <nslist>

// additional headers
#include <stdio.h>
#include <nsstring>

int main() {
    list<string> mylist = {string("Hello"), string("World"), string("!")};
    mylist.insert(string(", "), 1);
    string * myarray = (string *)mylist.to_array();
    printf("mylist: %s\n", string::join("", myarray, mylist.size()).c_str());
    printf("done\n");

    return 0;
}
