// Tests for nsmap
#include <nsmap>

// additional headers
#include <stdio.h>

int main() {
    map<char, int> mymap = {
        make_pair('a', 1),
        make_pair('b', 2),
        make_pair('c', 3),
        make_pair('d', 4),
        make_pair('f', 6),
    };

    mymap.insert('e', 5);

    for (int i=0; i<mymap.size(); i++) {
        printf("%c:%i, ", mymap.keys()[i], mymap[mymap.keys()[i]]);
    } printf("\n");

    return 0;
}
