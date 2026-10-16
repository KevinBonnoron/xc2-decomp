#pragma once
#include "gf/object/gf_obj_manager.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "types.h"

namespace gmk {

class GmkEnemyGob;

class GmkEnemy : public AGmkBase {
public:
  struct BdatInfo {
    u8 _00[0x8];
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
  explicit GmkEnemyList(u32 updateGmkNumPerFrame);
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
  u8 _228[0x470 - 0x228];
};

static_assert(sizeof(GmkEnemyList) == 0x470, "");

} // namespace gmk
