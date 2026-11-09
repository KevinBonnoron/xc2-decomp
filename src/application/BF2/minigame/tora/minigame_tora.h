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
  _sTask *unknown00;               // Inferred role: next task of the list, or next free slot; original member name unknown.
  _sTask *unknown08;               // Inferred role: previous task of the list; original member name unknown.
  void (*unknown10)(_sTask *task); // Inferred role: move function called by mytask::executeMove; original member name unknown.
  void (*unknown18)(_sTask *task); // Inferred role: draw function called by mytask::executeDraw; original member name unknown.
  u8 _20[0x2c - 0x20];
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
static_assert(offsetof(_sTask, unknown00) == 0x00, "");
static_assert(offsetof(_sTask, unknown08) == 0x08, "");
static_assert(offsetof(_sTask, unknown10) == 0x10, "");
static_assert(offsetof(_sTask, unknown18) == 0x18, "");

class mytask {
public:
  mytask(int taskSize, int taskCount);
  ~mytask();
  void reset();
  void *entry();
  void *entryNext(void *task);
  void *entryTop();
  void *entryPrev(void *task);
  void *entryEnd();
  void remove(void *task);
  void executeMove();
  void executeDraw();
  void *enum_next(void *task);

  void *unknown00;   // Inferred role: memory of the task pool; original member name unknown.
  int unknown08;     // Inferred role: size of a task; original member name unknown.
  int unknown0c;     // Inferred role: number of tasks; original member name unknown.
  _sTask *unknown10; // Inferred role: first free task; original member name unknown.
  _sTask *unknown18; // Inferred role: first task of the list; original member name unknown.
  _sTask *unknown20; // Inferred role: last task of the list; original member name unknown.
  _sTask *unknown28; // Inferred role: task executeMove and executeDraw run next, kept up to date when remove runs from a callback; original member name unknown.
};

static_assert(offsetof(mytask, unknown08) == 0x08, "");
static_assert(offsetof(mytask, unknown10) == 0x10, "");
static_assert(offsetof(mytask, unknown28) == 0x28, "");
static_assert(sizeof(mytask) == 0x30, "");

class minigame : public mm::mtl::PtrSingleton<minigame> {
public:
  void get_pc_pos(int &x, int &y);
  void get_pc_dxdy(int x, int y, int &dx, int &dy);
  void get_coli_xy(int &x, int &y, _sTask *task);
  void get_pc_atk_xy(int &x, int &y, _sTask *task);
  void clip_screen(int &x, int &y, int &w, int &h, int &ox, int &oy);

  u8 _08[0x3528 - 0x08];
  _sTask *unknown3528; // Task whose 0x2c/0x30 fields get_pc_pos and get_pc_dxdy read; original member name unknown.
  u8 _3530[0x3560 - 0x3530];
  int unknown3560; // Divided by 256 and added to the y of unknown3528 in get_pc_pos and get_pc_dxdy; original member name unknown.
};

static_assert(offsetof(minigame, unknown3528) == 0x3528, "");
static_assert(offsetof(minigame, unknown3560) == 0x3560, "");

} // namespace tora
} // namespace minigame
