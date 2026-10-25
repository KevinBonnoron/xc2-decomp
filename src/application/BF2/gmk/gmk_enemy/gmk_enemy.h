#pragma once
#include <stddef.h>

#include "gf/object/gf_obj_manager.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "gmk/gmk_trigger.h"
#include "types.h"

struct CBdatWrapper;

namespace gmk {

class GmkEnemyGob;

class GmkEnemy : public AGmkBase {
public:
  struct BdatInfo {
    void create(CBdatWrapper bdat, int id, const AGmkBase &gmk);

    u16 unknown00;  // Inferred role: target point name; original member name unknown.
    bool unknown02; // Inferred role: pop summon; original member name unknown.
    u16 unknown04;  // Inferred role: display radius; original member name unknown.
    u16 unknown06;  // Inferred role: display height; original member name unknown.
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
  void onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) override;

  u8 *unknown48; // Role and original member name unknown.
  u8 *unknown50; // Role and original member name unknown.
  int unknown58; // Role and original member name unknown.
  u8 _5c[0x1d0 - 0x5c];
};

static_assert(offsetof(GmkEnemy, unknown48) == 0x48, "");
static_assert(offsetof(GmkEnemy, unknown50) == 0x50, "");
static_assert(offsetof(GmkEnemy, unknown58) == 0x58, "");
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

  explicit GmkEnemyList(u32 updateGmkNumPerFrame) : TGmkList(updateGmkNumPerFrame), unknown240(0xffffffff) {}
  ~GmkEnemyList() override;

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
