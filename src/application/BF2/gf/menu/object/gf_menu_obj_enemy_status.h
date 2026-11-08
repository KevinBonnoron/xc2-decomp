#pragma once
#include <stddef.h>
#include <string.h>

#include "gf/menu/gf_menu_object.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace gf {

struct GF_OBJ_HANDLE;
class unknown135;

class GfMenuObjEnemyStatus : public GfMenuObject {
public:
  struct OpenParam {
    GF_OBJ_HANDLE *unknown00; // Inferred role: enemy handle; original member name unknown.
  };

  // Inferred role: enemy adapters cleared as a whole by the constructor; original name unknown.
  struct unknown005 {
    unknown005() { memset(this, 0, sizeof(*this)); }

    mm::mtl::FixedVector<unknown135 *, 25> unknown00; // Inferred role: adapters; original member name unknown.
  };

  GfMenuObjEnemyStatus(u32 handle);
  ~GfMenuObjEnemyStatus() override;
  static void open(const OpenParam &param);
  static void close();
  static void disp(bool isDisp);
  void initialize() override;
  void finalize() override;

  u8 _24[0x28 - 0x24];
  s64 unknown28;        // Inferred role: unused, -1 at start; original member name unknown.
  unknown005 unknown30; // Inferred role: enemy adapters; original member name unknown.
  int unknown100;       // Inferred role: unused, -1 at start; original member name unknown.
  u8 _104[0x108 - 0x104];
};

static_assert(sizeof(GfMenuObjEnemyStatus::unknown005) == 0xd0, "");
static_assert(offsetof(GfMenuObjEnemyStatus, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjEnemyStatus, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjEnemyStatus, unknown100) == 0x100, "");
static_assert(sizeof(GfMenuObjEnemyStatus) == 0x108, "");

} // namespace gf
