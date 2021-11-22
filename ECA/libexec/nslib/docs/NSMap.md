# NSMap

'include/nsmap': `#include <nsmap>`

The class you use is `map` (not inside namespace).

```cpp
#include <nsmap>

map<char, int> mymap;
unordered_map<char, int> myunorderedmap;
```

## Features

List of functions with summaries (not including operators).

| name | description |
|-|-|
| value | get the value of the key pair |
| insert | insert a key value pair into the array |

## Implementation

**Collection of {key, mapped} values, unique keys.**
**Collection of {key, mapped} values, unique keys.**

Vector where the indices are unqiue keys instead of integers, makes inserting and retrieving values much slower. Ordered map contains them in an ordered fashion using a comparison operator, average log2(n) search time. Unordered stores them in the order they are added, average n/2 search time.
