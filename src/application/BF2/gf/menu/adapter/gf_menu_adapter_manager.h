#pragma once
#include <stddef.h>

#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

class GfMenuAdapter;

class GfMenuAdapterManager : public mm::mtl::PtrSingleton<GfMenuAdapterManager> {
public:
  static bool isAdapterFull();
  static bool isInitialized();
  static void destroy();
  static void beginCategory(u32 category);
  static void endCategory();
  static void beginAddAfter();
  static void endAddAfter();
  void addAdapter(GfMenuAdapter *adapter, bool isUpdateAfter);
  void setAfterUpdate(GfMenuAdapter *adapter);

  u8 _08[0x9c - 0x08];
  u32 unknown9c;  // Inferred role: current category; original member name unknown.
  bool unknowna0; // Inferred role: adding after update; original member name unknown.
};

static_assert(offsetof(GfMenuAdapterManager, unknown9c) == 0x9c, "");
static_assert(offsetof(GfMenuAdapterManager, unknowna0) == 0xa0, "");

} // namespace gf
