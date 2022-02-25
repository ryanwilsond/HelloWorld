#include "ram.h"

void RAM::Init(const long long unsigned int alloc) {
    this->memory = new byte[alloc];
}

void RAM::Destroy() {
    delete[] this->memory;
}
