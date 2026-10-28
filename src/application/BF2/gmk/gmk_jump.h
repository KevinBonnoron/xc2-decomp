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
    BdatInfo() : unknown00(0), unknown02(0), unknown04(10) {}
    void create(CBdatWrapper bdat, int id, const AGmkBase &gmk);
    bool isPopCondMatched() const;
    void debugDraw(const AGmkBase &gmk) const;

    u16 unknown00; // Inferred role: condition; original member name unknown.
    u8 unknown02;  // Inferred role: jump type; original member name unknown.
    u16 unknown04; // Inferred role: name radius; original member name unknown.
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

  const BdatInfo *getBdatInfo() const { return reinterpret_cast<const BdatInfo *>(unknown20.unknown10); }
  const Data *getData() const { return static_cast<const Data *>(unknown20.unknown08); }

  u8 _48[0x50 - 0x48];
  bool unknown50;               // Inferred role: cond matched; original member name unknown.
  gf::GF_OBJ_HANDLE *unknown58; // Inferred role: handle; original member name unknown.
  DistHvCond unknown60;         // Inferred role: pop dist; original member name unknown.
  DistHvCond unknown68;         // Inferred role: depop dist; original member name unknown.
  u32 unknown70;                // Inferred role: icon handle; original member name unknown.
  DistCond unknown74;           // Inferred role: icon dist; original member name unknown.
  bool unknown78;               // Inferred role: icon dead; original member name unknown.
  bool unknown79;               // Inferred role: disp; original member name unknown.
};

static_assert(offsetof(GmkJump, unknown50) == 0x50, "");
static_assert(offsetof(GmkJump, unknown58) == 0x58, "");
static_assert(offsetof(GmkJump, unknown60) == 0x60, "");
static_assert(offsetof(GmkJump, unknown70) == 0x70, "");
static_assert(offsetof(GmkJump, unknown74) == 0x74, "");
static_assert(offsetof(GmkJump, unknown78) == 0x78, "");
static_assert(offsetof(GmkJump, unknown79) == 0x79, "");

static_assert(sizeof(GmkJump::BdatInfo) == 0x6, "");
static_assert(sizeof(GmkJump) == 0x80, "");

typedef TGmkList<GmkJump, GmkJump::BdatInfo, 0x504d554a, 3, GmkJumpGobCustom> GmkJumpList;

} // namespace gmk
