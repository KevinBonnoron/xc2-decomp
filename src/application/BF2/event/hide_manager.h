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
    u32 getID() const { return unknown04; }

  private:
    OBJ_TYPE m_type;
    u32 unknown04;  // Inferred role: id; original member name unknown.
    bool unknown08; // Inferred role: is hide org; original member name unknown.
    bool m_now;
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
  u32 unknown10; // Inferred role: flags; original member name unknown.
  GRP_TYPE m_group;
  mm::mtl::FixedVector<u32, LIST_COUNT> unknown18;    // Inferred role: primary list; original member name unknown.
  mm::mtl::FixedVector<u32, LIST_COUNT> unknown1020;  // Inferred role: secondary list; original member name unknown.
  mm::mtl::FixedVector<Obj *, OBJ_COUNT> unknown2028; // Inferred role: objs; original member name unknown.
};

static_assert(sizeof(HideManager::Obj) == 0xc, "");
static_assert(sizeof(HideManager) == 0x2230, "");

} // namespace event
