#pragma once
#include <stddef.h>

#include "mm_mtl/singleton.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace fw {

class UpdatableObjectManager;

class UpdatableObjectFactory : public mm::mtl::PtrSingleton<UpdatableObjectFactory> {
public:
  UpdatableObjectFactory(mm::mtl::IAllocator *allocator, UpdatableObjectManager *manager) : allocator(allocator), manager(manager) {}

  mm::mtl::IAllocator *allocator;
  UpdatableObjectManager *manager;
};

static_assert(offsetof(UpdatableObjectFactory, allocator) == 0x08, "");
static_assert(offsetof(UpdatableObjectFactory, manager) == 0x10, "");
static_assert(sizeof(UpdatableObjectFactory) == 0x18, "");

} // namespace fw
