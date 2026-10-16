#pragma once
#include "gmk/gmk_base.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "types.h"

namespace gmk {

class GmkTutorialGob;

class GmkTutorial : public AGmkBase {
public:
  struct BdatInfo {
    u8 _00[0xa];
  };

  static const GmkType GMK_TYPE = GMK_TYPE_TUTORIAL;

  ~GmkTutorial() override;
  GmkType getGmkType() const override;
  bool isValid() const override;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void debugDraw() const override;

  u8 _48[0x100 - 0x48];
};

static_assert(sizeof(GmkTutorial::BdatInfo) == 0xa, "");
static_assert(sizeof(GmkTutorial) == 0x100, "");

class GmkTutorialList : public TGmkList<GmkTutorial, GmkTutorial::BdatInfo, 0x4f545554, 4, GmkTutorialGob> {
public:
  explicit GmkTutorialList(u32 updateGmkNumPerFrame) : TGmkList(updateGmkNumPerFrame) {}
  ~GmkTutorialList() override;
};

} // namespace gmk
