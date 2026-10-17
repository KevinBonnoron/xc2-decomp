#pragma once
#include "gmk/gmk_base.h"
#include "gmk/gmk_cond.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "types.h"

struct CBdatWrapper;

namespace gmk {

class GmkDmgEffectGob;
class GmkDmgGimmickGobCustom;
class GmkDmgPhantomGob;
class GmkDmgSeGob;

class GmkDmgGimmick : public AGmkBase {
public:
  struct BdatInfo {
    void create(CBdatWrapper bdat, int id, const AGmkBase &gmk);
    bool isCondMatched() const;

    u16 condition;
    u16 depopCondition;
    f32 damageInterval;
    u8 pcDamage;
    u8 enemyDamage;
    const char *effectName;
    u8 seName;
    u8 volumeMax;
    u8 volumeMin;
    BootedGmkCond depopBootedGmk;
    DistCond effectDispDist;
    DistCond effectReleaseDist;
  };

  static const GmkType GMK_TYPE = GMK_TYPE_DMG_GIMMICK;

  ~GmkDmgGimmick() override;
  GmkType getGmkType() const override;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void debugDraw() const override;

  u8 _48[0x88 - 0x48];
};

static_assert(sizeof(GmkDmgGimmick::BdatInfo) == 0x28, "");
static_assert(sizeof(GmkDmgGimmick) == 0x88, "");

typedef TGmkList<GmkDmgGimmick, GmkDmgGimmick::BdatInfo, 0x4d474d44, 1, GmkDmgGimmickGobCustom> GmkDmgGimmickList;

class GmkDmgPhantom : public AGmkBase {
public:
  struct BdatInfo {};

  static const GmkType GMK_TYPE = GMK_TYPE_DMG_PHANTOM;

  ~GmkDmgPhantom() override;
  GmkType getGmkType() const override;
  bool isValid() const override;
  void dispose() override;

  u8 _48[0xb0 - 0x48];
};

static_assert(sizeof(GmkDmgPhantom) == 0xb0, "");

class GmkDmgPhantomList : public TGmkList<GmkDmgPhantom, GmkDmgPhantom::BdatInfo, 0x48504d44, 2, GmkDmgPhantomGob> {
public:
  explicit GmkDmgPhantomList(u32 updateGmkNumPerFrame) : TGmkList(updateGmkNumPerFrame) {}

  const AGmkBase *getInst(u32 index) const override;
};

class GmkDmgEffect : public AGmkBase {
public:
  struct BdatInfo {};

  static const GmkType GMK_TYPE = GMK_TYPE_DMG_EFFECT;

  ~GmkDmgEffect() override;
  GmkType getGmkType() const override;
  bool isValid() const override;
  void dispose() override;
  void update(f32 deltaTime) override;

  u8 _48[0x50 - 0x48];
};

static_assert(sizeof(GmkDmgEffect) == 0x50, "");

class GmkDmgEffectList : public TGmkList<GmkDmgEffect, GmkDmgEffect::BdatInfo, 0x46454d44, 1, GmkDmgEffectGob> {
public:
  explicit GmkDmgEffectList(u32 updateGmkNumPerFrame) : TGmkList(updateGmkNumPerFrame) {}

  const AGmkBase *getInst(u32 index) const override;
};

class GmkDmgSe : public AGmkBase {
public:
  struct BdatInfo {};

  static const GmkType GMK_TYPE = GMK_TYPE_DMG_SE;

  ~GmkDmgSe() override;
  GmkType getGmkType() const override;
  bool isValid() const override;
  void dispose() override;

  u8 _48[0xf0 - 0x48];
};

static_assert(sizeof(GmkDmgSe) == 0xf0, "");

class GmkDmgSeList : public TGmkList<GmkDmgSe, GmkDmgSe::BdatInfo, 0x45534d44, 2, GmkDmgSeGob> {
public:
  explicit GmkDmgSeList(u32 updateGmkNumPerFrame) : TGmkList(updateGmkNumPerFrame) {}

  const AGmkBase *getInst(u32 index) const override;
};

} // namespace gmk
