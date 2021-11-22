/* Tests for nsmap */
#include <nsmap>

// additional headers
#include <stdio.h>

int main() {
    printf("unordered\n");

    unordered_map<char, int> mymap = {
        make_pair('a', 1),
        make_pair('b', 2),
        make_pair('c', 3),
        make_pair('d', 4),
        make_pair('f', 6),
    };

    mymap.insert('e', 5);
    mymap.insert('f', 7);
    mymap.insert('j', 2);

    for (pair<char, int> p : mymap) {
        printf("%c:%i, ", p.key(), p.value());
    } printf("\n");

    printf("ordered\n");

    map<char, int> mymap2 = {
        make_pair('a', 1),
        make_pair('b', 2),
        make_pair('c', 3),
        make_pair('d', 4),
        make_pair('f', 6),
    };

    mymap2.insert('e', 5);
    mymap2.insert('f', 7);
    mymap2.insert('j', 2);

    for (pair<char, int> p : mymap2) {
        printf("%c:%i, ", p.key(), p.value());
    } printf("\n");

    printf("done\n");

    return 0;
}
