#pragma once
#include <stddef.h>

#include "gmk/gmk_base.h"
#include "gmk/gmk_cond.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "gmk/gmk_phantom.h"
#include "types.h"

struct CBdatWrapper;

namespace fw {
class SoundPack;
} // namespace fw

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

    u16 unknown00;           // Inferred role: condition; original member name unknown.
    u16 unknown02;           // Inferred role: depop condition; original member name unknown.
    f32 unknown04;           // Inferred role: damage interval; original member name unknown.
    u8 unknown08;            // Inferred role: pc damage; original member name unknown.
    u8 unknown09;            // Inferred role: enemy damage; original member name unknown.
    const char *unknown10;   // Inferred role: effect name; original member name unknown.
    u8 unknown18;            // Inferred role: se name; original member name unknown.
    u8 unknown19;            // Inferred role: volume max; original member name unknown.
    u8 unknown1a;            // Inferred role: volume min; original member name unknown.
    BootedGmkCond unknown1c; // Inferred role: depop booted gmk; original member name unknown.
    DistCond unknown20;      // Inferred role: effect disp dist; original member name unknown.
    DistCond unknown24;      // Inferred role: effect release dist; original member name unknown.
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

  ~GmkDmgSe() override { dispose(); }
  GmkType getGmkType() const override { return GMK_TYPE; }
  bool isValid() const override { return unknown08.unknown00 != nullptr && unknown20.unknown08 != nullptr; }
  void createGmkPhantom() const;
  void createSeInst(fw::SoundPack *pack, u32 id) const;
  void disposeSeInst(bool isFadeOut) const;
  void setSeVolume(f32 volume, f32 time) const;
  void dispose() override;
  void validateMute() const;

  u8 _48[0x50 - 0x48];
  mutable GmkPhantom unknown50; // Inferred role: phantom; original member name unknown.
  bool unknowne0;               // Inferred role: mute; original member name unknown.
  mutable u32 unknowne4;        // Inferred role: se handle; original member name unknown.
  mutable f32 unknowne8;        // Inferred role: se volume; original member name unknown.
};

static_assert(offsetof(GmkDmgSe, unknown50) == 0x50, "");
static_assert(offsetof(GmkDmgSe, unknowne0) == 0xe0, "");
static_assert(offsetof(GmkDmgSe, unknowne4) == 0xe4, "");
static_assert(offsetof(GmkDmgSe, unknowne8) == 0xe8, "");
static_assert(sizeof(GmkDmgSe) == 0xf0, "");

class GmkDmgSeList : public TGmkList<GmkDmgSe, GmkDmgSe::BdatInfo, 0x45534d44, 2, GmkDmgSeGob> {
public:
  explicit GmkDmgSeList(u32 updateGmkNumPerFrame) : TGmkList(updateGmkNumPerFrame) {}

  const AGmkBase *getInst(u32 index) const override;
};

} // namespace gmk
