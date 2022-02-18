#ifndef IOUTILS_H
#define IOUTILS_H

#include <string>
#include <vector>
#include <fstream>


#ifndef __has_include
  static_assert(false, "__has_include not supported");
#else
#  if __cplusplus >= 201703L && __has_include(<filesystem>)
#    include <filesystem>
    //  namespace fs = std::filesystem;
    using std::filesystem::current_path;
#  elif __has_include(<experimental/filesystem>)
#    include <experimental/filesystem>
    //  namespace fs = std::experimental::filesystem;
     using std::experimental::filesystem::current_path;
#  elif __has_include(<boost/filesystem.hpp>)
#    include <boost/filesystem.hpp>
    //  namespace fs = boost::filesystem;
     using boost::filesystem::current_path;
#  else
#    define _NO_FILESYSTEM_
#    include <unistd.h>
#  endif
#endif // __has_include


class file {
private:

    file() {}

public:

    static bool FileExists(const std::string& filename) {
        std::ifstream fstream (filename.c_str());

        if (fstream.is_open()) {
            fstream.close();
            return true;
        }

        return false;
    }

    static std::string ReadAllText(const std::string& filename) {
        std::string buf;
        std::string ln_buf;
        std::ifstream fstream (filename.c_str());

        if (fstream.is_open()) {
            while (std::getline(fstream, ln_buf)) {
                buf += ln_buf.c_str();
                buf += "\n";
            }

            fstream.close();
        }

        return buf;
    }

    static std::vector<std::string> ReadAllLines(const std::string& filename) {
        std::vector<std::string> lines;
        std::string ln_buf;
        std::ifstream fstream (filename.c_str());

        if (fstream.is_open()) {
            while (std::getline(fstream, ln_buf)) {
                lines.push_back(ln_buf); // copy?
            }

            fstream.close();
        }

        return lines;
    }

    static std::vector<unsigned char> ReadAllBytes(const std::string& filename) {
        std::vector<unsigned char> bytes;
        char byte_buf;
        std::ifstream fstream (filename.c_str());

        if (fstream.is_open()) {
            while (fstream.get(byte_buf)) {
                bytes.push_back((unsigned char)byte_buf);
            }

            fstream.close();
        }

        return bytes;
    }

    static void WriteAllText(const std::string& filename, const std::string& text) {
        std::ofstream fstream (filename.c_str(), std::ofstream::binary);
        fstream.write(text.c_str(), text.size());
        fstream.close();
    }

    static void WriteAllLines(const std::string& filename, const std::vector<std::string>& lines) {
        std::ofstream fstream (filename.c_str());
        std::string text;

        for (std::string str : lines) {
            text += str;
            text += "\n";
        }

        fstream.write(text.c_str(), text.size());
        fstream.close();
    }

    static void WriteAllBytes(const std::string& filename, const std::vector<unsigned char>& bytes) {
        std::ofstream fstream (filename.c_str(), std::ios::binary);

        char cst[bytes.size()];
        std::copy(bytes.begin(), bytes.end(), cst);

        fstream.write(cst, bytes.size());
        fstream.close();
    }

    static std::string GetWorkingDir() {
    #ifdef _NO_FILESYSTEM_
        char *tmp = (char*)malloc(512); // arbitrary
        getcwd(tmp, 512);
        return std::string(tmp);
     #else
        std::string std_path = current_path().string();
        return std_path;
     #endif
        }

    static int DeleteFile(std::string filename) {
        return remove(filename.c_str());
    }

};

#endif
