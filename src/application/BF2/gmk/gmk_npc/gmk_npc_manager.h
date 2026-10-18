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

    gf::QuestID quest;
    u16 shopId;
    u16 mountPoint;
    u16 mountObject;
    u16 mountPoint2;
    u16 mountObject2;
  };

  ~GmkNpcIdInfo() { dispose(); }

  void dispose();
  void disposeGobInst(bool isFadeOut);
  void setActiveGmkNpc(AGmkNpc *npc);

  u16 npcId;
  u8 *bdat;
  mm::mtl::IntrusiveList<AGmkNpc> *npcs;
  AGmkNpc *activeNpc;
  BdatInfo bdatInfo;
  gf::GF_OBJ_HANDLE *handle;
};

static_assert(sizeof(GmkNpcIdInfo::BdatInfo) == 0xe, "");
static_assert(offsetof(GmkNpcIdInfo, bdat) == 0x08, "");
static_assert(offsetof(GmkNpcIdInfo, npcs) == 0x10, "");
static_assert(offsetof(GmkNpcIdInfo, activeNpc) == 0x18, "");
static_assert(offsetof(GmkNpcIdInfo, bdatInfo) == 0x20, "");
static_assert(offsetof(GmkNpcIdInfo, handle) == 0x30, "");
static_assert(sizeof(GmkNpcIdInfo) == 0x38, "");

class GmkNpcManager {
public:
  explicit GmkNpcManager(u32 updateNpcNumPerFrame);
  virtual ~GmkNpcManager() { dispose(); }

  void create();
  void dispose();
  void update(f32 deltaTime);
  void setUpdateNpcNumPerFrame(u32 num) { updateNpcNumPerFrame = num; }

  mm::mtl::Vector<GmkNpcIdInfo> npcIdInfos;
  u8 _30[0x34 - 0x30];
  u32 updateNpcNumPerFrame;
  u32 updateNpcIndex;
  bool isCreateGameEntity;
};

static_assert(sizeof(GmkNpcManager) == 0x40, "");

} // namespace gmk
