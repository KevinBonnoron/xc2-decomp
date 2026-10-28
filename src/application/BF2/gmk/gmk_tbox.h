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
    BdatInfo() : unknown00(0), unknown02(false), unknown03(0), unknown04(0), unknown05(false), unknown08(), unknown0c() {}
    void create(u8 *bdat, int id, const AGmkBase &gmk);
    void dispose();
    bool isPopCondMatchedExceptDist() const;
    bool isPopCondMatched(const mm::Vec3 &position) const;
    bool isDepopCondMatched(const mm::Vec3 &position) const;
    void debugDraw(const AGmkBase &gmk) const;

    u16 unknown00;      // Inferred role: condition; original member name unknown.
    bool unknown02;     // Inferred role: dig; original member name unknown.
    u8 unknown03;       // Inferred role: msg visible; original member name unknown.
    u8 unknown04;       // Inferred role: msg dig visible; original member name unknown.
    bool unknown05;     // Inferred role: tbox category; original member name unknown.
    DistCond unknown08; // Inferred role: pop dist; original member name unknown.
    DistCond unknown0c; // Inferred role: depop dist; original member name unknown.
  };

  struct Data {
    u8 _00[0x4 - 0x0];
    u8 unknown04; // Inferred role: scale; original member name unknown.
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

  const Data *getData() const { return static_cast<const Data *>(unknown20.unknown08); }
  const BdatInfo *getBdatInfo() const { return reinterpret_cast<const BdatInfo *>(unknown20.unknown10); }

  gf::GF_OBJ_HANDLE *unknown48; // Inferred role: handle; original member name unknown.
  bool unknown50;               // Inferred role: disp; original member name unknown.
  f32 unknown54;                // Inferred role: opened dispose time; original member name unknown.
  f32 unknown58;                // Inferred role: opened timer; original member name unknown.
};

static_assert(sizeof(GmkTbox::BdatInfo) == 0x10, "");
static_assert(offsetof(GmkTbox::Data, unknown04) == 0x4, "");
static_assert(offsetof(GmkTbox, unknown48) == 0x48, "");
static_assert(offsetof(GmkTbox, unknown50) == 0x50, "");
static_assert(offsetof(GmkTbox, unknown54) == 0x54, "");
static_assert(offsetof(GmkTbox, unknown58) == 0x58, "");
static_assert(sizeof(GmkTbox) == 0x60, "");

typedef TGmkList<GmkTbox, GmkTbox::BdatInfo, 0x584f4254, 6, GmkTboxGob> GmkTboxList;

} // namespace gmk
