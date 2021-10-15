# NSLib Developer Details

## NSString

'include/nsstring'

### Features

You can view function docstrings in the source, here is a list of functions with summaries (not including operators).

| name | alises | description |
|-|-|
| c_str | returns a _Elem* (usally char*) representation of the string |
| size | length | gets the size of the interal char* |
| startswith | checks if string starts with substring |
| endswith | checks if string ends with substring |
| contains | checks if string contains substring (anywhere) |
| split | returns a vector, or array with string chuncks split up on delimeter |
| join | joins vector or array with delimeter |

## NSVector

'include/nsvector'

### Features

| name | aliases | description |
|-|-|
| push_back | append | adds element to the end of array |
| pop_back | pop | pops last element of the array |
| pop | pops element at index |
| size | count | gets number of elements in the array |
| index | gets the value at index |
| to_array | returns pointer-array of elements |

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

The string works as an internal char*, and whenver a impossible operation would occur, it will hide all the nasty details. For examle, if you concatinate two strings, it will actually delete its internal representation, and make a new one that is big enough to hold both strings.

### NSVector

Vector class is a dynamically allocatable array.

It works with an internal pointer array of \<class T\>, and allocates some extra room to be faster. Then when the space is used up, it deletes itself, makes a bigger internal representation, and copies all the old elements over. Most operations just make a new modified copy of itself, then sets the internal representation to that new modified copy.

### NSIO

File class that has static methods that abstract the current \<fstream\> a little. This includes static functions like file::ReadAllText(string filename) which will attempt to find filename, and return the contents in a string (from nslib). There is also an overload to check how the function failed. file::ReadAllText(string filename, string * _Buf) which instead writes to _Buf and returns the error.
