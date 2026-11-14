#pragma once
#include "event/i_manager.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace event {

class HideManager : public IManager, public mm::mtl::Singleton<HideManager> {
public:
  static constexpr u32 LIST_UNKNOWN_1024 = 1024;      // Inferred role: list count; original name unknown.
  static constexpr u32 DEFINE_LIST_UNKNOWN_256 = 256; // Inferred role: define list count; original name unknown.
  static constexpr u32 OBJ_UNKNOWN_64 = 64;           // Inferred role: obj count; original name unknown.

  enum OBJ_TYPE {
    OBJ_TYPE_UNKNOWN_0, // Inferred role: none; original name unknown.
    OBJ_TYPE_UNKNOWN_1, // Inferred role: npc; original name unknown.
    OBJ_TYPE_UNKNOWN_2, // Inferred role: routed npc; original name unknown.
    OBJ_TYPE_UNKNOWN_3, // Inferred role: map obj; original name unknown.
    OBJ_TYPE_UNKNOWN_4, // Inferred role: effect; original name unknown.
    OBJ_TYPE_UNKNOWN_5, // Inferred role: se; original name unknown.
    OBJ_TYPE_UNKNOWN_6, // Inferred role: map lod; original name unknown.
  };

  enum GRP_TYPE {
    GRP_TYPE_UNKNOWN_0, // Inferred role: none; original name unknown.
  };

  enum {
    FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: hide group flag; original name unknown.
    FLAG_UNKNOWN_1 = 1 << 1, // Inferred role: hide list flag; original name unknown.
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
  void defineList(mm::mtl::FixedVector<u32, DEFINE_LIST_UNKNOWN_256> primaryList, mm::mtl::FixedVector<u32, DEFINE_LIST_UNKNOWN_256> secondaryList);
  void hideObj(OBJ_TYPE type, u32 id, bool isHide);
  Obj *searchObj(OBJ_TYPE type, u32 id);
  virtual void OnEventProc(MSG_TYPE type);

private:
  u32 unknown10; // Inferred role: flags; original member name unknown.
  GRP_TYPE m_group;
  mm::mtl::FixedVector<u32, LIST_UNKNOWN_1024> unknown18;   // Inferred role: primary list; original member name unknown.
  mm::mtl::FixedVector<u32, LIST_UNKNOWN_1024> unknown1020; // Inferred role: secondary list; original member name unknown.
  mm::mtl::FixedVector<Obj *, OBJ_UNKNOWN_64> unknown2028;  // Inferred role: objs; original member name unknown.
};

static_assert(sizeof(HideManager::Obj) == 0xc, "");
static_assert(sizeof(HideManager) == 0x2230, "");

} // namespace event
