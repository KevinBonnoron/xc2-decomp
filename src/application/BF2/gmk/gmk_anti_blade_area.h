#pragma once
#include "gmk/gmk_base.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "types.h"

struct CBdatWrapper;

namespace gmk {

class GmkAntiBladeAreaGob;

class GmkAntiBladeArea : public AGmkBase {
public:
  struct BdatInfo {
    void create(CBdatWrapper bdat, int id, const AGmkBase &gmk);
    void dispose() { unknown00 = 0; }

    u16 unknown00; // Inferred role: map rev id; original member name unknown.
  };

  static const GmkType GMK_TYPE = GMK_TYPE_ANTI_BLADE_AREA;

  ~GmkAntiBladeArea() override;
  GmkType getGmkType() const override;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void debugDraw() const override;

  u8 _48[0xf0 - 0x48];
};

static_assert(sizeof(GmkAntiBladeArea::BdatInfo) == 0x2, "");
static_assert(sizeof(GmkAntiBladeArea) == 0xf0, "");

typedef TGmkList<GmkAntiBladeArea, GmkAntiBladeArea::BdatInfo, 0x414c4241, 2, GmkAntiBladeAreaGob> GmkAntiBladeAreaList;

} // namespace gmk
