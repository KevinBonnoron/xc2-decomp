#pragma once
#include <stddef.h>

#include "gf/object/gf_obj_manager.h"
#include "gmk/gmk_enemy/gmk_enemy.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "gmk/gmk_route.h"
#include "gmk/gmk_trigger.h"
#include "types.h"

namespace gmk {

class GmkRoutedEnemyGobCustom;
class GmkRoutedEnemyPointGobCustom;

class GmkRoutedEnemy : public GmkRoute {
public:
  static const GmkType GMK_TYPE = GMK_TYPE_ROUTED_ENEMY;

  ~GmkRoutedEnemy() override;
  GmkType getGmkType() const override;
  const IGmkList *getBindedRoutePointList() const override;
  bool isValid() const override;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void debugDraw() const override;
  IGmkList *getOwnerGmkEnemyList() const;
  void onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) override;

  void *unknown50; // Role and original member name unknown.
  void *unknown58; // Role and original member name unknown.
  int unknown60;   // Role and original member name unknown.
  u8 _64[0x200 - 0x64];
};

static_assert(offsetof(GmkRoutedEnemy, unknown50) == 0x50, "");
static_assert(offsetof(GmkRoutedEnemy, unknown58) == 0x58, "");
static_assert(offsetof(GmkRoutedEnemy, unknown60) == 0x60, "");
static_assert(sizeof(GmkRoutedEnemy) == 0x200, "");

class GmkRoutedEnemyList : public TGmkList<GmkRoutedEnemy, GmkEnemy::BdatInfo, 0x4d4e4552, 8, GmkRoutedEnemyGobCustom> {
public:
  explicit GmkRoutedEnemyList(u32 updateGmkNumPerFrame) : TGmkList(updateGmkNumPerFrame), unknown240(0xffffffff) {}
  ~GmkRoutedEnemyList() override;

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

static_assert(sizeof(GmkRoutedEnemyList) == 0x470, "");

class GmkRoutedEnemyPoint : public GmkRoutePoint {
public:
  struct BdatInfo {};

  static const GmkType GMK_TYPE = GMK_TYPE_ROUTED_ENEMY_POINT;

  ~GmkRoutedEnemyPoint() override;
  GmkType getGmkType() const override;
};

static_assert(sizeof(GmkRoutedEnemyPoint) == 0x50, "");

class GmkRoutedEnemyPointList : public TGmkList<GmkRoutedEnemyPoint, GmkRoutedEnemyPoint::BdatInfo, 0x50524e45, 4, GmkRoutedEnemyPointGobCustom> {
public:
  explicit GmkRoutedEnemyPointList(u32 updateGmkNumPerFrame) : TGmkList(updateGmkNumPerFrame) {}

protected:
  void createGmk(void *data) override;
};

} // namespace gmk
