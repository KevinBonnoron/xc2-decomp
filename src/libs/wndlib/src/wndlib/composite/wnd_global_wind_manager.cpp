// Original file name from the game string .../wndlib/src/wndlib/composite/wnd_global_wind_manager.cpp.
#include "wnd/wnd_global_wind_manager.h" // IWYU pragma: keep

namespace wnd {

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

void GlobalWindManager::cleanup() {}

} // namespace wnd
