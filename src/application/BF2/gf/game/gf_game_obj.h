#pragma once
#include "mm_mtl/fixed_list.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
}

namespace gf {

struct GF_OBJ_HANDLE;
struct GfSetupParam;

enum {
  GAME_OBJ_LIST_CAPACITY = 1024,
};

class GfGameObj : public mm::mtl::PtrSingleton<GfGameObj> {
public:
  static void build(const GfSetupParam &param);
  static void destroy();
  static void update(const fw::UpdateInfo &info);
  static void postUpdate(const fw::UpdateInfo &info);
  static const mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_OBJ_LIST_CAPACITY> *getList(u32 objectType);
  static const mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_OBJ_LIST_CAPACITY> *getListEnemyBlade();
  static bool isEmpty();
  static void bdatReload();
  static bool isValidGameObj(GF_OBJ_HANDLE *handle, bool isCheckState, mm::mtl::FixStr<128> *reason);
  static bool isEnterGameObj(GF_OBJ_HANDLE *handle);
  static void destroyGameObj(GF_OBJ_HANDLE *handle, f32 fadeTime);
  static void destroyGameObjWithAttribute(GF_OBJ_HANDLE *handle, f32 fadeTime, u32 attribute);
  static void changeStopLayerIgnoreEventObj(u32 layer, bool isIgnore);
  u32 getObjNumberByEnArrangeId(u32 arrange);
};

} // namespace gf
