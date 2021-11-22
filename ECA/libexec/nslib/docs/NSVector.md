# NSVector

'include/nsvector': `#include <nsvector>`

The class you use is `vector` (not inside namespace).

```cpp
#include <nsvector>

vector<int> myintvec = {1, 2, 3, 4};
```

## Features

List of functions with summaries (not including operators).

| name | description |
|-|-|
| append | adds element to the end of array |
| pop | pops last element of the array or at index |
| count | gets number of elements in the array |
| size | gets the size of the array |
| index | gets the value at index |
| to_array | returns pointer-array of elements |

## Implementation

**Varying size array of values.**

It works with an internal pointer array of \<class T\>, and allocates some extra room to be faster. Then when the space is used up, it deletes itself, makes a bigger internal representation, and copies all the old elements over. Most operations just make a new modified copy of itself, then sets the internal representation to that new modified copy.
