#pragma once
#include <stddef.h>

#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace gf {

struct GfSetupParam;

class GfFobjManager : public mm::mtl::PtrSingleton<GfFobjManager> {
public:
  static void build(const GfSetupParam &param);
  static void destroy();
  static void update(const fw::UpdateInfo &info);
  static bool isInitialized();
  static bool isExistObj();
  static void destroyObj();

  u8 _08[0x4830 - 0x08];
  s32 unknown4830; // Inferred role: number of objects; original member name unknown.
  u8 _4834[0x9050 - 0x4834];
  s32 unknown9050; // Inferred role: number of objects; original member name unknown.
  u8 _9054[0x9058 - 0x9054];
  bool unknown9058; // Inferred role: initialized; original member name unknown.
};

static_assert(offsetof(GfFobjManager, unknown4830) == 0x4830, "");
static_assert(offsetof(GfFobjManager, unknown9050) == 0x9050, "");
static_assert(offsetof(GfFobjManager, unknown9058) == 0x9058, "");

} // namespace gf
