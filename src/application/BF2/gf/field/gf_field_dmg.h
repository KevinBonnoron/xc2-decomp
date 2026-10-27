#pragma once
#include <stddef.h>

#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

struct GfSetupParam;

class GfFieldDmgManager : public mm::mtl::PtrSingleton<GfFieldDmgManager> {
public:
  struct BdatInfo;

  static void build(const GfSetupParam &param);
  static void destroy();
};

class GfFieldDmg {
public:
  struct CreateInfo {
    bool unknown00; // Inferred role: apply the damage; original member name unknown.
  };

  GfFieldDmg(const CreateInfo *info);
  virtual ~GfFieldDmg() { dispose(); }
  void create(const CreateInfo &info);
  void dispose();
  static s32 calculateDamage(u32 maxHp, u8 rate, f32 reduction);

  bool unknown08; // Inferred role: apply the damage; original member name unknown.
  bool unknown09; // Inferred role: created; original member name unknown.
  u8 _0a[0x10 - 0x0a];
  const GfFieldDmgManager::BdatInfo *unknown10; // Inferred role: damage info of the current damage id; original member name unknown.
  u32 unknown18;                                // Inferred role: current damage id; original member name unknown.
  f32 unknown1c;                                // Inferred role: elapsed time; original member name unknown.
  bool unknown20;                               // Inferred role: damage applied this frame; original member name unknown.
};

static_assert(offsetof(GfFieldDmg, unknown08) == 0x08, "");
static_assert(offsetof(GfFieldDmg, unknown10) == 0x10, "");
static_assert(offsetof(GfFieldDmg, unknown18) == 0x18, "");
static_assert(offsetof(GfFieldDmg, unknown1c) == 0x1c, "");
static_assert(offsetof(GfFieldDmg, unknown20) == 0x20, "");
static_assert(sizeof(GfFieldDmg) == 0x28, "");

} // namespace gf
