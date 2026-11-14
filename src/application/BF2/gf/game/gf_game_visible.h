#pragma once
#include <stddef.h>

#include "mm_mtl/fixed_queue.h"
#include "mm_mtl/map.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace fw {
struct UpdateInfo;
}

namespace gf {

struct GF_OBJ_HANDLE;
struct GfSetupParam;

class GfGameVisible : public mm::mtl::PtrSingleton<GfGameVisible> {
public:
  struct Info {
    Info() : unknown00(false), unknown01(false), unknown02(false), unknown04(0) {}

    bool unknown00; // Inferred role: visible; original member name unknown.
    bool unknown01; // Role and original member name unknown.
    bool unknown02; // Inferred role: model component; original member name unknown.
    u8 _03;
    s32 unknown04; // Inferred role: frames before the next check; original member name unknown.
  };

  static void build(const GfSetupParam &param);
  void setup();
  static void destroy();
  void update(const fw::UpdateInfo &info);
  void updateImpl(const fw::UpdateInfo &info);
  static void cleanup();
  static bool isVisible(GF_OBJ_HANDLE *handle);
  void searchObj(u32 type, const mm::Vec3 &position);
  bool checkVisible(GF_OBJ_HANDLE *handle, const mm::Vec3 &position, bool isModel);

  mm::mtl::Map<GF_OBJ_HANDLE *, Info *> unknown08; // Inferred role: visibility of the objects; original member name unknown.
  mm::mtl::FixedQueue<Info *, 0x400> unknown20;    // Inferred role: unused infos; original member name unknown.
  Info unknown2030[0x400];                         // Inferred role: storage of the infos; original member name unknown.
};

static_assert(offsetof(GfGameVisible, unknown08) == 0x08, "");
static_assert(offsetof(GfGameVisible, unknown20) == 0x20, "");
static_assert(offsetof(GfGameVisible, unknown2030) == 0x2030, "");
static_assert(sizeof(GfGameVisible) == 0x4030, "");

} // namespace gf
