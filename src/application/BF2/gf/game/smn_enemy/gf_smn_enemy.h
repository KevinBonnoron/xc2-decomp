#pragma once
#include <stddef.h>
#include <utility>

#include "gf/object/gf_obj_manager.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/singleton.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace gf {

struct GF_OBJ_HANDLE;

class GfRelSmnEnemy : public IGfObjListener {
public:
  // Layout evidence: GfRelSmnEnemy::create (0x7100389990) fills it from bdat values ("ActType", "ChestHeight") before
  // Vector<PopInfo>::push_back, whose copy moves the first 12 bytes raw, the Vec3 member by member and the byte at 0x20;
  // getPopPos (0x710038b38c) reads the offset at 0x10.
  struct PopInfo {
    u8 unknown00;       // Inferred role: pop point type (0 to 2); original member name unknown.
    u16 unknown02;      // Inferred role: enemy id; original member name unknown.
    u32 unknown04;      // Inferred role: action type ("ActType"); original member name unknown.
    f32 unknown08;      // Inferred role: chest height in meters ("ChestHeight"); original member name unknown.
    mm::Vec3 unknown10; // Inferred role: pop offset; original member name unknown.
    bool unknown20;     // Inferred role: popped; original member name unknown.
  };

  virtual ~GfRelSmnEnemy();
  void removeEnemy(GF_OBJ_HANDLE *handle);
  void listenerGfObj(OBJEVT event, GF_OBJ_HANDLE *handle, u32 objectType) override;

  bool isOwnerValid() const;
  u32 getEnemyNum() const;
  GF_OBJ_HANDLE *getEnemy(u32 index) const;
  void disposeWaitEnemies();
  void disposeEnemies(bool isFade);

  u8 _08[0x10 - 0x08];
  GF_OBJ_HANDLE *unknown10; // Inferred role: owner object; original member name unknown.
  s32 unknown18;            // Inferred role: bdat id of the summon enemy table row; original member name unknown.
  u8 _1c[0x78 - 0x1c];
  mm::mtl::Vector<std::pair<PopInfo *, GF_OBJ_HANDLE *>> unknown78; // Inferred role: wait enemies; original member name unknown.
  mm::mtl::Vector<GF_OBJ_HANDLE *> unknowna0;                       // Inferred role: popped enemies; original member name unknown.
};

static_assert(offsetof(GfRelSmnEnemy::PopInfo, unknown02) == 0x02, "");
static_assert(offsetof(GfRelSmnEnemy::PopInfo, unknown08) == 0x08, "");
static_assert(offsetof(GfRelSmnEnemy::PopInfo, unknown10) == 0x10, "");
static_assert(offsetof(GfRelSmnEnemy::PopInfo, unknown20) == 0x20, "");
static_assert(sizeof(GfRelSmnEnemy::PopInfo) == 0x30, "");
static_assert(offsetof(GfRelSmnEnemy, unknown18) == 0x18, "");
static_assert(offsetof(GfRelSmnEnemy, unknown78) == 0x78, "");
static_assert(offsetof(GfRelSmnEnemy, unknowna0) == 0xa0, "");

class GfSmnEnemyManager : public mm::mtl::PtrSingleton<GfSmnEnemyManager> {
public:
  static void create();
  static void dispose();
  static void update(f32 deltaTime);
};

} // namespace gf
