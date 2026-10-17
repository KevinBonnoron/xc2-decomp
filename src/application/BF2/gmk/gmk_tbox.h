#pragma once
#include <stddef.h>

#include "gf/object/gf_obj_manager.h"
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

  struct Data {
    u8 _00[0x4 - 0x0];
    u8 scale;
  };

  enum Progress {
    PROGRESS_CLOSED = 0,
    PROGRESS_OPENED = 1,
    PROGRESS_DUG = 2,
  };

  static const GmkType GMK_TYPE = GMK_TYPE_TBOX;
  static const int GAME_FLAG_PROGRESS = 0x7c15;

  u32 getProgress() const;
  GmkTbox();
  ~GmkTbox() override { dispose(); }
  GmkType getGmkType() const override { return GMK_TYPE; }
  int getGameFlagId() const;
  void successToAccess();
  void setTargetable(bool isTargetable) const;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void disposeGobInst(bool isFadeOut);
  void update(f32 deltaTime) override;
  bool canPopGobInst() const;
  void createGobInst();
  bool canDepopGobInst() const;
  void debugDraw() const override;
  void validateDisp() const;
  void onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) override;
  void onPlayerAccessed(gf::GF_OBJ_HANDLE *handle) override;

  const Data *getData() const { return static_cast<const Data *>(createInfo.data); }
  const BdatInfo *getBdatInfo() const { return reinterpret_cast<const BdatInfo *>(createInfo.info); }

  gf::GF_OBJ_HANDLE *handle;
  bool isDisp;
  f32 openedDisposeTime;
  f32 openedTimer;
};

static_assert(sizeof(GmkTbox::BdatInfo) == 0x10, "");
static_assert(offsetof(GmkTbox::Data, scale) == 0x4, "");
static_assert(offsetof(GmkTbox, handle) == 0x48, "");
static_assert(offsetof(GmkTbox, isDisp) == 0x50, "");
static_assert(offsetof(GmkTbox, openedDisposeTime) == 0x54, "");
static_assert(offsetof(GmkTbox, openedTimer) == 0x58, "");
static_assert(sizeof(GmkTbox) == 0x60, "");

typedef TGmkList<GmkTbox, GmkTbox::BdatInfo, 0x584f4254, 6, GmkTboxGob> GmkTboxList;

} // namespace gmk
