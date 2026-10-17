#pragma once
#include "gf/object/gf_obj_manager.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "types.h"

struct CBdatWrapper;

namespace gmk {

class GmkSalvageGobCustom;
class GmkSalvageLocatorGob;

class GmkSalvage : public AGmkBase {
public:
  struct BdatInfo {
    void create(CBdatWrapper bdat, int id, const AGmkBase &gmk);
    bool isCondMatched() const;

    u16 condition;
  };

  static const GmkType GMK_TYPE = GMK_TYPE_SALVAGE;

  ~GmkSalvage() override;
  GmkType getGmkType() const override;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void debugDraw() const override;
  void onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) override;
  void onPlayerAccessed(gf::GF_OBJ_HANDLE *handle) override;

  u8 _48[0x130 - 0x48];
};

static_assert(sizeof(GmkSalvage::BdatInfo) == 0x2, "");
static_assert(sizeof(GmkSalvage) == 0x130, "");

class GmkSalvageList : public TGmkList<GmkSalvage, GmkSalvage::BdatInfo, 0x564c4153, 2, GmkSalvageGobCustom> {
public:
  explicit GmkSalvageList(u32 updateGmkNumPerFrame);
  ~GmkSalvageList() override;

  void update(f32 deltaTime) override;
  void debugUpdateMmf() override;
  void debugDraw() const override;

protected:
  void createGmk(void *data) override;
  void disposeGmk() override;

private:
  u8 _228[0x5d0 - 0x228];
};

static_assert(sizeof(GmkSalvageList) == 0x5d0, "");

class GmkSalvageLocator : public AGmkBase {
public:
  struct BdatInfo {};

  static const GmkType GMK_TYPE = GMK_TYPE_SALVAGE_LOCATOR;

  ~GmkSalvageLocator() override;
  GmkType getGmkType() const override;
  bool isValid() const override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void debugDraw() const override;
  void onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) override;
  void onPlayerAccessed(gf::GF_OBJ_HANDLE *handle) override;

  u8 _48[0x100 - 0x48];
};

static_assert(sizeof(GmkSalvageLocator) == 0x100, "");

class GmkSalvageLocatorList : public TGmkList<GmkSalvageLocator, GmkSalvageLocator::BdatInfo, 0x434c4c53, 1, GmkSalvageLocatorGob> {
public:
  explicit GmkSalvageLocatorList(u32 updateGmkNumPerFrame) : TGmkList(updateGmkNumPerFrame) {}

  const AGmkBase *getInst(u32 index) const override;
};

} // namespace gmk
