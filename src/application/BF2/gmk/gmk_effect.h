#pragma once
#include "gmk/gmk_base.h"
#include "gmk/gmk_cond.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "types.h"

struct CBdatWrapper;

namespace gmk {

class GmkEffectGobCustom;
class GmkEffectLocatorGob;

class GmkEffect : public AGmkBase {
public:
  struct BdatInfo {
    void create(CBdatWrapper bdat, int id, const AGmkBase &gmk);
    bool isPopCondMatched() const;

    u16 unknown00;              // Inferred role: condition; original member name unknown.
    ScenarioFlagCond unknown02; // Inferred role: scenario flag; original member name unknown.
    QuestFlagCond unknown06;    // Inferred role: quest flag; original member name unknown.
  };

  static const GmkType GMK_TYPE = GMK_TYPE_EFFECT;

  ~GmkEffect() override;
  GmkType getGmkType() const override;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void debugDraw() const override;
  void debugUpdateMmf() override;

  u8 _48[0xc8 - 0x48];
};

static_assert(sizeof(GmkEffect::BdatInfo) == 0xa, "");
static_assert(sizeof(GmkEffect) == 0xc8, "");

typedef TGmkList<GmkEffect, GmkEffect::BdatInfo, 0x54434645, 8, GmkEffectGobCustom> GmkEffectList;

class GmkEffectLocator : public AGmkBase {
public:
  struct BdatInfo {};

  static const GmkType GMK_TYPE = GMK_TYPE_EFFECT_LOCATOR;

  GmkType getGmkType() const override;
  bool isValid() const override;
};

static_assert(sizeof(GmkEffectLocator) == 0x48, "");

typedef TGmkList<GmkEffectLocator, GmkEffectLocator::BdatInfo, 0x434c4645, 1, GmkEffectLocatorGob> GmkEffectLocatorList;

} // namespace gmk
