#include <stddef.h>

// Definitions for shim delete operators needed to compile against C++17.

void operator delete(void* ptr, size_t size) noexcept;

void operator delete[](void* ptr, size_t size) noexcept;
