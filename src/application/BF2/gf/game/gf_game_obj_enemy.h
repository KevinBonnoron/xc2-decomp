#pragma once
#include <stddef.h>

#include "mm_mtl/fixed_list.h"
#include "mm_mtl/fixed_queue.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace gf {

struct GF_OBJ_HANDLE;

class GfGameObjEnemy : public mm::mtl::PtrSingleton<GfGameObjEnemy> {
public:
  // Name from the game symbol mm::mtl::FixedList<gf::GfGameObjEnemy::GINFO, 64>::erase.
  struct GINFO {
    int unknown00;                                      // Inferred role: genus; original member name unknown.
    mm::mtl::FixedList<GF_OBJ_HANDLE *, 64> *unknown08; // Inferred role: objects of the genus; original member name unknown.
  };

  // Name from the game symbol gf::GfGameObjEnemy::calcGenusLink(gf::GfGameObjEnemy::Pair&).
  struct Pair {
    GF_OBJ_HANDLE *unknown00; // Inferred role: first object; original member name unknown.
    GF_OBJ_HANDLE *unknown08; // Inferred role: second object; original member name unknown.
    bool unknown10;           // Inferred role: linked; original member name unknown.
    s16 unknown12;            // Inferred role: bone index of the first object; original member name unknown.
    s16 unknown14;            // Inferred role: bone index of the second object; original member name unknown.
  };

  GfGameObjEnemy();
  ~GfGameObjEnemy();
  void update(const fw::UpdateInfo &info);
  void enterEnemyObj(GF_OBJ_HANDLE *handle);
  void leaveEnemyObj(GF_OBJ_HANDLE *handle);
  static bool isGenusLink(GF_OBJ_HANDLE *handle);
  static bool getGenusLink(mm::mtl::FixedList<GF_OBJ_HANDLE *, 1024> &list, GF_OBJ_HANDLE *handle);
  void calcGenusLink(Pair &pair);
  bool empty() const;

  mm::mtl::FixedList<GINFO, 64> unknown08;              // Inferred role: object lists by genus; original member name unknown.
  mm::mtl::FixedList<GF_OBJ_HANDLE *, 256> unknown670;  // Inferred role: object list; original member name unknown.
  mm::mtl::FixedList<GF_OBJ_HANDLE *, 256> unknown1890; // Inferred role: object list; original member name unknown.
  mm::mtl::FixedQueue<Pair, 1024> unknown2ab0;          // Inferred role: pairs to check; original member name unknown.
};

static_assert(offsetof(GfGameObjEnemy, unknown08) == 0x08, "");
static_assert(offsetof(GfGameObjEnemy, unknown670) == 0x670, "");
static_assert(offsetof(GfGameObjEnemy, unknown1890) == 0x1890, "");
static_assert(offsetof(GfGameObjEnemy, unknown2ab0) == 0x2ab0, "");
static_assert(sizeof(GfGameObjEnemy) == 0x8ac0, "");

} // namespace gf
