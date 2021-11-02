# NSIO

'include/nsio': `#include <nsio>`

The static class name is `file` (not inside namespace).

```cpp
#include <nsio>
#include <nsstring>

string filename = "myfile.txt";
string content = file::ReadAllText(filename);
```

## Features

List of functions with summaries (not including operators).

| name | description |
|-|-|
| FileExists | checks if file exists |
| ReadAllText | reads file as string |
| ReadAllLines | reads file as vector of strings |
| ReadAllBytes | reads file as bytes |
| WriteAllText | writes file with string |
| WriteAllLines | writes file with vector (adds newlines) |
| WriteAllBytes | writes binary file with bytes |
| GetWorkingDir | gets current working directory, does this in multiple ways to make sure it works on all C++ versions |

## Implementation

> Note: This part of the libary is just an abstraction layer

**Input/output stream associated with a C stream.**

File class that has static methods that abstract the current \<fstream\> a little. This includes static functions like `string file::ReadAllText(string _File)` which will attempt to find filename, and return the contents in a string (from nslib). There is also an overload to check how the function failed. `int file::ReadAllText(string _File, string * _Buf)` which instead writes to _Buf and returns the error.
