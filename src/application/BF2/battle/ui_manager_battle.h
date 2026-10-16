#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"
#include <stddef.h>

namespace fw {
struct UpdateInfo;
}

namespace gf {
struct GF_OBJ_HANDLE;
class GfMenuCallContext;
} // namespace gf

namespace btl {

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
  void ExitElementalComboDirectionUI(u32 id);
  void SetKakuseiData(bool isEnableKakusei, bool isKakusei, f32 kakuseiRestTimeRatio);
  void RegisterRescueUI(gf::GF_OBJ_HANDLE *handle);
  void DispChainUI(gf::GF_OBJ_HANDLE *handle);
  void NotifyInput(INPUT_TYPE type, int value);

  gf::GfMenuCallContext *elementEffectContext;
  u32 elementEffectId;
  u8 elementEffectAttribute;
  bool isElementEffectCanceled;
  u8 _16[0x18 - 0x16];
  f32 kakuseiRestTimeRatio;
  bool isEnableKakusei;
  bool isKakusei;
  u8 _1e[0x20 - 0x1e];
  gf::GF_OBJ_HANDLE *rescueTarget;
  u8 _28[0x44 - 0x28];
  u16 : 3;
  u16 isPushReversePalette0 : 1;
  u16 isPushReversePalette1 : 1;
  u16 isPushReversePalette2 : 1;
  u16 isPushReversePalette3 : 1;
  u16 isDispBattleUI : 1;
  u16 : 8;
};

static_assert(offsetof(UIManager, elementEffectContext) == 0x08, "");
static_assert(offsetof(UIManager, isElementEffectCanceled) == 0x15, "");
static_assert(offsetof(UIManager, kakuseiRestTimeRatio) == 0x18, "");
static_assert(offsetof(UIManager, isEnableKakusei) == 0x1c, "");
static_assert(offsetof(UIManager, rescueTarget) == 0x20, "");

} // namespace btl
