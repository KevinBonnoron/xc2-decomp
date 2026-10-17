#pragma once
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

    u16 targetPointName;
    bool isPopSummon;
    u16 displayRadius;
    u16 displayHeight;
  };

  static const GmkType GMK_TYPE = GMK_TYPE_ENEMY;

  ~GmkEnemy() override;
  GmkType getGmkType() const override;
  bool isValid() const override;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void debugDraw() const override;
  void onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) override;

  u8 _48[0x1d0 - 0x48];
};

static_assert(sizeof(GmkEnemy::BdatInfo) == 0x8, "");
static_assert(sizeof(GmkEnemy) == 0x1d0, "");

class GmkEnemyList : public TGmkList<GmkEnemy, GmkEnemy::BdatInfo, 0x4d454e45, 5, GmkEnemyGob> {
public:
  struct BdatInfo {
    BdatInfo() : mapId(-1), enemyDisplayRadius(100), enemyDisplayHeight(50), enemyReleaseRadius(10), enemyReleaseHeight(5), enemyRepopTime(3) {}

    bool create();

    int mapId;
    u8 enemyDisplayRadius;
    u8 enemyDisplayHeight;
    u8 enemyReleaseRadius;
    u8 enemyReleaseHeight;
    u8 enemyRepopTime;
  };

  explicit GmkEnemyList(u32 updateGmkNumPerFrame) : TGmkList(updateGmkNumPerFrame), triggerList(0xffffffff) {}
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
  GmkEnemyList::BdatInfo bdatInfo;
  GmkTriggerList triggerList;
};

static_assert(sizeof(GmkEnemyList::BdatInfo) == 0xc, "");
static_assert(sizeof(GmkEnemyList) == 0x470, "");

} // namespace gmk
