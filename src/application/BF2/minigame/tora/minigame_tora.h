#pragma once
#include <stddef.h>

#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
class UpdatableObject;
}

namespace ui {
class UIObjectAcc;
}

namespace minigame {
namespace tora {
namespace factory {

fw::UpdatableObject *create(ui::UIObjectAcc *parent);

} // namespace factory

struct _sTask {
  u8 _00[0x2c - 0x00];
  int unknown2c; // Read by get_pc_pos and, shifted right by 8, by get_coli_xy and get_pc_atk_xy as the x coordinate; original member name unknown.
  int unknown30; // Read by get_pc_pos and, shifted right by 8, by get_coli_xy and get_pc_atk_xy as the y coordinate; original member name unknown.
  u8 _34[0x36 - 0x34];
  s16 unknown36; // Signed 16-bit offset added to the shifted x in get_coli_xy; original member name unknown.
  s16 unknown38; // Signed 16-bit offset added to the shifted y in get_coli_xy; original member name unknown.
  u8 _3a[0x58 - 0x3a];
  s16 unknown58; // Signed 16-bit offset added to the shifted x in get_pc_atk_xy; original member name unknown.
  s16 unknown5a; // Signed 16-bit offset added to the shifted y in get_pc_atk_xy; original member name unknown.
  u8 unknown5c;  // Unsigned 8-bit value subtracted from x in get_pc_atk_xy; original member name unknown.
  u8 unknown5d;  // Unsigned 8-bit value subtracted from y in get_pc_atk_xy; original member name unknown.
};

static_assert(offsetof(_sTask, unknown2c) == 0x2c, "");
static_assert(offsetof(_sTask, unknown30) == 0x30, "");
static_assert(offsetof(_sTask, unknown36) == 0x36, "");
static_assert(offsetof(_sTask, unknown38) == 0x38, "");
static_assert(offsetof(_sTask, unknown58) == 0x58, "");
static_assert(offsetof(_sTask, unknown5a) == 0x5a, "");
static_assert(offsetof(_sTask, unknown5c) == 0x5c, "");
static_assert(offsetof(_sTask, unknown5d) == 0x5d, "");

class minigame : public mm::mtl::PtrSingleton<minigame> {
public:
  void get_pc_pos(int &x, int &y);
  void get_pc_dxdy(int x, int y, int &dx, int &dy);
  void get_coli_xy(int &x, int &y, _sTask *task);
  void get_pc_atk_xy(int &x, int &y, _sTask *task);

  u8 _08[0x3528 - 0x08];
  _sTask *unknown3528; // Task whose 0x2c/0x30 fields get_pc_pos and get_pc_dxdy read; original member name unknown.
  u8 _3530[0x3560 - 0x3530];
  int unknown3560; // Divided by 256 and added to the y of unknown3528 in get_pc_pos and get_pc_dxdy; original member name unknown.
};

static_assert(offsetof(minigame, unknown3528) == 0x3528, "");
static_assert(offsetof(minigame, unknown3560) == 0x3560, "");

} // namespace tora
} // namespace minigame
