#pragma once
#include <stddef.h>

#include "gf/object/gf_obj_manager.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_cond.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

struct CBdatWrapper;
namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace gmk {

class GmkJumpGobCustom;

class GmkJump : public AGmkBase {
public:
  struct BdatInfo {
    void create(CBdatWrapper bdat, int id, const AGmkBase &gmk);
    bool isPopCondMatched() const;
    void debugDraw(const AGmkBase &gmk) const;

    u16 condition;
    u8 jumpType;
    u16 nameRadius;
  };

  static const GmkType GMK_TYPE = GMK_TYPE_JUMP;

  struct Data {
    mm::Vec3 position;
  };

  GmkJump();
  ~GmkJump() override { dispose(); }
  GmkType getGmkType() const override { return GMK_TYPE; }
  void create(const CreateInfo &info) override;
  void dispose() override;
  void disposeIcon(bool isFadeOut);
  void disposeGobInst(bool isFadeOut);
  void update(f32 deltaTime) override;
  bool canPopGobInst() const;
  void createGobInst();
  bool canDepopGobInst() const;
  void createIcon();
  void debugDraw() const override;
  void debugUpdateMmf() override;
  void validateIconPos();
  void validateDisp() const;
  void reqDeadIcon();
  void reqRecreateIcon();
  void onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) override;
  void onPlayerAccessed(gf::GF_OBJ_HANDLE *handle) override {}

  const BdatInfo *getBdatInfo() const { return reinterpret_cast<const BdatInfo *>(createInfo.info); }
  const Data *getData() const { return static_cast<const Data *>(createInfo.data); }

  u8 _48[0x50 - 0x48];
  bool isCondMatched;
  gf::GF_OBJ_HANDLE *handle;
  DistHvCond popDist;
  DistHvCond depopDist;
  u32 iconHandle;
  DistCond iconDist;
  bool isIconDead;
  bool isDisp;
};

static_assert(offsetof(GmkJump, isCondMatched) == 0x50, "");
static_assert(offsetof(GmkJump, handle) == 0x58, "");
static_assert(offsetof(GmkJump, popDist) == 0x60, "");
static_assert(offsetof(GmkJump, iconHandle) == 0x70, "");
static_assert(offsetof(GmkJump, iconDist) == 0x74, "");
static_assert(offsetof(GmkJump, isIconDead) == 0x78, "");
static_assert(offsetof(GmkJump, isDisp) == 0x79, "");

static_assert(sizeof(GmkJump::BdatInfo) == 0x6, "");
static_assert(sizeof(GmkJump) == 0x80, "");

typedef TGmkList<GmkJump, GmkJump::BdatInfo, 0x504d554a, 3, GmkJumpGobCustom> GmkJumpList;

} // namespace gmk
