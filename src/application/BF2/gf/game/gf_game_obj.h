#pragma once
#include <stddef.h>

#include "gf/game/gf_game_mount.h"
#include "gf/object/gf_obj_manager.h"
#include "mm_mtl/fixed_list.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
}

namespace gf {

struct GF_OBJ_HANDLE;
struct GfSetupParam;
class GfObj;

enum {
  GAME_OBJ_LIST_CAPACITY = 1024,
};

class GfObjAcc;

class GfGameObj : public mm::mtl::PtrSingleton<GfGameObj> {
public:
  struct INOUT {
    GF_OBJ_HANDLE *unknown00; // Inferred role: object handle; original member name unknown.
    f32 unknown08;            // Inferred role: fade time elapsed; original member name unknown.
    f32 unknown0c;            // Inferred role: fade time; original member name unknown.
    u8 _10[0x16 - 0x10];
    bool unknown16; // Inferred role: effect fade enabled; original member name unknown.
    u8 _17[0x18 - 0x17];
  };

  static void build(const GfSetupParam &param);
  static void destroy();
  static void update(const fw::UpdateInfo &info);
  static void postUpdate(const fw::UpdateInfo &info);
  static const mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_OBJ_LIST_CAPACITY> *getList(u32 objectType);
  static void getList(mm::mtl::FixedVector<GF_OBJ_HANDLE *, GAME_OBJ_LIST_CAPACITY> &list, u32 objectType);
  mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_OBJ_LIST_CAPACITY> *getListType(u32 objectType, GF_OBJ_HANDLE *handle);
  static const mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_OBJ_LIST_CAPACITY> *getListEnemyBlade();
  static void getListEnemyBlade(mm::mtl::FixedVector<GF_OBJ_HANDLE *, GAME_OBJ_LIST_CAPACITY> &list);
  static bool isEmpty();
  static bool isExistEnemy();
  static void bdatReload();
  static bool isValidGameObj(GF_OBJ_HANDLE *handle, bool isCheckState, mm::mtl::FixStr<128> *reason);
  static bool isEnterGameObj(GF_OBJ_HANDLE *handle);
  static bool isDestroyGameObj(GF_OBJ_HANDLE *handle);
  static void setupEnterGameObj(GF_OBJ_HANDLE *handle, f32 fadeTime);
  static GfObj *getObj(GF_OBJ_HANDLE *handle);
  bool isEffectFadeEnd(const INOUT &inout, const GfObjAcc &acc) const;
  bool isBattle(const mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_OBJ_LIST_CAPACITY> &list) const;
  static void destroyGameObj(GF_OBJ_HANDLE *handle, f32 fadeTime);
  static void destroyGameObjWithAttribute(GF_OBJ_HANDLE *handle, f32 fadeTime, u32 attribute);
  static void changeStopLayerIgnoreEventObj(u32 layer, bool isIgnore);
  u32 getObjNumberByEnArrangeId(u32 arrange);
  static bool isInitialized();
  static bool isGameObjWaiting(GF_OBJ_HANDLE *handle);
  static void enterStayObject(GF_OBJ_HANDLE *handle);
  static void enterStayObject(GF_OBJ_HANDLE *handle, GFATTACH attach, OPTMNT type);

  u8 _08[0x10 - 0x08];
  mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_OBJ_LIST_CAPACITY> unknown10;    // Inferred role: object list; original member name unknown.
  mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_OBJ_LIST_CAPACITY> unknown4830;  // Inferred role: object list; original member name unknown.
  mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_OBJ_LIST_CAPACITY> unknown9050;  // Inferred role: object list; original member name unknown.
  mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_OBJ_LIST_CAPACITY> unknownd870;  // Inferred role: enemy blades; original member name unknown.
  mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_OBJ_LIST_CAPACITY> unknown12090; // Inferred role: object list; original member name unknown.
  mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_OBJ_LIST_CAPACITY> unknown168b0; // Inferred role: object list; original member name unknown.
  mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_OBJ_LIST_CAPACITY> unknown1b0d0; // Inferred role: object list; original member name unknown.
  mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_OBJ_LIST_CAPACITY> unknown1f8f0; // Inferred role: object list; original member name unknown.
  mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_OBJ_LIST_CAPACITY> unknown24110; // Inferred role: object list; original member name unknown.
  mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_OBJ_LIST_CAPACITY> unknown28930; // Inferred role: object list; original member name unknown.
  mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_OBJ_LIST_CAPACITY> unknown2d150; // Inferred role: object list; original member name unknown.
  mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_OBJ_LIST_CAPACITY> unknown31970; // Inferred role: object list; original member name unknown.
  mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_OBJ_LIST_CAPACITY> unknown36190; // Inferred role: object list; original member name unknown.
  mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_OBJ_LIST_CAPACITY> unknown3a9b0; // Inferred role: object list; original member name unknown.
  mm::mtl::FixedList<INOUT, GAME_OBJ_LIST_CAPACITY> unknown3f1d0;           // Inferred role: objects entering the game; original member name unknown.
  mm::mtl::FixedList<INOUT, GAME_OBJ_LIST_CAPACITY> unknown47a00;           // Inferred role: objects leaving the game; original member name unknown.
  u8 _50230[0x55c70 - 0x50230];
  bool unknown55c70; // Inferred role: initialized; original member name unknown.
};

static_assert(sizeof(mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_OBJ_LIST_CAPACITY>) == 0x4820, "");
static_assert(sizeof(mm::mtl::FixedList<GfGameObj::INOUT, GAME_OBJ_LIST_CAPACITY>) == 0x8830, "");
static_assert(offsetof(GfGameObj, unknown10) == 0x10, "");
static_assert(offsetof(GfGameObj, unknown4830) == 0x4830, "");
static_assert(offsetof(GfGameObj, unknown9050) == 0x9050, "");
static_assert(offsetof(GfGameObj, unknown12090) == 0x12090, "");
static_assert(offsetof(GfGameObj, unknown168b0) == 0x168b0, "");
static_assert(offsetof(GfGameObj, unknown1b0d0) == 0x1b0d0, "");
static_assert(offsetof(GfGameObj, unknown1f8f0) == 0x1f8f0, "");
static_assert(offsetof(GfGameObj, unknown24110) == 0x24110, "");
static_assert(offsetof(GfGameObj, unknown28930) == 0x28930, "");
static_assert(offsetof(GfGameObj, unknown2d150) == 0x2d150, "");
static_assert(offsetof(GfGameObj, unknown31970) == 0x31970, "");
static_assert(offsetof(GfGameObj, unknown36190) == 0x36190, "");
static_assert(offsetof(GfGameObj, unknown3a9b0) == 0x3a9b0, "");
static_assert(offsetof(GfGameObj, unknown47a00) == 0x47a00, "");
static_assert(offsetof(GfGameObj, unknownd870) == 0xd870, "");
static_assert(sizeof(GfGameObj::INOUT) == 0x18, "");
static_assert(offsetof(GfGameObj, unknown3f1d0) == 0x3f1d0, "");
static_assert(offsetof(GfGameObj, unknown55c70) == 0x55c70, "");

} // namespace gf
