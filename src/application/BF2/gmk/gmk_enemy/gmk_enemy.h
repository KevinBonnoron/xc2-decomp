#pragma once
#include <stddef.h>

#include "gf/object/gf_obj_manager.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_cond.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "gmk/gmk_trigger.h"
#include "mm_mtl/vector.h"
#include "types.h"

struct CBdatWrapper;
namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace mm {
struct Vec3;
} // namespace mm

namespace gmk {

class GmkEnemyGob;
class GmkSquad;

// Layout evidence: gmk::GmkEnemyInsts::reqForcePopGobInst (0x71005efab8) copies these 8 bytes to offset 0x144 of the
// instances and GfSmnEnemyManager fills them; GmkEnemyInsts::createGobInsts copies the first byte to PopInfo::CreateInfo::unknown0c.
struct ForcePopEnemyInfo {
  u8 unknown00; // Role and original member name unknown.
  u8 _01[0x04 - 0x01];
  u32 unknown04; // Role and original member name unknown.
};

static_assert(sizeof(ForcePopEnemyInfo) == 0x8, "");

class GmkEnemyInsts {
public:
  class IPopXformFinder;

  // Layout evidence: GmkEnemy::create at 0x71005f05d0 fills it on the stack, GmkEnemyInsts::create copies 0x38 bytes of it
  // to the start of the instances and GmkEnemyInsts::dispose restores the defaults written by GmkEnemyInsts::GmkEnemyInsts.
  struct CreateInfo {
    CreateInfo()
        : unknown00(nullptr), unknown08(nullptr), unknown10(-1), unknown14(100.0f), unknown18(50.0f), unknown1c(110.0f), unknown20(55.0f), unknown24(0.0f), unknown28(0), unknown2c(0), unknown30(0),
          unknown34(0) {}

    AGmkBase *unknown00; // Inferred role: owner gimmick; original member name unknown.
    u8 *unknown08;       // Inferred role: bdat; original member name unknown.
    int unknown10;       // Inferred role: bdat id; original member name unknown.
    f32 unknown14;       // Inferred role: display radius; original member name unknown.
    f32 unknown18;       // Inferred role: display height; original member name unknown.
    f32 unknown1c;       // Inferred role: release radius; original member name unknown.
    f32 unknown20;       // Inferred role: release height; original member name unknown.
    f32 unknown24;       // Inferred role: repop time in seconds; original member name unknown.
    u32 unknown28;       // Role and original member name unknown.
    u32 unknown2c;       // Role and original member name unknown.
    u32 unknown30;       // Role and original member name unknown.
    u32 unknown34;       // Role and original member name unknown.
  };

  struct UpdateInfo {
    f32 unknown00;                    // Inferred role: delta time; original member name unknown.
    const mm::Vec3 *unknown08;        // Inferred role: position; original member name unknown.
    const IPopXformFinder *unknown10; // Inferred role: pop xform finder; original member name unknown.
  };

  struct BdatInfo {
    void create(CBdatWrapper bdat, int id, const AGmkBase &gmk);
    bool isInvincibleCondMatched() const;
    bool isPopCondMatchedOfSmn() const;

    u16 unknown00;              // Inferred role: condition; original member name unknown.
    bool unknown02;             // Inferred role: enemy priority; original member name unknown.
    bool unknown03;             // Inferred role: pop summon; original member name unknown.
    u16 unknown04;              // Inferred role: squad id; original member name unknown.
    u16 unknown06;              // Inferred role: squad scale; original member name unknown.
    u8 unknown08;               // Inferred role: form; original member name unknown.
    u8 unknown09;               // Inferred role: form range; original member name unknown.
    u16 unknown0a;              // Inferred role: invincible condition; original member name unknown.
    bool unknown0c;             // Role and original member name unknown.
    ScenarioFlagCond unknown0e; // Inferred role: scenario flag; original member name unknown.
    QuestFlagCond unknown12;    // Inferred role: quest flag; original member name unknown.
    TimeCond unknown18;         // Inferred role: time cond; original member name unknown.
    WeatherCond unknown28;      // Inferred role: weather cond; original member name unknown.
    CloudCond unknown38;        // Inferred role: cloud cond; original member name unknown.
    QuestFlagCond unknown48;    // Inferred role: invincible quest flag; original member name unknown.
  };

  struct PopInfo {
    // Layout evidence: GmkEnemyInsts::createGobInsts (0x71005efc40) fills it on the stack and PopInfo::create reads it.
    struct CreateInfo {
      u8 *unknown00; // Inferred role: bdat; original member name unknown.
      int unknown08; // Inferred role: bdat id; original member name unknown.
      u8 unknown0c;  // Inferred role: type genus filter; original member name unknown.
    };

    struct PopEnemyInfo {
      void dispose();

      // Inferred helper: number of game objects of this enemy; original name unknown.
      u32 unknown001() const {
        if (unknown10 == nullptr || unknown18 == nullptr) {
          return 0;
        }
        return (unknown10->size() + unknown18->size()) & 0xff;
      }

      // Inferred helper: number of defeated enemies, the high byte of unknown20; original name unknown.
      u8 unknown002() const { return unknown20 >> 8; }

      u16 unknown00; // Inferred role: enemy id; original member name unknown.
      u8 unknown02;  // Role and original member name unknown.
      u8 unknown03;  // Role and original member name unknown.
      u8 unknown04;  // Inferred role: enemy num; original member name unknown.
      u8 _05[0x07 - 0x05];
      u8 unknown07; // Inferred role: type genus; original member name unknown.
      u8 _08[0x10 - 0x08];
      mm::mtl::Vector<gf::GF_OBJ_HANDLE *> *unknown10; // Inferred role: game objects; original member name unknown.
      mm::mtl::Vector<gf::GF_OBJ_HANDLE *> *unknown18; // Inferred role: game objects; original member name unknown.
      u16 unknown20;                                   // Inferred role: counts, the low byte then the defeated num in the high byte; original member name unknown.
      u8 _22[0x24 - 0x22];
      u32 unknown24; // Role and original member name unknown.
    };

    void dispose();
    void create(const CreateInfo &info);
    int getGobInstNum() const;
    bool isPopFinished() const;
    void removeGobInst(gf::GF_OBJ_HANDLE *handle, bool isDead);
    void removeDefeatedNamedEnemyInfo();
    bool hasEneID(u16 eneId, bool flag) const;
    bool hasTypeGenus(u8 genus, bool flag) const;

    u16 unknown00; // Role and original member name unknown.
    u8 unknown02;  // Role and original member name unknown.
    u8 _03[0x08 - 0x03];
    PopEnemyInfo unknown08[4]; // Inferred role: enemies; original member name unknown.
  };

  // Inferred role: matched; original type name unknown.
  enum unknown004 {
    unknown004_0 = 1 << 0, // Inferred role: pop condition matched; original name unknown.
    unknown004_1 = 1 << 1, // Inferred role: pop distance condition matched; original name unknown.
    unknown004_2 = 1 << 2, // Inferred role: depop distance condition matched; original name unknown.
  };

  bool isPopFinished() const;
  void validateDisp(gf::GF_OBJ_HANDLE *handle) const;
  void validateDisp() const;
  bool reqForcePopGobInst(const ForcePopEnemyInfo &info) const;
  bool isQuestDead() const;
  int getGobInstCapa() const;
  gf::GF_OBJ_HANDLE *getGobInst(u32 index) const;
  void update(const UpdateInfo &info);
  void seqUpdatePopDepop(const UpdateInfo &info);
  void removeGobInst(gf::GF_OBJ_HANDLE *handle);
  void disposeGobInsts(bool isFadeOut, bool isCheckBattle);
  void seqUpdateRepopCounter(const UpdateInfo &info);
  void createGobInsts();
  void onEnemyDead(gf::GF_OBJ_HANDLE *handle);
  void dispose();
  void disposeSquad();

  CreateInfo unknown00;    // Inferred role: create info; original member name unknown.
  BdatInfo unknown38;      // Inferred role: bdat info; original member name unknown.
  DistHvCond unknown88;    // Inferred role: pop dist; original member name unknown.
  DistHvCond unknown90;    // Inferred role: depop dist; original member name unknown.
  PopInfo unknown98;       // Inferred role: pop info; original member name unknown.
  bool unknown140;         // Inferred role: display enabled; original member name unknown.
  mutable bool unknown141; // Inferred role: force pop requested; original member name unknown.
  u8 _142[0x144 - 0x142];
  mutable ForcePopEnemyInfo unknown144; // Inferred role: force pop request; original member name unknown.
  u8 _14c[0x150 - 0x14c];
  GmkSquad *unknown150; // Inferred role: squad; original member name unknown.
  bool unknown158;      // Inferred role: pop condition flag; original member name unknown.
  bool unknown159;      // Inferred role: pop condition matched; original member name unknown.
  bool unknown15a;      // Inferred role: request to clear the repop counter; original member name unknown.
  u8 _15b[0x160 - 0x15b];
  void (GmkEnemyInsts::*unknown160)(const UpdateInfo &info); // Inferred role: seq; original member name unknown.
  f32 unknown170;                                            // Inferred role: repop counter; original member name unknown.
  u8 _174[0x178 - 0x174];
  u64 unknown178;  // Inferred role: matched condition flags; original member name unknown.
  bool unknown180; // Role and original member name unknown.
  u8 _181[0x188 - 0x181];
};

static_assert(sizeof(GmkEnemyInsts::BdatInfo) == 0x50, "");
static_assert(sizeof(GmkEnemyInsts::CreateInfo) == 0x38, "");
static_assert(offsetof(GmkEnemyInsts, unknown38) == 0x38, "");
static_assert(offsetof(GmkEnemyInsts, unknown88) == 0x88, "");
static_assert(offsetof(GmkEnemyInsts, unknown90) == 0x90, "");
static_assert(sizeof(GmkEnemyInsts::PopInfo::PopEnemyInfo) == 0x28, "");
static_assert(offsetof(GmkEnemyInsts::PopInfo::PopEnemyInfo, unknown10) == 0x10, "");
static_assert(offsetof(GmkEnemyInsts::PopInfo::PopEnemyInfo, unknown18) == 0x18, "");
static_assert(offsetof(GmkEnemyInsts::PopInfo::PopEnemyInfo, unknown20) == 0x20, "");
static_assert(offsetof(GmkEnemyInsts::PopInfo::PopEnemyInfo, unknown24) == 0x24, "");
static_assert(sizeof(GmkEnemyInsts::PopInfo) == 0xa8, "");
static_assert(offsetof(GmkEnemyInsts, unknown98) == 0x98, "");
static_assert(offsetof(GmkEnemyInsts, unknown140) == 0x140, "");
static_assert(offsetof(GmkEnemyInsts, unknown141) == 0x141, "");
static_assert(offsetof(GmkEnemyInsts, unknown144) == 0x144, "");
static_assert(offsetof(GmkEnemyInsts, unknown150) == 0x150, "");
static_assert(offsetof(GmkEnemyInsts, unknown15a) == 0x15a, "");
static_assert(offsetof(GmkEnemyInsts, unknown160) == 0x160, "");
static_assert(offsetof(GmkEnemyInsts, unknown158) == 0x158, "");
static_assert(offsetof(GmkEnemyInsts, unknown170) == 0x170, "");
static_assert(offsetof(GmkEnemyInsts, unknown178) == 0x178, "");
static_assert(offsetof(GmkEnemyInsts, unknown180) == 0x180, "");
static_assert(sizeof(GmkEnemyInsts) == 0x188, "");

class GmkEnemyInsts::IPopXformFinder {
public:
  virtual bool findPosRot(mm::Vec3 &position, mm::Vec3 &rotation, gf::GF_OBJ_HANDLE *handle, const GmkEnemyInsts::PopInfo::PopEnemyInfo &info) const = 0;
  virtual bool isYSnap() const = 0;
  virtual bool onPopGob(gf::GF_OBJ_HANDLE *handle) const = 0;
  virtual void onCreateGobInsts(u32 num) const = 0;
};

class GmkEnemy : public AGmkBase {
public:
  struct BdatInfo {
    BdatInfo() : unknown00(0), unknown02(false), unknown04(0), unknown06(0) {}
    void create(CBdatWrapper bdat, int id, const AGmkBase &gmk);

    u16 unknown00;  // Inferred role: target point name; original member name unknown.
    bool unknown02; // Inferred role: pop summon; original member name unknown.
    u16 unknown04;  // Inferred role: display radius; original member name unknown.
    u16 unknown06;  // Inferred role: display height; original member name unknown.
  };

  struct Data {
    f32 unknown00;  // Inferred role: random walk radius; original member name unknown. The size of this structure is unknown.
    bool unknown04; // Inferred role: snap the pop position to the ground; original member name unknown.
  };

  // Layout evidence: the vtable at 0x11a3688 holds the four virtual functions of GmkEnemyInsts::IPopXformFinder in this order
  // (findPosRot called through slot 0 by PopInfo::findPopPosRot, onPopGob through slot 2 and onCreateGobInsts through slot 3).
  class PopXformFinder : public GmkEnemyInsts::IPopXformFinder {
  public:
    bool findPosRot(mm::Vec3 &position, mm::Vec3 &rotation, gf::GF_OBJ_HANDLE *handle, const GmkEnemyInsts::PopInfo::PopEnemyInfo &info) const override;
    bool isYSnap() const override;
    bool onPopGob(gf::GF_OBJ_HANDLE *handle) const override;
    void onCreateGobInsts(u32 num) const override;

    GmkEnemy *unknown08; // Inferred role: owner; original member name unknown.
  };

  static const GmkType GMK_TYPE = GMK_TYPE_ENEMY;

  ~GmkEnemy() override;
  GmkType getGmkType() const override;
  bool isValid() const override;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void debugDraw() const override;
  IGmkList *getOwnerGmkEnemyList() const;
  bool isPointInsideRandomWalk(const mm::Vec3 &position) const;
  mm::Vec3 &getPositionInRandomWalk(mm::Vec3 &result, f32 angleMin, f32 angleMax, f32 distanceMin, f32 distanceMax) const;
  void onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) override;

  const Data *getData() const { return static_cast<const Data *>(unknown20.unknown08); }

  GmkEnemyInsts unknown48; // Inferred role: enemy instances; original member name unknown.
};

static_assert(sizeof(GmkEnemy::PopXformFinder) == 0x10, "");
static_assert(offsetof(GmkEnemy, unknown48) == 0x48, "");
static_assert(sizeof(GmkEnemy::BdatInfo) == 0x8, "");
static_assert(sizeof(GmkEnemy) == 0x1d0, "");

class GmkEnemyList : public TGmkList<GmkEnemy, GmkEnemy::BdatInfo, 0x4d454e45, 5, GmkEnemyGob> {
public:
  struct BdatInfo {
    BdatInfo() : unknown00(-1), unknown04(100), unknown05(50), unknown06(10), unknown07(5), unknown08(3) {}

    bool create();

    int unknown00; // Inferred role: map id; original member name unknown.
    u8 unknown04;  // Inferred role: enemy display radius; original member name unknown.
    u8 unknown05;  // Inferred role: enemy display height; original member name unknown.
    u8 unknown06;  // Inferred role: enemy release radius; original member name unknown.
    u8 unknown07;  // Inferred role: enemy release height; original member name unknown.
    u8 unknown08;  // Inferred role: enemy repop time; original member name unknown.
  };

  explicit GmkEnemyList(u32 updateGmkNumPerFrame);
  ~GmkEnemyList() override { dispose(); }

  const AGmkBase *getInst(u32 index) const override;
  void setUpdateGmkNumPerFrame(u32 num) override;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void update(f32 deltaTime) override;
  bool updateImmediate() override;
  void debugUpdateMmf() override;
  void debugDraw() const override;

protected:
  void createGmk(void *data) override;

private:
  GmkEnemyList::BdatInfo unknown228; // Inferred role: bdat info; original member name unknown.
  GmkTriggerList unknown240;         // Inferred role: trigger list; original member name unknown.
};

static_assert(sizeof(GmkEnemyList::BdatInfo) == 0xc, "");
static_assert(sizeof(GmkEnemyList) == 0x470, "");

} // namespace gmk
