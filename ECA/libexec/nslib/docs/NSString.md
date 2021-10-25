# NSString

'include/nsstring': `#include <nsstring>`

The class you use is `string` (not inside namespace).

```cpp
#include <nsstring>

string mystring = "Hello, world!";
```

## Features

List of functions with summaries (not including operators).

| name | alises | description |
|-|-|-|
| c_str | | returns a _Elem\* (usally char*) representation of the string |
| size | length | gets the size of the interal char* |
| startswith | | checks if string starts with substring |
| endswith | | checks if string ends with substring |
| contains | | checks if string contains substring (anywhere) |
| split | | returns a vector, or array with string chuncks split up on delimeter |
| join | | joins vector or array with delimeter |
| substring | | gets substring from start index to end index (inclusive) |
| lower | | returns lowercase version of string |
| upper | | returns uppercase version of string |
| data | | returns const character array (not a copy) |
| index | | gets _Elem at index (supports negative indexing) |

## Implementation

String class that can convert char, const char\*, char*, and const string& into itself. Will maybe add std::string conversion.

The string works as an internal char*, and whenver a impossible operation would occur, it will hide all the nasty details. For examle, if you concatinate two strings, it will actually delete its internal representation, and make a new one that is big enough to hold both strings.
