/* Tests for nsio */
#include <nsio>

// additional headers
#include <stdio.h>
#include <nsstring>

int main() {
    string filename = "textfile.txt";
    string filecontent = "this is a test file\ntesting\ntesting\n123\n";
    file::WriteAllText(filename, filecontent);
    printf("created file\n");
    string readcontent = file::ReadAllText(filename);
    printf("filecontent: %s\n", readcontent.c_str());
    file::DeleteFile(filename);
    printf("done\n");

    return 0;
}
