#pragma once
#include <stddef.h>

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
  bool canPopInst() const;
  bool canDepopInst() const;
  void validateDisp() const;

  u8 _48[0x90 - 0x48];
  void (GmkEffect::*unknown90)(f32); // Inferred role: sequence; original member name unknown.
  void *unknownA0;                   // Role and original member name unknown.
  bool unknownA8;                    // Role and original member name unknown.
  u8 _a9[0xac - 0xa9];
  u32 unknownAC;  // Role and original member name unknown.
  bool unknownB0; // Role and original member name unknown.
  u8 _b1[0xb8 - 0xb1];
  u64 unknownB8_0 : 1; // Role and original member name unknown.
  u64 unknownB8_1 : 1; // Inferred role: can pop; original member name unknown.
  u64 unknownB8_2 : 1; // Inferred role: can depop; original member name unknown.
  u64 : 61;
  bool unknownC0; // Role and original member name unknown.
  bool unknownC1; // Inferred role: fade out inst; original member name unknown.
  u8 _c2[0xc8 - 0xc2];
};

static_assert(sizeof(GmkEffect::BdatInfo) == 0xa, "");
static_assert(offsetof(GmkEffect, unknown90) == 0x90, "");
static_assert(offsetof(GmkEffect, unknownA0) == 0xa0, "");
static_assert(offsetof(GmkEffect, unknownA8) == 0xa8, "");
static_assert(offsetof(GmkEffect, unknownAC) == 0xac, "");
static_assert(offsetof(GmkEffect, unknownB0) == 0xb0, "");
static_assert(offsetof(GmkEffect, unknownC0) == 0xc0, "");
static_assert(offsetof(GmkEffect, unknownC1) == 0xc1, "");
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
