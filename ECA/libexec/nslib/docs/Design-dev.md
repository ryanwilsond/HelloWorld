# NSLib Developer Details

Links to each part of the library:

- NSString: [NSString.md](./NSString.md)
- NSVector: [NSVector.md](./NSVector.md)
- NSIO: [NSIO.md](./NSIO.md)
- NSMap: [NSMap.md](./NSMap.md)

This file goes over the implementation of shared functions and classes used by multiple parts of the library.

## xnsmem0

This contains an allocator class which handles all the allocation for nsstring and nsvector. This can be swapped out with your own allocator if needed.

### allocator

Allocator functions:

| name | description |
|-|-|
| allocate | allocates bytes on the heap |
| deallocate | frees memory allocated using the heap |

## xnsdef

Collection of utils functions NOT to be used by users.

| name | description |
|-|-|
| addressof | gets address of pointer (workaround to pointer addressing issue) |
| copyinto | copies elements from an array into another array |

## xnsinit_list

Custom initalizer list implementation. Mainly because the goal of nslib is to **completely** avoid all of the standard headers

Same functionality as std::initalizer_list.
