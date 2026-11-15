// Original file name from the game string .../wndlib/src/wndlib/composite/wnd_global_wind_manager.cpp.
#include "wnd/wnd_global_wind_manager.h" // IWYU pragma: keep

#include "mm/mm_std_base.h"

namespace wnd {
class WindNode;

GlobalWindManager::GlobalWindManager() : unknown140(-1), unknown144(-1) {}

void GlobalWindManager::setup(const Array<const ResConpoundWind *> &resWind, mm::mtl::IAllocator *allocator) {
  unknown30 = resWind.size();
  unknown28 = resWind.m_pElements;
  unknown00.setAllocator(allocator);
  u32 count = resWind.size();
  unknown00.resize(count);
  for (u32 i = 0; i < count; i++) {
#line 42
    MM_ASSERT(resWind[i]);
    ConpoundWind &wind = unknown00[i];
    wind.unknownd0 = resWind[i];
  }
}

bool GlobalWindManager::setCurrentWind(int index) {
  if (static_cast<s32>(unknown00.size()) < index) {
    return false;
  }
  if (unknown140 == index) {
    return true;
  }
  if (unknown144 == -1) {
    ConpoundWind *wind = index == -1 ? nullptr : &unknown00[index];
    unknown40.changeNode(wind, 1.0f);
    // Address 0x7100988c20: no-op store that the game emits when the current node is the debug node.
    if (unknown40.unknowne8 == unknown40.unknownf0) {
      unknown40.unknownf0 = unknown40.unknowne8;
    }
    unknown40.unknowne8 = wind;
  }
  unknown140 = index;
  return true;
}

void GlobalWindManager::setDebugWind(bool enable, u32 mask) {
  WindNode *node = nullptr;
  if (enable) {
    unknown144 = mask;
    node = &unknown00[static_cast<s32>(mask)];
  } else {
    int index = unknown140;
    unknown144 = -1;
    if (index != -1) {
      node = &unknown00[index];
    }
  }
  unknown40.setNode(node);
  unknown40.unknowne8 = node;
  // Address 0x7100988d30: redundant store after setNode, which already clears unknownd8; the game emits it.
  unknown40.unknownd8 = nullptr;
}

void GlobalWindManager::cleanup() {}

} // namespace wnd
