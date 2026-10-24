#pragma once
#include "gmk/gmk_base.h"
#include "gmk/gmk_cond.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "types.h"

struct CBdatWrapper;

namespace gmk {

class GmkMapJumpGob;

class GmkMapJump : public AGmkBase {
public:
  struct BdatInfo {
    void create(CBdatWrapper bdat, int id, const AGmkBase &gmk);
    bool isCondMatched() const;

    u16 unknown00;              // Inferred role: map jump id; original member name unknown.
    u16 unknown02;              // Inferred role: condition; original member name unknown.
    ScenarioFlagCond unknown04; // Inferred role: scenario flag; original member name unknown.
    QuestFlagCond unknown08;    // Inferred role: quest flag; original member name unknown.
  };

  static const GmkType GMK_TYPE = GMK_TYPE_MAP_JUMP;

  ~GmkMapJump() override;
  GmkType getGmkType() const override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void debugDraw() const override;

  u8 _48[0xf0 - 0x48];
};

static_assert(sizeof(GmkMapJump::BdatInfo) == 0xc, "");
static_assert(sizeof(GmkMapJump) == 0xf0, "");

typedef TGmkList<GmkMapJump, GmkMapJump::BdatInfo, 0x504a504d, 2, GmkMapJumpGob> GmkMapJumpList;

} // namespace gmk
