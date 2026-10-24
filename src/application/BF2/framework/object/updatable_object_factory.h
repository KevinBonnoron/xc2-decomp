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
  UpdatableObjectFactory(mm::mtl::IAllocator *allocator, UpdatableObjectManager *manager) : unknown08(allocator), unknown10(manager) {}

  mm::mtl::IAllocator *unknown08;    // Inferred role: allocator; original member name unknown.
  UpdatableObjectManager *unknown10; // Inferred role: manager; original member name unknown.
};

static_assert(offsetof(UpdatableObjectFactory, unknown08) == 0x08, "");
static_assert(offsetof(UpdatableObjectFactory, unknown10) == 0x10, "");
static_assert(sizeof(UpdatableObjectFactory) == 0x18, "");

} // namespace fw
