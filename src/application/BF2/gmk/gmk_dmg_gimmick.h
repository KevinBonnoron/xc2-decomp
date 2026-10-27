#pragma once
#include <stddef.h>

#include "gf/data/gf_bdat_wrapper.h"
#include "gf/event/gf_event.h"
#include "gf/object/gf_obj_manager.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_cond.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "gmk/gmk_phantom.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace fw {
class SoundPack;
} // namespace fw

namespace gmk {

class GmkDmgEffect;
class GmkDmgEffectGob;
class GmkDmgGimmickGobCustom;
class GmkDmgPhantom;
class GmkDmgPhantomGob;
class GmkDmgSe;
class GmkDmgSeGob;

class GmkDmgGimmick : public AGmkBase {
public:
  struct Data {
    u16 unknown00; // Role and original member name unknown.
    u16 unknown02; // Role and original member name unknown.
    u16 unknown04; // Role and original member name unknown.
    u16 unknown06; // Role and original member name unknown.
    u16 unknown08; // Role and original member name unknown.
    u16 unknown0a; // Role and original member name unknown.
  };

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
  static mm::mtl::RTTI m_rtti;

  ~GmkDmgGimmick() override;
  GmkType getGmkType() const override;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void debugDraw() const override;
  const mm::mtl::RTTI *getRTTI() const;
  void seqWaitToCreateChild(f32 deltaTime);
  void validateDisp() const;
  GmkDmgPhantom *getGmkDmgPhantom(u32 index) const;
  GmkDmgEffect *getGmkDmgEffect(u32 index) const;
  GmkDmgSe *getGmkDmgSe(u32 index) const;
  void seqUpdatePopDepop(f32 deltaTime);

  u8 _48[0x58 - 0x48];
  void *unknown58;          // Role and original member name unknown.
  fw::SoundPack *unknown60; // Inferred role: map sound pack; original member name unknown.
  const Data *getData() const { return static_cast<const Data *>(unknown20.unknown08); }
  const BdatInfo *getBdatInfo() const { return reinterpret_cast<const BdatInfo *>(unknown20.unknown10); }

  void (GmkDmgGimmick::*unknown68)(f32); // Inferred role: sequence; original member name unknown.
  u8 _78[0x80 - 0x78];
  bool unknown80; // Role and original member name unknown.
  u8 _81[0x88 - 0x81];
};

static_assert(sizeof(GmkDmgGimmick::BdatInfo) == 0x28, "");
static_assert(offsetof(GmkDmgGimmick, unknown58) == 0x58, "");
static_assert(offsetof(GmkDmgGimmick, unknown60) == 0x60, "");
static_assert(offsetof(GmkDmgGimmick, unknown68) == 0x68, "");
static_assert(offsetof(GmkDmgGimmick, unknown80) == 0x80, "");
static_assert(sizeof(GmkDmgGimmick) == 0x88, "");

typedef TGmkList<GmkDmgGimmick, GmkDmgGimmick::BdatInfo, 0x4d474d44, 1, GmkDmgGimmickGobCustom> GmkDmgGimmickList;

class GmkDmgPhantom : public AGmkBase {
public:
  struct BdatInfo {
    void create(CBdatWrapper, int, const AGmkBase &) {}
  };

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
  struct BdatInfo {
    void create(CBdatWrapper, int, const AGmkBase &) {}
  };

  static const GmkType GMK_TYPE = GMK_TYPE_DMG_EFFECT;

  ~GmkDmgEffect() override { dispose(); }
  GmkType getGmkType() const override;
  bool isValid() const override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void createEffectInst(void *const &data) const;
  void disposeEffectInst(bool isFadeOut) const;
  void applyEffectParam() const;
  void validateDisp() const;

  bool unknown48; // Inferred role: visible; original member name unknown.
  u8 _49[0x4c - 0x49];
  mutable u32 unknown4C; // Role and original member name unknown.
};

static_assert(offsetof(GmkDmgEffect, unknown48) == 0x48, "");
static_assert(offsetof(GmkDmgEffect, unknown4C) == 0x4c, "");
static_assert(sizeof(GmkDmgEffect) == 0x50, "");

class GmkDmgEffectList : public TGmkList<GmkDmgEffect, GmkDmgEffect::BdatInfo, 0x46454d44, 1, GmkDmgEffectGob> {
public:
  explicit GmkDmgEffectList(u32 updateGmkNumPerFrame) : TGmkList(updateGmkNumPerFrame) {}

  const AGmkBase *getInst(u32 index) const override;
};

class GmkDmgSe : public AGmkBase {
public:
  struct BdatInfo {
    void create(CBdatWrapper, int, const AGmkBase &) {}
  };

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

class GmkDmgPhantomManager : public gf::IGfObjListener, public gf::IGfEvent {
public:
  GmkDmgPhantomManager();
  ~GmkDmgPhantomManager() override;
  void create();
  void dispose();
  void addTargetInfo(gf::GF_OBJ_HANDLE *handle);
  void removeTargetInfo(gf::GF_OBJ_HANDLE *handle);
  void listenerGfObj(OBJEVT event, gf::GF_OBJ_HANDLE *handle, u32 objectType) override;
  void gevPartyMover(gf::GF_OBJ_HANDLE *handle, bool isJoin) override;

  mm::mtl::Vector<GmkDmgPhantomTargetInfo> unknown10; // Inferred role: phantom targets; original member name unknown.
  bool unknown38;                                     // Role and original member name unknown.
};

static_assert(offsetof(GmkDmgPhantomManager, unknown10) == 0x10, "");
static_assert(offsetof(GmkDmgPhantomManager, unknown38) == 0x38, "");
static_assert(sizeof(GmkDmgPhantomManager) == 0x40, "");

} // namespace gmk
