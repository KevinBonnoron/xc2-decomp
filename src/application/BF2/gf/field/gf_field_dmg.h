#pragma once
#include <stddef.h>

#include "gf/event/gf_event.h"
#include "mm_mtl/singleton.h"
#include "mm_mtl/vector.h"
#include "types.h"

struct CBdatWrapper;

namespace gf {

struct GF_OBJ_HANDLE;
struct GfSetupParam;

class GfFieldDmgManager : public mm::mtl::PtrSingleton<GfFieldDmgManager>, public IGfEvent {
public:
  // Layout from GfFieldDmgManager::gevMapjump (1.0.0: 0x71002d77c0), which fills it from the bdat columns, and findBdatInfo (attribute id at +2).
  struct BdatInfo {
    // User-provided: Vector<BdatInfo>::resize stores the ten member bytes of each element instead of a memset.
    BdatInfo() : unknown00(0), unknown02(0), unknown04(0.0f), unknown08(0), unknown09(0) {}
    void create(const CBdatWrapper &bdat, int id);

    u16 unknown00; // Inferred role: condition; original member name unknown.
    u16 unknown02; // Inferred role: attribute id; original member name unknown.
    f32 unknown04; // Inferred role: damage interval; original member name unknown.
    u8 unknown08;  // Inferred role: damage rate to the player characters; original member name unknown.
    u8 unknown09;  // Inferred role: damage rate to the enemies; original member name unknown.
  };

  GfFieldDmgManager(const GfSetupParam *param);
  ~GfFieldDmgManager();
  void create(const GfSetupParam &param);
  void dispose();
  void gevMapjump(GEV event, const MapjumpCallbackInfo &info) override;
  const BdatInfo *findBdatInfo(u16 attribute) const;
  static void build(const GfSetupParam &param);
  static void destroy();

  mm::mtl::Vector<BdatInfo> unknown10; // Inferred role: BDAT_FLD_DMGFLOOR rows of the current map; original member name unknown.
};

static_assert(offsetof(GfFieldDmgManager::BdatInfo, unknown04) == 0x04, "");
static_assert(offsetof(GfFieldDmgManager::BdatInfo, unknown09) == 0x09, "");
static_assert(sizeof(GfFieldDmgManager::BdatInfo) == 0x0c, "");
static_assert(offsetof(GfFieldDmgManager, unknown10) == 0x10, "");
static_assert(sizeof(GfFieldDmgManager) == 0x38, "");

class GfFieldDmg {
public:
  struct CreateInfo {
    bool unknown00; // Inferred role: apply the damage; original member name unknown.
  };

  struct UpdateInfo {
    GF_OBJ_HANDLE *m_GF_OBJ_HANDLE; // Inferred role: damaged object; original member name unknown.
    int unknown08;                  // Inferred role: damage id of the ground; original member name unknown.
    f32 unknown0c;                  // Inferred role: delta time; original member name unknown.
  };

  GfFieldDmg(const CreateInfo *info);
  virtual ~GfFieldDmg() { dispose(); }
  void create(const CreateInfo &info);
  void dispose();
  void update(const UpdateInfo &info);
  static bool applyDamage(GF_OBJ_HANDLE *handle, u8 rate);
  static s32 calculateDamage(u32 maxHp, u8 rate, f32 reduction);

  bool unknown08; // Inferred role: apply the damage; original member name unknown.
  bool unknown09; // Inferred role: created; original member name unknown.
  u8 _0a[0x10 - 0x0a];
  const GfFieldDmgManager::BdatInfo *m_bdatInfo; // Inferred role: damage info of the current damage id; original member name unknown.
  u32 unknown18;                                 // Inferred role: current damage id; original member name unknown.
  f32 unknown1c;                                 // Inferred role: elapsed time; original member name unknown.
  bool unknown20;                                // Inferred role: damage applied this frame; original member name unknown.
};

static_assert(offsetof(GfFieldDmg, unknown08) == 0x08, "");
static_assert(offsetof(GfFieldDmg, m_bdatInfo) == 0x10, "");
static_assert(offsetof(GfFieldDmg, unknown18) == 0x18, "");
static_assert(offsetof(GfFieldDmg, unknown1c) == 0x1c, "");
static_assert(offsetof(GfFieldDmg, unknown20) == 0x20, "");
static_assert(sizeof(GfFieldDmg) == 0x28, "");

static_assert(offsetof(GfFieldDmg::UpdateInfo, unknown0c) == 0x0c, "");

} // namespace gf
