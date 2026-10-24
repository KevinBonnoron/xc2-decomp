#pragma once
#include <stddef.h>

#include "framework/manager_object.h"
#include "mm_mtl/singleton.h"

namespace navi {
class NvmshAcObj;
class NvmshManager;
} // namespace navi

namespace fw {

class NaviManager : public ManagerObject, public mm::mtl::PtrSingleton<NaviManager> {
public:
  NaviManager();
  bool initialize() override;
  bool finalize() override;
  bool createNaviMesh(void *data, const char *name);
  void releaseNaviMesh();
  navi::NvmshAcObj *createObject();
  void releaseObject(navi::NvmshAcObj *object);
  void update();
  void tail();
  void openDebugWindow();

  void *unknown18;               // Inferred role: navi mesh data; original member name unknown.
  navi::NvmshManager *unknown20; // Inferred role: manager; original member name unknown.
};

static_assert(offsetof(NaviManager, unknown18) == 0x18, "");
static_assert(offsetof(NaviManager, unknown20) == 0x20, "");

} // namespace fw
