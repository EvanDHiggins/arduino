#include "CppShim.h"

// C++14/17 sized deallocation shim
void operator delete(void* ptr, size_t size) noexcept {
    // Just call the standard delete, ignoring the size
    operator delete(ptr);
}

// You might also need the array version
void operator delete[](void* ptr, size_t size) noexcept {
    operator delete[](ptr);
}
