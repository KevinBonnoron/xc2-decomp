#pragma once
#include "framework/manager_object.h"
#include "mm_mtl/singleton.h"

namespace wnd {
struct ResWind;
} // namespace wnd

namespace fw {

class WindManager : public ManagerObject, public mm::mtl::PtrSingleton<WindManager> {
public:
  void setGlobalWind(int wind);
  void buildWorld(const wnd::ResWind *resWind);
  void destroyWorld();
};

} // namespace fw
