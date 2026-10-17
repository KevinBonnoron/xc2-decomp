#pragma once
#include "gf/object/gf_obj_manager.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_cond.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace gmk {

class GmkTboxGob;

class GmkTbox : public AGmkBase {
public:
  struct BdatInfo {
    void create(u8 *bdat, int id, const AGmkBase &gmk);
    void dispose();
    bool isPopCondMatchedExceptDist() const;
    bool isPopCondMatched(const mm::Vec3 &position) const;
    bool isDepopCondMatched(const mm::Vec3 &position) const;
    void debugDraw(const AGmkBase &gmk) const;

    u16 condition;
    bool isDig;
    u8 msgVisible;
    u8 msgDigVisible;
    bool isTboxCategory;
    DistCond popDist;
    DistCond depopDist;
  };

  static const GmkType GMK_TYPE = GMK_TYPE_TBOX;

  ~GmkTbox() override;
  GmkType getGmkType() const override;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void debugDraw() const override;
  void onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) override;
  void onPlayerAccessed(gf::GF_OBJ_HANDLE *handle) override;

  u8 _48[0x60 - 0x48];
};

static_assert(sizeof(GmkTbox::BdatInfo) == 0x10, "");
static_assert(sizeof(GmkTbox) == 0x60, "");

typedef TGmkList<GmkTbox, GmkTbox::BdatInfo, 0x584f4254, 6, GmkTboxGob> GmkTboxList;

} // namespace gmk
