#include "nsio"

static string ReadAllText(string f) {
    string t;
    std::string ln;
    std::ifstream file (f.c_str());

    if (file.is_open()) {
        while (std::getline(file, ln)) {
            t += ln.c_str();
        }
        file.close();
    }
    return t;
}

vector<string> file::ReadAllLines(string f) {
    vector<string> lns;
    return lns;
}

vector<byte> file::ReadAllBytes(string f) {
    vector<byte> bs;
    return bs;
}

void file::WriteAllText(string f, string d) {

}

void file::WriteAllLines(string f, vector<string> d) {

}

void file::WriteAllBytes(string f, vector<byte> d) {

}
