#pragma once
#include <stddef.h>

#include "gmk/gmk_base.h"
#include "gmk/gmk_cond.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

struct CBdatWrapper;

namespace gf {
class GfMenuCallContext;
} // namespace gf

namespace gmk {

class GmkClimbingGob;

class GmkClimbing : public AGmkBase {
public:
  struct BdatInfo {
    BdatInfo() : unknown00(0), unknown02(3) {}
    void create(CBdatWrapper bdat, int id, const AGmkBase &gmk);
    bool isPopCondMatched() const;

    u16 unknown00;              // Inferred role: condition; original member name unknown.
    u16 unknown02;              // Inferred role: climb icon radius; original member name unknown.
    ScenarioFlagCond unknown04; // Inferred role: scenario flag; original member name unknown.
    QuestFlagCond unknown08;    // Inferred role: quest flag; original member name unknown.
    BootedGmkCond unknown0c;    // Inferred role: booted gmk; original member name unknown.
  };

  static const GmkType GMK_TYPE = GMK_TYPE_CLIMBING;

  GmkClimbing() : unknown48(nullptr), unknown50(mm::Vec3::zero) {}
  ~GmkClimbing() override { dispose(); }
  GmkType getGmkType() const override;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void disposeIcon();
  void update(f32 deltaTime) override;
  bool isPopCondMatched() const;
  void createIcon();
  void updateIcon();

  const BdatInfo *getBdatInfo() const { return reinterpret_cast<const BdatInfo *>(unknown20.unknown10); }

  gf::GfMenuCallContext *unknown48; // Inferred role: menu icon; original member name unknown.
  mm::Vec3 unknown50;               // Inferred role: icon position; original member name unknown.
};

static_assert(sizeof(GmkClimbing::BdatInfo) == 0x10, "");
static_assert(offsetof(GmkClimbing, unknown48) == 0x48, "");
static_assert(offsetof(GmkClimbing, unknown50) == 0x50, "");
static_assert(sizeof(GmkClimbing) == 0x60, "");

typedef TGmkList<GmkClimbing, GmkClimbing::BdatInfo, 0x424d4c43, 2, GmkClimbingGob> GmkClimbingList;

} // namespace gmk
