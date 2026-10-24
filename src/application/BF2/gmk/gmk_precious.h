#pragma once
#include "gf/object/gf_obj_manager.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_cond.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "types.h"

struct CBdatWrapper;

namespace gmk {

class GmkPreciousGob;

class GmkPrecious : public AGmkBase {
public:
  struct BdatInfo {
    void create(CBdatWrapper bdat, int id, const AGmkBase &gmk);
    void dispose();
    bool isPopCondMatched() const;

    u16 unknown00;              // Inferred role: item id; original member name unknown.
    u16 unknown02;              // Inferred role: condition; original member name unknown.
    u16 unknown04;              // Inferred role: quest id; original member name unknown.
    ScenarioFlagCond unknown06; // Inferred role: scenario flag; original member name unknown.
    QuestFlagCond unknown0a;    // Inferred role: quest flag; original member name unknown.
    TimeCond unknown10;         // Inferred role: time cond; original member name unknown.
    WeatherCond unknown20;      // Inferred role: weather cond; original member name unknown.
  };

  static const GmkType GMK_TYPE = GMK_TYPE_PRECIOUS;

  ~GmkPrecious() override;
  GmkType getGmkType() const override;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void debugDraw() const override;
  void onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) override;

  u8 _48[0x78 - 0x48];
};

static_assert(sizeof(GmkPrecious::BdatInfo) == 0x30, "");
static_assert(sizeof(GmkPrecious) == 0x78, "");

typedef TGmkList<GmkPrecious, GmkPrecious::BdatInfo, 0x53435250, 2, GmkPreciousGob> GmkPreciousList;

} // namespace gmk
