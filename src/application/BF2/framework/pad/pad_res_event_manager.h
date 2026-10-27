#pragma once
#include <stddef.h>

#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/singleton.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace fw {
class PadResEvent;

class PadResEventManager : public mm::mtl::PtrSingleton<PadResEventManager> {
public:
  PadResEventManager();
  ~PadResEventManager() override;
  void setup(u32 count, mm::mtl::IAllocator *allocator);
  void cleanup();
  static void setResource(u32 index, const PadResEvent *event);

  mm::mtl::Vector<mm::mtl::IntrusivePtr<const PadResEvent>> unknown08; // Inferred role: events; original member name unknown.
};

static_assert(offsetof(PadResEventManager, unknown08) == 0x08, "");
static_assert(sizeof(PadResEventManager) == 0x30, "");

} // namespace fw
