#pragma once
#include <stddef.h>

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace ml {
namespace device_detail {

extern mtl::ALLOC_HANDLE hMemFile;

void *allocateFile(size_t size);
void deallocateFile(void *pointer, size_t size);
void *allocateDebug(size_t size);
void deallocateDebug(void *pointer, size_t size);

} // namespace device_detail
} // namespace ml
