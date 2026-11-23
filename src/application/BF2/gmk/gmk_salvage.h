#pragma once
#include <stddef.h>

#include "gf/data/gf_bdat_chrenarrange.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/field/gf_fobj_dropitem.h"
#include "gf/object/gf_obj_manager.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_form_pc.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "gmk/gmk_set.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace gmk {

class GmkSalvageGobCustom;
class GmkSalvageLocator;
class GmkSalvageLocatorGob;

class GmkSalvage : public AGmkBase {
public:
  struct Data {
    int unknown00; // Role and original member name unknown.
    int unknown04; // Role and original member name unknown.
    int unknown08; // Role and original member name unknown.
    int unknown0c; // Role and original member name unknown.
    int unknown10; // Role and original member name unknown.
    int unknown14; // Role and original member name unknown.
  };

  struct RaffleInfo {
    u32 unknown00; // Inferred role: number of treasure boxes; original member name unknown.
    f32 unknown04; // Inferred role: button challenge point; original member name unknown.
    u32 unknown08; // Inferred role: skill point; original member name unknown.
  };

  struct RaffleResult {
    // Inferred role: enemy entry of the raffle result; original type name unknown.
    struct unknown001 {
      // Inferred name; kept as an exception to the unknown-name rule (AGENTS.md): single-user helper whose existence only the match proves; rename if a sibling build gives a symbol.
      // Its user, isPowerfullEnemyExist (0x71006097bc, 66 instructions), matches only with a method called on the by-value loop copy: with the sum written in the loop
      // (`(arrange->getChrEnArrangeLv(enemy.unknown00) & 0xff) + enemy.unknown02`) the copy is split into ldrh/ldrsb (63 instructions), and a static helper taking the
      // entry by value gives the loop test `cmp; b.hs` (60), where the game keeps the word load and `cset ls; csel hi; cbnz`.
      u32 getLevel(const gf::GfBdatChrEnArrange *arrange) const { return (arrange->getChrEnArrangeLv(unknown00) & 0xff) + unknown02; }

      u16 unknown00; // Role and original member name unknown.
      s8 unknown02;  // Role and original member name unknown.
    };

    RaffleResult();
    bool isPowerfullEnemyExist() const;

    u64 unknown00;    // Role and original member name unknown.
    s32 unknown08[3]; // Role and original member name unknown.
    u8 _14[0x18 - 0x14];
    u64 unknown18;    // Role and original member name unknown.
    s32 unknown20[3]; // Role and original member name unknown.
    u8 _2c[0x30 - 0x2c];
    u64 unknown30;    // Role and original member name unknown.
    s32 unknown38[3]; // Role and original member name unknown.
    // Layout evidence: the constructor (0x7100609714) clears three 4-byte entries at 0x44, 0x48 and 0x4c (`strh`, `strb`), and isPowerfullEnemyExist (0x71006097bc) reads
    // the three words, each with the same body (`ldr w22, [x19, #0x44]`, `#0x48`, `#0x4c`; halfword id in the low 16 bits, signed byte at bit 16).
    unknown001 unknown44[3]; // Role and original member name unknown.
  };

  struct BdatInfo {
    void create(CBdatWrapper bdat, int id, const AGmkBase &gmk);
    bool isCondMatched() const;

    u16 unknown00; // Inferred role: condition; original member name unknown.
  };

  static const GmkType GMK_TYPE = GMK_TYPE_SALVAGE; // Inferred name; shared by every gimmick class for the TGmkList templates.

  GmkSalvage();
  ~GmkSalvage() override { dispose(); }
  GmkType getGmkType() const override;
  int getGameFlagId() const;
  int getGmkSalvageLocatorNum() const;
  GmkSalvageLocator *getGmkSalvageLocator(u32 index) const;
  const GmkFormPc *getGmkFormPc() const;
  void createGfObjHandle();
  void disposeGfObjHandle();
  void disposeRaffle(bool isFadeOut);
  void createRaffle(const RaffleInfo &info);
  void popByRaffleResult();
  void seqUpdatePopDepop(f32 deltaTime);
  void seqValidateGmkSalvageLocatorDetails(f32 deltaTime);
  void disposeTboxes(bool isFadeOut);
  void disposeEnemies(bool isFadeOut);
  void validateDisp() const;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void debugDraw() const override;
  void onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) override;
  void onPlayerAccessed(gf::GF_OBJ_HANDLE *handle) override;

  const Data *getData() const { return static_cast<const Data *>(m_createInfo.unknown08); }
  const BdatInfo *getBdatInfo() const { return reinterpret_cast<const BdatInfo *>(m_createInfo.unknown10); }

  void (GmkSalvage::*unknown48)(f32);
  gf::GF_OBJ_HANDLE *unknown58;                           // Inferred role: game object; original member name unknown.
  f32 unknown60;                                          // Role and original member name unknown.
  f32 unknown64;                                          // Role and original member name unknown.
  mm::mtl::FixedVector<GmkSalvageLocator *, 3> unknown68; // Role and original member name unknown.
  mm::mtl::FixedVector<GmkSalvageLocator *, 3> unknown88; // Inferred role: treasure box locators; original member name unknown.
  GmkSalvageLocator *m_gmkSalvageLocator;                 // Role and original member name unknown.
  mm::mtl::FixedVector<GmkSalvageLocator *, 3> unknownb0; // Inferred role: enemy locators; original member name unknown.
  u8 unknownd0;                                           // Role and original member name unknown.
  u8 unknownd1;                                           // Role and original member name unknown.
  u8 _d2[0xd8 - 0xd2];
  RaffleResult m_raffleResult; // Inferred role: raffle result; original member name unknown.
  mutable bool unknown128;     // Inferred role: display enabled; original member name unknown.
  bool unknown129;             // Inferred role: request to sync the depop of the treasure boxes; original member name unknown.
};

static_assert(sizeof(GmkSalvage::RaffleResult) == 0x50, "");
static_assert(offsetof(GmkSalvage::RaffleResult, unknown44) == 0x44, "");
static_assert(sizeof(GmkSalvage::RaffleResult::unknown001) == 0x4, "");
static_assert(sizeof(GmkSalvage::BdatInfo) == 0x2, "");
static_assert(offsetof(GmkSalvage, unknown48) == 0x48, "");
static_assert(offsetof(GmkSalvage, unknown58) == 0x58, "");
static_assert(offsetof(GmkSalvage, unknown60) == 0x60, "");
static_assert(offsetof(GmkSalvage, unknown64) == 0x64, "");
static_assert(offsetof(GmkSalvage, unknown68) == 0x68, "");
static_assert(offsetof(GmkSalvage, unknown88) == 0x88, "");
static_assert(offsetof(GmkSalvage, m_gmkSalvageLocator) == 0xa8, "");
static_assert(offsetof(GmkSalvage, unknownb0) == 0xb0, "");
static_assert(offsetof(GmkSalvage, unknownd0) == 0xd0, "");
static_assert(offsetof(GmkSalvage, unknownd1) == 0xd1, "");
static_assert(offsetof(GmkSalvage, m_raffleResult) == 0xd8, "");
static_assert(offsetof(GmkSalvage, unknown128) == 0x128, "");
static_assert(offsetof(GmkSalvage, unknown129) == 0x129, "");
static_assert(sizeof(GmkSalvage) == 0x130, "");

class GmkSetOfSalvageChildren : public GmkSet {
public:
  GmkSetOfSalvageChildren() : GmkSet(nullptr) {}
  ~GmkSetOfSalvageChildren() override {}

  void createGmkLists(int gmkSetId) override;
  IGmkList *getGmkList(GmkType type) const;
};

static_assert(sizeof(GmkSetOfSalvageChildren) == 0x3a0, "");

class GmkSalvageList : public TGmkList<GmkSalvage, GmkSalvage::BdatInfo, 0x564c4153, 2, GmkSalvageGobCustom> {
public:
  explicit GmkSalvageList(u32 updateGmkNumPerFrame);
  ~GmkSalvageList() override {}

  void debugUpdateMmf() override;
  void debugDraw() const override;
  void update(f32 deltaTime) override;

  GmkSetOfSalvageChildren m_gmkSetOfSalvageChildren; // Inferred role: set of the salvage children lists; original member name unknown.

protected:
  void createGmk(void *data) override;
  void disposeGmk() override;
};

static_assert(sizeof(GmkSalvageList) == 0x5d0, "");

class GmkSalvageLocator : public AGmkBase {
public:
  struct BdatInfo {
    void create(CBdatWrapper, int, const AGmkBase &) {}
  };

  struct Data {
    u8 unknown00; // Role and original member name unknown.
  };

  static const GmkType GMK_TYPE = GMK_TYPE_SALVAGE_LOCATOR; // Inferred name; shared by every gimmick class for the TGmkList templates.

  GmkSalvageLocator();
  ~GmkSalvageLocator() override { dispose(); }
  GmkType getGmkType() const override;
  bool isValid() const override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void debugDraw() const override;
  void onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) override;
  void onPlayerAccessed(gf::GF_OBJ_HANDLE *handle) override;
  void onEnemyDead(gf::GF_OBJ_HANDLE *handle);
  void onEnemyHomeToPlayerAccess(gf::GF_OBJ_HANDLE *handle);
  void setEnemyPopInfo(int, int, s8);
  void disposeGobInst(bool isFadeOut);
  void createCollectDropitemEmitter();
  void createTboxGobInst();
  void createEnemyGobInst();
  void setTargetable(bool isTargetable) const;
  void reqDisposeTboxGobInst(f32 waitTime) const;
  void initWaitPopTime(f32 waitTime);
  void syncDepopTboxes();
  void seqWaitPop(f32 deltaTime);
  void seqPop(f32 deltaTime);

  const Data *getData() const { return static_cast<const Data *>(m_createInfo.unknown08); }

  void (GmkSalvageLocator::*unknown48)(f32); // Inferred role: sequence; original member name unknown.
  bool unknown58;                            // Inferred role: dropitem emitter created; original member name unknown.
  gf::GfDropitemEmitter m_dropitemEmitter;   // Inferred role: dropitem emitter of the collect locator; original member name unknown.
  gf::GF_OBJ_HANDLE *unknownc0;              // Inferred role: game object; original member name unknown.
  u8 unknownc8;                              // Role and original member name unknown.
  GmkSalvage *m_gmkSalvage;                  // Inferred role: owner salvage, set by GmkSalvage; original member name unknown.
  f32 unknownd8;                             // Role and original member name unknown.
  f32 unknowndc;                             // Role and original member name unknown.
  mutable f32 unknowne0;                     // Role and original member name unknown.
  mutable f32 unknowne4;                     // Inferred role: elapsed time before the depop of the treasure box; original member name unknown.
  int unknowne8;                             // Role and original member name unknown.
  int unknownec;                             // Role and original member name unknown.
  s8 unknownf0;                              // Role and original member name unknown.
  bool unknownf1;                            // Role and original member name unknown.
  bool unknownf2;                            // Role and original member name unknown.
};

static_assert(offsetof(GmkSalvageLocator, unknown48) == 0x48, "");
static_assert(offsetof(GmkSalvageLocator, unknown58) == 0x58, "");
static_assert(offsetof(GmkSalvageLocator, m_dropitemEmitter) == 0x60, "");
static_assert(offsetof(GmkSalvageLocator, unknownc0) == 0xc0, "");
static_assert(offsetof(GmkSalvageLocator, unknownc8) == 0xc8, "");
static_assert(offsetof(GmkSalvageLocator, m_gmkSalvage) == 0xd0, "");
static_assert(offsetof(GmkSalvageLocator, unknownd8) == 0xd8, "");
static_assert(offsetof(GmkSalvageLocator, unknowne0) == 0xe0, "");
static_assert(offsetof(GmkSalvageLocator, unknowne8) == 0xe8, "");
static_assert(offsetof(GmkSalvageLocator, unknownf0) == 0xf0, "");
static_assert(offsetof(GmkSalvageLocator, unknownf1) == 0xf1, "");
static_assert(offsetof(GmkSalvageLocator, unknownf2) == 0xf2, "");
static_assert(sizeof(GmkSalvageLocator) == 0x100, "");

class GmkSalvageLocatorList : public TGmkList<GmkSalvageLocator, GmkSalvageLocator::BdatInfo, 0x434c4c53, 1, GmkSalvageLocatorGob> {
public:
  explicit GmkSalvageLocatorList(u32 updateGmkNumPerFrame) : TGmkList(updateGmkNumPerFrame) {}

  const AGmkBase *getInst(u32 index) const override;

  // Inlined access to the locator vector; the original helper name is unknown.
  GmkSalvageLocator *unknown001(u32 index) { return &gmkInsts[index]; }
};

} // namespace gmk
