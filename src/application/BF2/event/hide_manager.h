#pragma once
#include "event/i_manager.h"
#include "mm_mtl/bitflag.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace event {

class HideManager : public IManager, public mm::mtl::Singleton<HideManager> {
public:
  static constexpr u32 LIST_UNKNOWN_1024 = 1024;      // Inferred role: list count; original name unknown.
  static constexpr u32 DEFINE_LIST_UNKNOWN_256 = 256; // Inferred role: define list count; original name unknown.
  static constexpr u32 OBJ_UNKNOWN_64 = 64;           // Inferred role: obj count; original name unknown.
  static constexpr u32 TBL_UNKNOWN_17 = 17;           // Inferred role: s_tbl entry count; original name unknown.

  enum OBJ_TYPE {
    OBJ_TYPE_UNKNOWN_0, // Inferred role: none; original name unknown.
    OBJ_TYPE_UNKNOWN_1, // Inferred role: npc; original name unknown.
    OBJ_TYPE_UNKNOWN_2, // Inferred role: routed npc; original name unknown.
    OBJ_TYPE_UNKNOWN_3, // Inferred role: map obj; original name unknown.
    OBJ_TYPE_UNKNOWN_4, // Inferred role: effect; original name unknown.
    OBJ_TYPE_UNKNOWN_5, // Inferred role: se; original name unknown.
    OBJ_TYPE_UNKNOWN_6, // Inferred role: map lod; original name unknown.
  };

  // Bit i of the group is the entry i of HideManager::s_tbl (the game symbol _ZN5event11HideManager5s_tblE, read by hideGroup, which tests `(1 << i) & m_group`).
  // Derivation of the names: each enumerator is the string of its entry without the EVTDISP_ prefix ("EVTDISP_PC_WEAPON" gives GRP_TYPE_PC_WEAPON).
  enum GRP_TYPE {
    GRP_TYPE_UNKNOWN_0 = 0, // Inferred role: none; original name unknown.
    GRP_TYPE_PC = 1 << 0,
    GRP_TYPE_PC_WEAPON = 1 << 1,
    GRP_TYPE_BLADE = 1 << 2,
    GRP_TYPE_ENEMY = 1 << 3,
    GRP_TYPE_EN_WEAPON = 1 << 4,
    GRP_TYPE_NPC = 1 << 5,
    GRP_TYPE_MOB = 1 << 6,
    GRP_TYPE_FIELD_OBJ = 1 << 7,
    GRP_TYPE_MAP = 1 << 8,
    GRP_TYPE_COLLECTION = 1 << 9,
    GRP_TYPE_SALVAGE = 1 << 10,
    GRP_TYPE_PRECIOUS = 1 << 11,
    GRP_TYPE_TBOX = 1 << 12,
    GRP_TYPE_JUMP = 1 << 13,
    GRP_TYPE_WARP = 1 << 14,
    GRP_TYPE_DMG_EFFECT = 1 << 15,
    GRP_TYPE_DMG_SE = 1 << 16,
  };

  enum {
    FLAG_UNKNOWN_0 = 0, // Inferred role: hide group flag; original name unknown.
    FLAG_UNKNOWN_1 = 1, // Inferred role: hide list flag; original name unknown.
  };

  // Inferred role: event display type of a hide group bit; original type name unknown.
  struct unknown001 {
    const char *unknown00; // Inferred role: name; original member name unknown.
    u32 unknown08;         // Inferred role: event display type; original member name unknown.
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

  static const unknown001 s_tbl[TBL_UNKNOWN_17]; // Name given by the xc2 symbol _ZN5event11HideManager5s_tblE.

private:
  // Inferred role: flags; original member name unknown. A bit set like AgelogManager and MotstmManager at the same offset 0x10 (decision 48): the game tests
  // the list flag with a byte load in clear (0x71000e2060) and, through a plain u32 member, clang widens the flag load of hideGroup (0x71000e2114) with the
  // load of m_group at 0x14 into one 64-bit load.
  mm::mtl::unknown027<32> unknown10;
  GRP_TYPE m_group;
  mm::mtl::FixedVector<u32, LIST_UNKNOWN_1024> unknown18;   // Inferred role: primary list; original member name unknown.
  mm::mtl::FixedVector<u32, LIST_UNKNOWN_1024> unknown1020; // Inferred role: secondary list; original member name unknown.
  mm::mtl::FixedVector<Obj *, OBJ_UNKNOWN_64> unknown2028;  // Inferred role: objs; original member name unknown.
};

static_assert(sizeof(HideManager::Obj) == 0xc, "");
static_assert(sizeof(HideManager) == 0x2230, "");

} // namespace event
