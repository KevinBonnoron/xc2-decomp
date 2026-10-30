#pragma once
#include <stddef.h>

#include "gmk/gmk_base.h"
#include "gmk/gmk_cond.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "gmk/gmk_phantom.h"
#include "mm_mtl/intrusive_list.h"
#include "types.h"

struct CBdatWrapper;

namespace gmk {

class GmkEventGob;

class GmkEvent : public AGmkBase, public mm::mtl::IntrusiveListNode<GmkEvent> {
public:
  struct BdatInfo {
    void create(CBdatWrapper bdat, int id, const AGmkBase &gmk);
    bool isCondMatched() const;

    u16 unknown00;              // Inferred role: condition; original member name unknown.
    u16 unknown02;              // Inferred role: event id; original member name unknown.
    u16 unknown04;              // Inferred role: icon; original member name unknown.
    ScenarioFlagCond unknown06; // Inferred role: scenario flag; original member name unknown.
    QuestFlagCond unknown0a;    // Inferred role: quest flag; original member name unknown.
  };

  static const GmkType GMK_TYPE = GMK_TYPE_EVENT;

  GmkEvent();
  ~GmkEvent() override { dispose(); }
  GmkType getGmkType() const override;
  void create(const CreateInfo &info) override;
  void beginEvent();
  void dispose() override;
  void update(f32 deltaTime) override;
  void debugDraw() const override;
  void disposeGmkPhantom();

  // Inferred helper: bdat info of the event; original name unknown.
  const BdatInfo *unknown001() const { return reinterpret_cast<const BdatInfo *>(unknown20.unknown10); }

  u8 _58[0x60 - 0x58];
  GmkPhantom unknown60; // Inferred role: phantom; original member name unknown.
  bool unknownf0;       // Role and original member name unknown.
  bool unknownf1;       // Role and original member name unknown.
  bool unknownf2;       // Role and original member name unknown.
  u8 _f3[0x100 - 0xf3];
};

static_assert(sizeof(GmkEvent::BdatInfo) == 0xe, "");
static_assert(offsetof(GmkEvent, unknown60) == 0x60, "");
static_assert(offsetof(GmkEvent, unknownf0) == 0xf0, "");
static_assert(offsetof(GmkEvent, unknownf1) == 0xf1, "");
static_assert(offsetof(GmkEvent, unknownf2) == 0xf2, "");
static_assert(sizeof(GmkEvent) == 0x100, "");

typedef TGmkList<GmkEvent, GmkEvent::BdatInfo, 0x544e5645, 4, GmkEventGob> GmkEventList;

} // namespace gmk
