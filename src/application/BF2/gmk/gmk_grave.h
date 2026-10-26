#pragma once
#include <stddef.h>

#include "gf/object/gf_obj_manager.h"
#include "gmk/gmk_acc.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_cond.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace mm {
struct Vec3;
} // namespace mm

namespace gmk {

class GmkGraveGob;

class GmkGrave : public AGmkBase {
public:
  struct BdatInfo {
    void create(u8 *bdat, int id, const AGmkBase &gmk);
    bool isPopCondMatched(const mm::Vec3 &position) const;
    bool isDepopCondMatched(const mm::Vec3 &position) const;
    void debugDraw(const AGmkBase &gmk) const;

    void dispose() {
      unknown00 = 0;
      unknown02 = 0;
    }

    bool isValid() const { return unknown00 != 0 && unknown02 != 0; }

    u16 unknown00;        // Inferred role: enemy pop id; original member name unknown.
    u16 unknown02;        // Inferred role: enemy id; original member name unknown.
    DistHvCond unknown04; // Inferred role: pop dist; original member name unknown.
    DistHvCond unknown0c; // Inferred role: depop dist; original member name unknown.
  };

  static const GmkType GMK_TYPE = GMK_TYPE_GRAVE;

  GmkGrave();
  ~GmkGrave() override { dispose(); }
  GmkType getGmkType() const override { return GMK_TYPE; }
  void dispose() override;
  void disposeGobInst(bool isFadeOut);
  void update(f32 deltaTime) override;
  void validateTargetable();
  bool canPopGobInst() const;
  void createGobInst();
  bool canDepopGobInst() const;
  void debugDraw() const override;
  bool reqPopEnemy() const;
  template <typename T> bool reqPopEnemy() const;
  void onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) override;
  void onPlayerAccessed(gf::GF_OBJ_HANDLE *handle) override;

  const BdatInfo *getBdatInfo() const { return reinterpret_cast<const BdatInfo *>(unknown20.unknown10); }

  bool unknown48;               // Inferred role: enemy defeated; original member name unknown.
  gf::GF_OBJ_HANDLE *unknown50; // Inferred role: handle; original member name unknown.
  GmkAcc unknown58;             // Inferred role: enemy; original member name unknown.
  bool unknown98;               // Inferred role: enemy popped; original member name unknown.
};

static_assert(sizeof(GmkGrave::BdatInfo) == 0x14, "");
static_assert(offsetof(GmkGrave, unknown48) == 0x48, "");
static_assert(offsetof(GmkGrave, unknown50) == 0x50, "");
static_assert(offsetof(GmkGrave, unknown58) == 0x58, "");
static_assert(offsetof(GmkGrave, unknown98) == 0x98, "");
static_assert(sizeof(GmkGrave) == 0xa0, "");

typedef TGmkList<GmkGrave, GmkGrave::BdatInfo, 0x56415247, 4, GmkGraveGob> GmkGraveList;

} // namespace gmk
