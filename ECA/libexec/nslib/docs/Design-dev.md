# NSLib Developer Details

Links to each part of the library:

- NSString: [NSString.md](./NSString.md)
- NSVector: [NSVector.md](./NSVector.md)
- NSMap: [NSMap.md](./NSMap.md)
- NSList: [NSList.md](./NSList.md)
- NSIO: [NSIO.md](./NSIO.md)
- NSHeap: [NSHeap.md](./NSHeap.md)

> Note: NSIO is not an implementation, but an abstraction layer unlike the rest of nslib

This file goes over the implementation of shared functions and classes used by multiple parts of the library.

## xnsmem0

This contains an allocator class which handles all the allocation for nsstring and nsvector. This can be swapped out with your own allocator if needed.

[This also contains nslib heap implementation.](./NSHeap.md)

### allocator

Allocator functions:

| name | description |
|-|-|
| allocate | allocates bytes on the heap |
| deallocate | frees memory allocated on the heap |

## xnsdef

Collection of utils functions NOT to be used by users.

| name | description |
|-|-|
| addressof | gets address of pointer (workaround to pointer addressing issue) |
| copyinto | copies elements from an array into another array |
| posindex| converts a signed index to a positive index |

## xnsinit_list

Adds std::initializer_list to nstd namespace because it is not possible to create a custom initializer_list implementation. Only exists to prevent the rest of nslib from including standard headers.
