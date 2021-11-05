# NSHeap

The heap is not meant to be interacted with dirrectly, only used with other parts of NSLib.

If you really want to allocation dirrectly:

```cpp
#include <xnsmem0>

int * myarr = (int *)nsmalloc(sizeof(int) * 10);
```

## Features

Allocation of memory chunks and releasing of chunks allowing reallocation of that space.

## Implementation

Not implemented.
