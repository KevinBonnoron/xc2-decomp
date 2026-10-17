#pragma once
#include "gmk/gmk_base.h"
#include "gmk/gmk_cond.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "types.h"

struct CBdatWrapper;

namespace gmk {

class GmkEventGob;

class GmkEvent : public AGmkBase {
public:
  struct BdatInfo {
    void create(CBdatWrapper bdat, int id, const AGmkBase &gmk);
    bool isCondMatched() const;

    u16 condition;
    u16 eventId;
    u16 icon;
    ScenarioFlagCond scenarioFlag;
    QuestFlagCond questFlag;
  };

  static const GmkType GMK_TYPE = GMK_TYPE_EVENT;

  ~GmkEvent() override;
  GmkType getGmkType() const override;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void debugDraw() const override;

  u8 _48[0x100 - 0x48];
};

static_assert(sizeof(GmkEvent::BdatInfo) == 0xe, "");
static_assert(sizeof(GmkEvent) == 0x100, "");

typedef TGmkList<GmkEvent, GmkEvent::BdatInfo, 0x544e5645, 4, GmkEventGob> GmkEventList;

} // namespace gmk
