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
