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

  void *naviMeshData;
  navi::NvmshManager *manager;
};

static_assert(offsetof(NaviManager, naviMeshData) == 0x18, "");
static_assert(offsetof(NaviManager, manager) == 0x20, "");

} // namespace fw
