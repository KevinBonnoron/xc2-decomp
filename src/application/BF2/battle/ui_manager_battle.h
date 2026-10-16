#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"
#include <stddef.h>

namespace fw {
struct UpdateInfo;
}

namespace gf {
struct GF_OBJ_HANDLE;
}

namespace btl {

class UIManager : public mm::mtl::PtrSingleton<UIManager> {
public:
  ~UIManager();
  void Initialize();
  static void Destroy();
  void Finalize();
  static void PreUpdate(const fw::UpdateInfo &updateInfo);
  void PreUpdateProc(const fw::UpdateInfo &updateInfo);
  static void Update(const fw::UpdateInfo &updateInfo);
  void UpdateProc(const fw::UpdateInfo &updateInfo);
  void SetKakuseiData(bool isEnableKakusei, bool isKakusei, f32 kakuseiRestTimeRatio);
  void RegisterRescueUI(gf::GF_OBJ_HANDLE *handle);

  u8 _08[0x18 - 0x08];
  f32 kakuseiRestTimeRatio;
  bool isEnableKakusei;
  bool isKakusei;
  u8 _1e[0x20 - 0x1e];
  gf::GF_OBJ_HANDLE *rescueTarget;
  u8 _28[0x44 - 0x28];
  u16 : 7;
  u16 isDispBattleUI : 1;
  u16 : 8;
};

static_assert(offsetof(UIManager, kakuseiRestTimeRatio) == 0x18, "");
static_assert(offsetof(UIManager, isEnableKakusei) == 0x1c, "");
static_assert(offsetof(UIManager, rescueTarget) == 0x20, "");

} // namespace btl
