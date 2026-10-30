#pragma once
#include <stddef.h>

// Provenance: the names and prototypes are the public SDK API, as declared in the open-ead nnheaders project
// (https://github.com/open-ead/nnheaders, include/nv.h); each function is an imported symbol of the game
// (_ZN2nv... in work/syms_base.txt), called by grlib::CGLibDeviceObj::init (0x71007b31d0).

namespace nv {

void SetGraphicsAllocator(void *(*allocator)(size_t size, size_t alignment, void *userPtr), void (*deallocator)(void *address, void *userPtr),
                          void *(*reallocator)(void *address, size_t newSize, void *userPtr), void *userPtr);
void SetGraphicsDevtoolsAllocator(void *(*allocator)(size_t size, size_t alignment, void *userPtr), void (*deallocator)(void *address, void *userPtr),
                                  void *(*reallocator)(void *address, size_t newSize, void *userPtr), void *userPtr);
void InitializeGraphics(void *address, size_t size);

} // namespace nv
