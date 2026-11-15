#pragma once
#include <stddef.h>
#include <utility>

#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_manager.h"
#include "gmk/gmk_cond.h"
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

  struct CreateInfo {
    CreateInfo() : unknown00(unknown020), unknown08(0), unknown10(mm::Vec3::zero), unknown20(false) {}

    GF_OBJ_HANDLE *unknown00; // Inferred role: owner object; original member name unknown.
    s32 unknown08;            // Inferred role: bdat id of the summon enemy table row; original member name unknown.
    mm::Vec3 unknown10;       // Inferred role: position; original member name unknown.
    bool unknown20;           // Inferred role: flag; original member name unknown.
  };

  GfRelSmnEnemy(const CreateInfo *info);
  virtual ~GfRelSmnEnemy();
  void create(const CreateInfo &info);
  void dispose();
  void update(f32 deltaTime);
  void updatePopEnemy();
  void debugDraw() const;
  void updateDepopEnemy();
  void validatePopPos();
  void removeEnemy(GF_OBJ_HANDLE *handle);
  void listenerGfObj(OBJEVT event, GF_OBJ_HANDLE *handle, u32 objectType) override;

  bool isOwnerValid() const;
  u32 getEnemyNum() const;
  GF_OBJ_HANDLE *getEnemy(u32 index) const;
  void disposeWaitEnemies();
  void disposeEnemies(bool isFade);

  u8 _08[0x10 - 0x08];
  CreateInfo unknown10;                                             // Inferred role: create info; original member name unknown.
  f32 unknown40;                                                    // Inferred role: minimum pop radius; original member name unknown.
  f32 unknown44;                                                    // Inferred role: maximum pop radius; original member name unknown.
  gmk::DistHvCond unknown48;                                        // Inferred role: depop range of the popped enemies; original member name unknown.
  mm::mtl::Vector<PopInfo> unknown50;                               // Inferred role: pop points; original member name unknown.
  mm::mtl::Vector<std::pair<PopInfo *, GF_OBJ_HANDLE *>> unknown78; // Inferred role: wait enemies; original member name unknown.
  mm::mtl::Vector<GF_OBJ_HANDLE *> unknowna0;                       // Inferred role: popped enemies; original member name unknown.
};

static_assert(offsetof(GfRelSmnEnemy::PopInfo, unknown02) == 0x02, "");
static_assert(offsetof(GfRelSmnEnemy::PopInfo, unknown08) == 0x08, "");
static_assert(offsetof(GfRelSmnEnemy::PopInfo, unknown10) == 0x10, "");
static_assert(offsetof(GfRelSmnEnemy::PopInfo, unknown20) == 0x20, "");
static_assert(sizeof(GfRelSmnEnemy::PopInfo) == 0x30, "");
static_assert(offsetof(GfRelSmnEnemy::CreateInfo, unknown10) == 0x10, "");
static_assert(sizeof(GfRelSmnEnemy::CreateInfo) == 0x30, "");
static_assert(offsetof(GfRelSmnEnemy, unknown10) == 0x10, "");
static_assert(offsetof(GfRelSmnEnemy, unknown40) == 0x40, "");
static_assert(offsetof(GfRelSmnEnemy, unknown48) == 0x48, "");
static_assert(offsetof(GfRelSmnEnemy, unknown50) == 0x50, "");
static_assert(offsetof(GfRelSmnEnemy, unknown78) == 0x78, "");
static_assert(offsetof(GfRelSmnEnemy, unknowna0) == 0xa0, "");

class GfSmnEnemyManager : public mm::mtl::PtrSingleton<GfSmnEnemyManager> {
public:
  // Layout evidence: execRelSummon (0x710038c4c4) copies these 12 bytes to the owner and the table row of a GfRelSmnEnemy::CreateInfo.
  struct RelSmnInfo {
    GF_OBJ_HANDLE *unknown00; // Inferred role: owner object; original member name unknown.
    s32 unknown08;            // Inferred role: bdat id of the summon enemy table row; original member name unknown.
  };

  // Layout evidence: execAbsSummon (0x710038c188) reads the owner at 0x00, the radius at 0x08 and the genus at 0x0c.
  struct AbsSmnInfo {
    GF_OBJ_HANDLE *unknown00; // Inferred role: owner object; original member name unknown.
    f32 unknown08;            // Inferred role: radius; original member name unknown.
    u8 unknown0c;             // Inferred role: enemy genus (SDataEnemy::unknown99), 0 for any; original member name unknown.
  };

  GfSmnEnemyManager();
  ~GfSmnEnemyManager();
  static void create();
  static void dispose();
  static void update(f32 deltaTime);
  static void clearSmnEnemies();
  static void debugDraw();
  static bool execAbsSummon(const AbsSmnInfo &info);
  static bool execRelSummon(const RelSmnInfo &info);

  mm::mtl::Vector<GfRelSmnEnemy *> unknown08; // Inferred role: relative summon enemies; original member name unknown.
};

static_assert(offsetof(GfSmnEnemyManager, unknown08) == 0x08, "");
static_assert(sizeof(GfSmnEnemyManager) == 0x30, "");
static_assert(offsetof(GfSmnEnemyManager::AbsSmnInfo, unknown08) == 0x08, "");
static_assert(offsetof(GfSmnEnemyManager::AbsSmnInfo, unknown0c) == 0x0c, "");
static_assert(sizeof(GfSmnEnemyManager::AbsSmnInfo) == 0x10, "");

} // namespace gf
