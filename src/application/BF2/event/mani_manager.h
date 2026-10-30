#pragma once
#include <stddef.h>

#include "event/i_manager.h"
#include "ml/work_event.h"
#include "mm_math/mm_mat44.h"
#include "mm_mtl/bitflag.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/noncopyable.h"
#include "types.h"

namespace mm {
struct Vec3;
}

namespace ml {
class EventView;
}

namespace event {

class IManiCallback;

enum MANI_TYPE {
  MANI_TYPE_POS = 1,
  MANI_TYPE_ROT = 2,
  MANI_TYPE_TAR = 3,
};

class ManiManager : public IManager, public mm::mtl::NoncopyableBase, public ml::IWorkEvent {
public:
  static constexpr u32 ITEM_COUNT = 512;

  enum {
    FLAG_ENABLE = 0,
    FLAG_ATTACHED = 1,
    FLAG_ACTIVE = 2,
    FLAG_ADJEST_POS = 3,
  };

  enum {
    DEBUG_FLAG_ENABLE = 0,
  };

  struct Item {
    IManiCallback *unknown00; // Inferred role: callback; original member name unknown.
    mm::Mat44 unknown10;      // Inferred role: callback origin matrix; original member name unknown.
    mm::Mat44 unknown50;      // Inferred role: inverse of the origin matrix; original member name unknown.
    mm::Mat44 unknown90;      // Inferred role: local matrix; original member name unknown.
    mm::Mat44 unknownd0;      // Inferred role: local matrix times the origin matrix; original member name unknown.
  };

  ManiManager();
  virtual ~ManiManager() {}
  void create();
  void clear();
  void clearManipulate();
  void update();
  void updateManipulate();
  void render();
  static void adjestPosY(mm::Vec3 &position);
  void addManipulate(IManiCallback *callback, MANI_TYPE type);
  static bool exist(mm::mtl::FixedVector<Item, ITEM_COUNT> &items, IManiCallback *callback);
  void removeManipulate(IManiCallback *callback);
  void changeManipulate(MANI_TYPE type);
  void setAdjestPosEnable(bool isEnable);
  bool isAdjestPosEnable() const;
  void setEnable(bool isEnable);
  void setDebugEnable(bool isEnable);
  virtual bool OnMouseButtonDown(ml::EventView *view);
  virtual bool OnKeyDown(ml::EventView *view);
  virtual void OnEventProc(MSG_TYPE type);

private:
  mm::mtl::unknown027<32> unknown18;                // Inferred role: flags; original member name unknown.
  mm::mtl::unknown027<32> unknown1c;                // Inferred role: debug flags; original member name unknown.
  mm::mtl::FixedVector<Item, ITEM_COUNT> unknown20; // Inferred role: items; original member name unknown.
  MANI_TYPE unknown22030;                           // Inferred role: type; original member name unknown.
  u8 _22034[0x22040 - 0x22034];
  mm::Mat44 unknown22040; // Inferred role: matrix; original member name unknown.
  mm::Mat44 unknown22080; // Inferred role: matrix; original member name unknown.
  mm::Mat44 unknown220c0; // Inferred role: matrix; original member name unknown.
  mm::Mat44 unknown22100; // Inferred role: matrix; original member name unknown.
  mm::Mat44 unknown22140; // Inferred role: matrix; original member name unknown.

  friend struct ManiManagerLayout;
};

struct ManiManagerLayout {
  static_assert(offsetof(ManiManager, unknown22040) == 0x22040, "");
  static_assert(offsetof(ManiManager, unknown22080) == 0x22080, "");
  static_assert(offsetof(ManiManager, unknown220c0) == 0x220c0, "");
  static_assert(offsetof(ManiManager, unknown22100) == 0x22100, "");
  static_assert(offsetof(ManiManager, unknown22140) == 0x22140, "");
  static_assert(sizeof(ManiManager) == 0x22180, "");
  static_assert(offsetof(ManiManager::Item, unknown10) == 0x10, "");
  static_assert(offsetof(ManiManager::Item, unknown50) == 0x50, "");
  static_assert(offsetof(ManiManager::Item, unknown90) == 0x90, "");
  static_assert(offsetof(ManiManager::Item, unknownd0) == 0xd0, "");
  static_assert(sizeof(ManiManager::Item) == 0x110, "");
};

} // namespace event
