#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"
#include <stddef.h>

namespace mm {
struct Vec3;
}

namespace fw {
struct UpdateInfo;
}

namespace gf {
struct GF_OBJ_HANDLE;
class GfMenuCallContext;
} // namespace gf

namespace btl {

class BattleCharacter;

class UIManager : public mm::mtl::PtrSingleton<UIManager> {
public:
  enum INPUT_TYPE {
    INPUT_TYPE_ARTS_PALETTE,
    INPUT_TYPE_BLADE_CHANGE,
    INPUT_TYPE_SPECIAL_GAUGE,
    INPUT_TYPE_REVERSE_PALETTE_0,
    INPUT_TYPE_REVERSE_PALETTE_1,
    INPUT_TYPE_REVERSE_PALETTE_2,
    INPUT_TYPE_REVERSE_PALETTE_3,
  };

  ~UIManager();
  void Initialize();
  static void Destroy();
  void Finalize();
  static void PreUpdate(const fw::UpdateInfo &updateInfo);
  void PreUpdateProc(const fw::UpdateInfo &updateInfo);
  static void Update(const fw::UpdateInfo &updateInfo);
  void UpdateProc(const fw::UpdateInfo &updateInfo);
  void UpdateRescueUI();
  void UpdateTutorial(const fw::UpdateInfo &updateInfo);
  void ExitElementalComboDirectionUI(u32 id);
  void SetKakuseiData(bool isEnableKakusei, bool isKakusei, f32 kakuseiRestTimeRatio);
  void RegisterRescueUI(gf::GF_OBJ_HANDLE *handle);
  void DispChainUI(gf::GF_OBJ_HANDLE *handle);
  void DispElementalEffectUI(gf::GF_OBJ_HANDLE *handle, int caption);
  void NotifyInput(INPUT_TYPE type, int value);
  void NotifyMapChange();
  void DispUniteComboUI(const mm::Vec3 &position, int attribute, int combo);
  void DispSystemMessageUI(const BattleCharacter *character, int message, bool flag);
  void RegisterTutorial(u32 tutorial, f32 time, bool isRequest);
  u32 StartElementalComboDirectionUI(int attribute);

  gf::GfMenuCallContext *unknown08; // Inferred role: element effect context; original member name unknown.
  u32 unknown10;                    // Inferred role: element effect id; original member name unknown.
  u8 unknown14;                     // Inferred role: element effect attribute; original member name unknown.
  bool unknown15;                   // Inferred role: element effect canceled; original member name unknown.
  u8 _16[0x18 - 0x16];
  f32 unknown18;  // Inferred role: kakusei rest time ratio; original member name unknown.
  bool unknown1c; // Inferred role: enable kakusei; original member name unknown.
  bool unknown1d; // Inferred role: kakusei; original member name unknown.
  u8 _1e[0x20 - 0x1e];
  gf::GF_OBJ_HANDLE *unknown20; // Inferred role: rescue target; original member name unknown.
  bool unknown28;               // Inferred role: rescue window opened; original member name unknown.
  u8 _29[0x30 - 0x29];
  u32 unknown30; // Inferred role: pending tutorial bit field; original member name unknown.
  f32 unknown34; // Inferred role: tutorial display delay; original member name unknown.
  u32 unknown38; // Inferred role: element effect sequence id; original member name unknown.
  u8 _3c[0x44 - 0x3c];
  u16 : 3;
  u16 unknown44_3 : 1; // Inferred role: push reverse palette 0; original member name unknown.
  u16 unknown44_4 : 1; // Inferred role: push reverse palette 1; original member name unknown.
  u16 unknown44_5 : 1; // Inferred role: push reverse palette 2; original member name unknown.
  u16 unknown44_6 : 1; // Inferred role: push reverse palette 3; original member name unknown.
  u16 unknown44_7 : 1; // Inferred role: display battle UI; original member name unknown.
  u16 : 1;
  u16 unknown45_1 : 1; // Role and original member name unknown.
  u16 unknown45_2 : 1; // Role and original member name unknown.
  u16 : 5;
};

static_assert(offsetof(UIManager, unknown08) == 0x08, "");
static_assert(offsetof(UIManager, unknown15) == 0x15, "");
static_assert(offsetof(UIManager, unknown18) == 0x18, "");
static_assert(offsetof(UIManager, unknown1c) == 0x1c, "");
static_assert(offsetof(UIManager, unknown20) == 0x20, "");
static_assert(offsetof(UIManager, unknown28) == 0x28, "");
static_assert(offsetof(UIManager, unknown30) == 0x30, "");
static_assert(offsetof(UIManager, unknown34) == 0x34, "");
static_assert(offsetof(UIManager, unknown38) == 0x38, "");

} // namespace btl
