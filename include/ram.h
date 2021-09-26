#ifndef RAM_H
#define RAM_H

#include "defs.h"

struct RAM {
    /// Defines allocation for memory
    /// @param alloc    heap allocation
    void Init(const int alloc);

    /// Deallocates memory
    void Destroy();

    byte * memory;
};

#endif
