#pragma once
#include <stddef.h>

#include "gf/data/gf_bdat_wrapper.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_cond.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "types.h"

namespace gmk {

class GmkEffectGobCustom;
class GmkEffectLocatorGob;

class GmkEffect : public AGmkBase {
public:
  struct Data {
    const char *unknown00; // Inferred role: effect name; original member name unknown.
  };

  struct BdatInfo {
    void create(CBdatWrapper bdat, int id, const AGmkBase &gmk);
    bool isPopCondMatched() const;

    u16 unknown00;              // Inferred role: condition; original member name unknown.
    ScenarioFlagCond unknown02; // Inferred role: scenario flag; original member name unknown.
    QuestFlagCond unknown06;    // Inferred role: quest flag; original member name unknown.
  };

  static const GmkType GMK_TYPE = GMK_TYPE_EFFECT;

  GmkEffect();
  ~GmkEffect() override { dispose(); }
  GmkType getGmkType() const override;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void debugDraw() const override;
  void debugUpdateMmf() override;
  void createInst();
  void disposeInst(bool isFadeOut);
  void applyEffectParam(bool isUpdate) const;
  void updatePopDepopCond();
  void seqValidateResHandle(f32 deltaTime);
  void seqUpdate(f32 deltaTime);
  bool canPopInst() const;
  bool canDepopInst() const;
  void validateDisp() const;

  const Data *getData() const { return static_cast<const Data *>(unknown20.unknown08); }

  u64 unknown48;                     // Role and original member name unknown.
  TimeCond unknown50;                // Inferred role: time cond; original member name unknown.
  WeatherCond unknown60;             // Inferred role: weather cond; original member name unknown.
  InOutDoorCond unknown70;           // Inferred role: indoor and outdoor cond; original member name unknown.
  CloudCond unknown80;               // Inferred role: cloud sea cond; original member name unknown.
  void (GmkEffect::*unknown90)(f32); // Inferred role: sequence; original member name unknown.
  void *unknowna0;                   // Role and original member name unknown.
  bool unknowna8;                    // Role and original member name unknown.
  u8 _a9[0xac - 0xa9];
  u32 unknownac;  // Role and original member name unknown.
  bool unknownb0; // Role and original member name unknown.
  u8 _b1[0xb8 - 0xb1];
  u64 unknownB8_0 : 1;  // Role and original member name unknown.
  u64 unknownB8_1 : 1;  // Inferred role: can pop; original member name unknown.
  u64 unknownB8_2 : 1;  // Inferred role: can depop; original member name unknown.
  u64 unknownB8_3 : 61; // Role and original member name unknown.
  bool unknownc0;       // Role and original member name unknown.
  bool unknownc1;       // Inferred role: fade out inst; original member name unknown.
  u8 _c2[0xc8 - 0xc2];
};

static_assert(sizeof(GmkEffect::BdatInfo) == 0xa, "");
static_assert(offsetof(GmkEffect, unknown48) == 0x48, "");
static_assert(offsetof(GmkEffect, unknown50) == 0x50, "");
static_assert(offsetof(GmkEffect, unknown60) == 0x60, "");
static_assert(offsetof(GmkEffect, unknown70) == 0x70, "");
static_assert(offsetof(GmkEffect, unknown80) == 0x80, "");
static_assert(offsetof(GmkEffect, unknown90) == 0x90, "");
static_assert(offsetof(GmkEffect, unknowna0) == 0xa0, "");
static_assert(offsetof(GmkEffect, unknowna8) == 0xa8, "");
static_assert(offsetof(GmkEffect, unknownac) == 0xac, "");
static_assert(offsetof(GmkEffect, unknownb0) == 0xb0, "");
static_assert(offsetof(GmkEffect, unknownc0) == 0xc0, "");
static_assert(offsetof(GmkEffect, unknownc1) == 0xc1, "");
static_assert(sizeof(GmkEffect) == 0xc8, "");

typedef TGmkList<GmkEffect, GmkEffect::BdatInfo, 0x54434645, 8, GmkEffectGobCustom> GmkEffectList;

class GmkEffectLocator : public AGmkBase {
public:
  struct BdatInfo {
    void create(CBdatWrapper, int, const AGmkBase &) {}
  };

  static const GmkType GMK_TYPE = GMK_TYPE_EFFECT_LOCATOR;

  GmkEffectLocator() {}
  GmkType getGmkType() const override;
  bool isValid() const override;
};

static_assert(sizeof(GmkEffectLocator) == 0x48, "");

typedef TGmkList<GmkEffectLocator, GmkEffectLocator::BdatInfo, 0x434c4645, 1, GmkEffectLocatorGob> GmkEffectLocatorList;

} // namespace gmk
