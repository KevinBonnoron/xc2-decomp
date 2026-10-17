#pragma once
#include <stddef.h>

#include "mm_mtl/delegate.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace ui {
struct EventData;
} // namespace ui

namespace gf {

struct GfSetupParam;

class GfMenuHUD : public mm::mtl::PtrSingleton<GfMenuHUD> {
public:
  static const u32 LAYER_MAX = 8;

  GfMenuHUD(const GfSetupParam &param);
  void initialize(const GfSetupParam &param);
  ~GfMenuHUD() override;
  static bool isDisp();
  static void build(const GfSetupParam &param);
  static void destroy();
  void finalize();
  static bool isInitialized();
  static void postUpdate(const fw::UpdateInfo &info);
  void reciveUIEvent(const ui::EventData &event, u32 handle);
  static void changeScene(u32 scene);
  void sceneChangeStart();
  static u32 getSceneID();
  void systemStart();
  void sceneWaitChange();
  void sceneUpdateField();
  void sceneUpdateBattle();
  void sceneUpdateEvent();
  void sceneUpdateFullscreen();
  void systemWait();
  void systemUpdate();

  bool initialized;
  u32 sceneID;
  u32 nextSceneID;
  mm::mtl::FixedVector<u32, LAYER_MAX> layers;
  mm::mtl::Delegate<void()> systemUpdater;
  mm::mtl::Delegate<void()> sceneUpdater;
};

static_assert(offsetof(GfMenuHUD, initialized) == 0x08, "");
static_assert(offsetof(GfMenuHUD, sceneID) == 0x0c, "");
static_assert(offsetof(GfMenuHUD, nextSceneID) == 0x10, "");
static_assert(offsetof(GfMenuHUD, layers) == 0x18, "");
static_assert(offsetof(GfMenuHUD, systemUpdater) == 0x40, "");
static_assert(offsetof(GfMenuHUD, sceneUpdater) == 0x60, "");
static_assert(sizeof(GfMenuHUD) == 0x80, "");

} // namespace gf
