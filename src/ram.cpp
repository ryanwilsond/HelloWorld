#include "ram.h"

void RAM::Init(const int alloc) {
    this->memory = new byte[alloc];
}

void RAM::Destroy() {
    delete[] this->memory;
}
