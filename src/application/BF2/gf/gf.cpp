#include "gf/gf_allocator.h"

namespace gf {

GfAllocator *getAllocator(ALLOCATOR allocator) { return GfAllocatorManager::getAllocator(allocator); }

} // namespace gf
