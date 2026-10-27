#pragma once
#include <stddef.h>

#include "fw/fw_update_info.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

struct GfReqParam;
struct GfSetupParam;

class GfReqManager : public mm::mtl::PtrSingleton<GfReqManager> {
public:
  static void build(const GfSetupParam &param);
  static void destroy();
  void update(const fw::UpdateInfo &info);
  static bool isValid(u32 request);
  static bool isInitialized();
  int getHandle();
  static void terminateCommand();
  static fw::UpdateInfo *getUpdateInfo();
  static bool isExistCommand(void (*command)(const GfReqParam *param));

  fw::UpdateInfo unknown08; // Inferred role: update info; original member name unknown.
  u8 _14[0x1840 - 0x14];
  bool unknown1840; // Inferred role: command terminated; original member name unknown.
  int unknown1844;  // Inferred role: last handle; original member name unknown.
  bool unknown1848; // Inferred role: initialized; original member name unknown.
};

static_assert(offsetof(GfReqManager, unknown08) == 0x08, "");
static_assert(offsetof(GfReqManager, unknown1840) == 0x1840, "");
static_assert(offsetof(GfReqManager, unknown1844) == 0x1844, "");
static_assert(offsetof(GfReqManager, unknown1848) == 0x1848, "");

} // namespace gf
