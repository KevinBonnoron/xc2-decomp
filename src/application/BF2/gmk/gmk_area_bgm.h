#pragma once
#include "gmk/gmk_base.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "types.h"

struct CBdatWrapper;

namespace gmk {

class GmkAreaBgmGob;

class GmkAreaBgm : public AGmkBase {
public:
  struct BdatInfo {
    void create(CBdatWrapper bdat, int id, const AGmkBase &gmk);
    void dispose() { bgmCondition = 0; }

    u16 bgmCondition;
  };

  static const GmkType GMK_TYPE = GMK_TYPE_AREA_BGM;

  ~GmkAreaBgm() override;
  GmkType getGmkType() const override;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void debugDraw() const override;

  u8 _48[0x170 - 0x48];
};

static_assert(sizeof(GmkAreaBgm::BdatInfo) == 0x2, "");
static_assert(sizeof(GmkAreaBgm) == 0x170, "");

typedef TGmkList<GmkAreaBgm, GmkAreaBgm::BdatInfo, 0x52414742, 2, GmkAreaBgmGob> GmkAreaBgmList;

} // namespace gmk
