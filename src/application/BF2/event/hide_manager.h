#pragma once
#include "event/i_manager.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace event {

class HideManager : public IManager, public mm::mtl::Singleton<HideManager> {
public:
  static constexpr u32 LIST_COUNT = 1024;
  static constexpr u32 DEFINE_LIST_COUNT = 256;
  static constexpr u32 OBJ_COUNT = 64;

  enum OBJ_TYPE {
    OBJ_TYPE_NONE,
    OBJ_TYPE_NPC,
    OBJ_TYPE_ROUTED_NPC,
    OBJ_TYPE_MAP_OBJ,
    OBJ_TYPE_EFFECT,
    OBJ_TYPE_SE,
    OBJ_TYPE_MAP_LOD,
  };

  enum GRP_TYPE {
    GRP_TYPE_NONE,
  };

  enum {
    FLAG_HIDE_GROUP = 1 << 0,
    FLAG_HIDE_LIST = 1 << 1,
  };

  class Obj {
  public:
    Obj(OBJ_TYPE type, u32 id);
    void clear();
    void exec(bool isHide);
    OBJ_TYPE getType() const;
    bool getNow() const;
    u32 getID() const { return mID; }

  private:
    OBJ_TYPE mType;
    u32 mID;
    bool mIsHideOrg;
    bool mIsHide;
  };

  HideManager();
  virtual ~HideManager() {}
  void clear();
  void hideGroup(bool isHide);
  void hideList(bool isHide);
  void resetHideObj();
  void update();
  void defineGroup(GRP_TYPE group);
  GRP_TYPE getGroup() const;
  void defineList(mm::mtl::FixedVector<u32, DEFINE_LIST_COUNT> primaryList, mm::mtl::FixedVector<u32, DEFINE_LIST_COUNT> secondaryList);
  void hideObj(OBJ_TYPE type, u32 id, bool isHide);
  Obj *searchObj(OBJ_TYPE type, u32 id);
  virtual void OnEventProc(MSG_TYPE type);

private:
  u32 flags;
  GRP_TYPE mGroup;
  mm::mtl::FixedVector<u32, LIST_COUNT> mPrimaryList;
  mm::mtl::FixedVector<u32, LIST_COUNT> mSecondaryList;
  mm::mtl::FixedVector<Obj *, OBJ_COUNT> objs;
};

static_assert(sizeof(HideManager::Obj) == 0xc, "");
static_assert(sizeof(HideManager) == 0x2230, "");

} // namespace event
