#pragma once
#include <stddef.h>

#include "gf/game/quest/gf_quest_id.h"
#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/vector.h"
#include "types.h"

struct CBdatWrapper;

namespace gf {
struct GF_OBJ_HANDLE;
}

namespace gmk {

class AGmkNpc;

class GmkNpcIdInfo {
public:
  struct BdatInfo {
    BdatInfo();

    void create(CBdatWrapper bdat, int id);
    void dispose();

    gf::QuestID unknown00; // Inferred role: quest; original member name unknown.
    u16 unknown04;         // Inferred role: shop id; original member name unknown.
    u16 unknown06;         // Inferred role: mount point; original member name unknown.
    u16 unknown08;         // Inferred role: mount object; original member name unknown.
    u16 unknown0a;         // Inferred role: mount point2; original member name unknown.
    u16 unknown0c;         // Inferred role: mount object2; original member name unknown.
  };

  ~GmkNpcIdInfo() { dispose(); }

  void dispose();
  void disposeGobInst(bool isFadeOut);
  void setActiveGmkNpc(AGmkNpc *npc);

  u16 unknown00;                              // Inferred role: npc id; original member name unknown.
  u8 *unknown08;                              // Inferred role: bdat; original member name unknown.
  mm::mtl::IntrusiveList<AGmkNpc> *unknown10; // Inferred role: npcs; original member name unknown.
  AGmkNpc *unknown18;                         // Inferred role: active npc; original member name unknown.
  BdatInfo unknown20;                         // Inferred role: bdat info; original member name unknown.
  gf::GF_OBJ_HANDLE *unknown30;               // Inferred role: handle; original member name unknown.
};

static_assert(sizeof(GmkNpcIdInfo::BdatInfo) == 0xe, "");
static_assert(offsetof(GmkNpcIdInfo, unknown08) == 0x08, "");
static_assert(offsetof(GmkNpcIdInfo, unknown10) == 0x10, "");
static_assert(offsetof(GmkNpcIdInfo, unknown18) == 0x18, "");
static_assert(offsetof(GmkNpcIdInfo, unknown20) == 0x20, "");
static_assert(offsetof(GmkNpcIdInfo, unknown30) == 0x30, "");
static_assert(sizeof(GmkNpcIdInfo) == 0x38, "");

class GmkNpcManager {
public:
  explicit GmkNpcManager(u32 updateNpcNumPerFrame);
  virtual ~GmkNpcManager() { dispose(); }

  void create();
  void dispose();
  void update(f32 deltaTime);
  GmkNpcIdInfo *getNpcIdInfoByNpcId(int npcId);
  const GmkNpcIdInfo *getNpcIdInfoByNpcId(int npcId) const;
  static int getNpcIdInfoIdxFromNpcId(int npcId);
  void setUpdateNpcNumPerFrame(u32 num) { unknown34 = num; }

  mm::mtl::Vector<GmkNpcIdInfo> unknown08; // Inferred role: npc id infos; original member name unknown.
  u8 _30[0x34 - 0x30];
  u32 unknown34;  // Inferred role: update npc num per frame; original member name unknown.
  u32 unknown38;  // Inferred role: update npc index; original member name unknown.
  bool unknown3c; // Inferred role: create game entity; original member name unknown.
};

static_assert(sizeof(GmkNpcManager) == 0x40, "");

} // namespace gmk
