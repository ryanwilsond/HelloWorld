# NSLib Developer Details

## NSString

'include/nsstring'

### Features

You can view function docstrings in the source, here is a list of functions with summaries (not including operators).

| name | description |
|-|-|
| length | gets the size of the interal char* |
| c_str | returns a char* representation of the string |
| isUpperCaseChar | checks if a character is uppercase |
| lowerChar | converts char to lowercase |
| lower | returns string with all uppercase letters replaced with lowercase letters |
| split | returns a vector with string chuncks split up on delimeter |
| startswith | checks if string starts with substring |
| endswith | checks if string ends with substring |
| size | same as length (basically) returns size_t |
| contains | checks if string contains substring (anywhere) |
| join | joins vector with delimeter |
| copy | creates string copy |

## NSVector

'include/nsvector'

### Features

| name | description |
|-|-|
| append | push_back (adds element to the end) |
| index | gets the value at index |
| count | gets number of elements in the array |
| alloc | gets the current amount of space reserved for the array |
| toArray | returns pointer-array of elements |
| pop | removes value at index and shifts the rest of the array (default last element) |

## NSIO

'include/nsio'

### Features

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

### NSString

String class that can convert char, const char*, char*, and const string& into itself. Will maybe add std::string conversion.

The string works as an internal char*, and whenver a impossible operation would occur, it will hide all the nasty details. For examle, if you append two strings, it will actually delete its internal representation, and make a new one that is big enough to hold both strings.

### NSVector

Vector class is a dynamically allocatable array.

It works with an internal pointer array of <class T>, and allocates some extra room to be faster. Then when the space is used up, it deletes itself, makes a bigger internal representation, and copies all the old elements over. Most operations just make a new modified copy of itself, then sets the internal representation to that new modified copy.

### NSIO

File class that has static methods that abstract the current <fstream> a little. This includes static functions like file::ReadAllText(string filename) which will attempt to find filename, and return the contents in a string (from nslib). There is also an overload to check how the function failed. file::ReadAllText(string filename, string * _buf) which instead writes to _buf and returns the error.
