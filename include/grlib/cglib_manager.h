#pragma once
#include <stddef.h>

#include "grlib/cglib_device_obj.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace grlib {

namespace context {
class CGLibSystemContext;
} // namespace context

class CGLibManager : public mm::mtl::PtrSingleton<CGLibManager>, public CGLibDeviceObj {
public:
  CGLibManager();
  ~CGLibManager();
  void deviceInit();
  bool deviceRelease();
  void begin();
  void end();
  void swap();
  void tail();
  s64 getGpuTimeStamp() const;
  void isRelease();
  static bool isReleaseOk();

  static int s_nDblNowIdx;
  static int s_nTriNowIdx;
  static int s_nStkNowIdx;
  static bool s_nReleaseOk;

  context::CGLibSystemContext *unknown5028; // Inferred role: system context; original member name unknown.
};

static_assert(offsetof(CGLibManager, unknown00) == 0x8, "");
static_assert(offsetof(CGLibManager, unknown5028) == 0x5028, "");
static_assert(sizeof(CGLibManager) == 0x5030, "");

} // namespace grlib
