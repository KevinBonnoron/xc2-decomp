#pragma once
#include <stddef.h>

#include "battle/effect/effect_object.h"
#include "mm_mtl/fixed_list.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
}

namespace gf {
struct GF_OBJ_HANDLE;
}

namespace btl {

constexpr int EFFECT_DATA_COUNT = 100;
constexpr int REGISTER_DATA_COUNT = 30;

class EffectManager : public mm::mtl::PtrSingleton<EffectManager> {
public:
  struct PROC_DATA {
    u32 unknown00; // Inferred role: effect id; original member name unknown.
    int unknown04; // Inferred role: effect data index; original member name unknown.
  };

  struct REGISTER_PROC_DATA {
    u8 unknown00; // Inferred role: register data index; original member name unknown.
  };

  struct REGISTER_DATA {
    u8 _00[0x08 - 0x00];
    gf::GF_OBJ_HANDLE *unknown08; // Inferred role: attacker; original member name unknown.
    u8 _10[0x72 - 0x10];
    bool unknown72; // Inferred role: in use; original member name unknown.
    u8 _73[0xc0 - 0x73];
  };

  struct EFFECT_DATA {
    EffectObject unknown00; // Inferred role: effect; original member name unknown.
    u8 _260[0x261 - 0x260];
    bool unknown261; // Inferred role: in use; original member name unknown.
    u8 _262[0x270 - 0x262];
  };

  virtual ~EffectManager();
  void Initialize();
  static void Destroy();
  void Finalize();
  void NotifyMapChange();
  void DeleteAllEffect();
  EffectObject *GetEffect(u32 id);
  bool IsExistChrHitEffect(gf::GF_OBJ_HANDLE *handle) const;
  static void PreUpdate(const fw::UpdateInfo &updateInfo);
  void PreUpdateProc(const fw::UpdateInfo &updateInfo);
  static void Update(const fw::UpdateInfo &updateInfo);
  void UpdateProc(const fw::UpdateInfo &updateInfo);

  u8 _08[0x10 - 0x08];
  EFFECT_DATA unknown10[EFFECT_DATA_COUNT];                     // Inferred role: effects; original member name unknown.
  mm::mtl::FixedList<PROC_DATA, EFFECT_DATA_COUNT> unknownf3d0; // Inferred role: effects in use; original member name unknown.
  u8 _f8fc[0xf940 - 0xf8fc];
  // The constructor initializes 30 entries at a stride of 0xc0, but the 30th one would overlap unknown10f80:
  // only the first 29 are declared and the rest stays padding.
  REGISTER_DATA unknownf940[REGISTER_DATA_COUNT - 1]; // Inferred role: registered effects; original member name unknown.
  u8 _10f00[0x10f80 - 0x10f00];
  mm::mtl::FixedList<REGISTER_PROC_DATA, REGISTER_DATA_COUNT> unknown10f80; // Inferred role: registers in use; original member name unknown.
  u8 _11024[0x11030 - 0x11024];
};

static_assert(sizeof(EffectManager::EFFECT_DATA) == 0x270, "");
static_assert(sizeof(EffectManager::REGISTER_DATA) == 0xc0, "");
static_assert(offsetof(EffectManager, unknownf940) == 0xf940, "");
static_assert(offsetof(EffectManager, unknown10) == 0x10, "");
static_assert(offsetof(EffectManager, unknownf3d0) == 0xf3d0, "");
static_assert(offsetof(EffectManager, unknown10f80) == 0x10f80, "");
static_assert(sizeof(EffectManager) == 0x11030, "");

} // namespace btl
