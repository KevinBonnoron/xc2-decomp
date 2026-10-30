#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_types.h"
#include "mm_mtl/delegate.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "types.h"
#include "ui/input/ui_input_switcher.h"

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace gf {

struct GfSetupParam;

class GfMenuFullScreen : public mm::mtl::PtrSingleton<GfMenuFullScreen> {
public:
  struct unknown001 {
    u16 unknown00; // Inferred role: ui layer id; original member name unknown.
    u8 _02[0x08 - 0x02];
    mm::mtl::FixedVector<u32, 8> unknown08; // Inferred role: terminated layers; original member name unknown.
    u32 unknown30;                          // Inferred role: layer object; original member name unknown.
    bool unknown34;                         // Inferred role: shadow; original member name unknown.
    u8 _35[0x38 - 0x35];
  };

  // Inferred role: layer parameter; original type name unknown.
  struct unknown003 {
    u32 unknown00;                // Inferred role: ui layer id; original member name unknown.
    GfMenuTypes::Param unknown08; // Inferred role: parameter; original member name unknown.
  };

  static const u32 LAYER_COUNT = 4;

  static bool isInitialized();
  static bool isOpen();
  static bool isDisp();
  static bool isSwitching();
  static void close(bool isFadeOut, bool isFadeIn);
  static void open(u32 layer, bool isFadeOut, bool isFadeIn);
  static void enableSwitching();
  static void disableSwitching();
  static void overrideFadeInFrame(u32 frame);
  static void overrideFadeOutFrame(u32 frame);
  static void overrideInputBorder(u32 border);
  static u32 getScreenID();
  static u32 getScreenLayerID(u32 screen);
  static void preloadScreenResource(u32 screen);
  static bool setInputObject(u32 layer, u32 object);
  static u32 getInputObject(u32 layer);
  static void enableInput(u32 layer);
  static void disableInput();
  static bool isActiveInput(u32 layer);
  static void registLayerParam(u32 layer, const GfMenuTypes::Param &param);
  static bool getLayerParam(u32 layer, GfMenuTypes::Param &param);
  static void removeLayerParam(u32 layer);
  static void registLayerObject(u32 layer, u32 object);
  static void setShadowLayer(u32 layer, bool shadow);
  static u16 getLayerGroup(u32 layer);
  static void destroy();
  static void postUpdate(const fw::UpdateInfo &info);
  void initialize(const GfSetupParam &param);
  void finalize();
  void createLayer(u16 index, u16 layer);
  void releaseLayer(u16 index);
  u32 convScreenIDToLayerID(u32 screen) const;
  void startProcess();
  void exitProcess(bool isReset);
  void terminateLayer(u16 index, bool isImmediate, bool isKeep);

  bool unknown08; // Inferred role: initialized; original member name unknown.
  u32 unknown0c;  // Inferred role: current screen; original member name unknown.
  u32 unknown10;  // Inferred role: requested screen; original member name unknown.
  u8 _14[0x18 - 0x14];
  unknown001 unknown18[LAYER_COUNT];              // Inferred role: layers; original member name unknown.
  bool unknownf8;                                 // Inferred role: unknown flag; original member name unknown.
  bool unknownf9;                                 // Inferred role: switching; original member name unknown.
  u32 unknownfc;                                  // Inferred role: fade in frame override; original member name unknown.
  u32 unknown100;                                 // Inferred role: fade out frame override; original member name unknown.
  u32 unknown104;                                 // Inferred role: input border override; original member name unknown.
  bool unknown108;                                // Inferred role: switching enabled; original member name unknown.
  bool unknown109;                                // Inferred role: fade out; original member name unknown.
  bool unknown10a;                                // Inferred role: fade in; original member name unknown.
  mm::mtl::Delegate<void()> unknown110;           // Inferred role: switching step; original member name unknown.
  u32 unknown130;                                 // Inferred role: target layer; original member name unknown.
  u16 unknown134;                                 // Inferred role: unknown; original member name unknown.
  mm::mtl::Delegate<void()> unknown138;           // Inferred role: sub layer step; original member name unknown.
  u32 unknown158;                                 // Inferred role: unknown; original member name unknown.
  u16 unknown15c;                                 // Inferred role: sub layer index; original member name unknown.
  ui::UIInputSwitcher unknown160;                 // Inferred role: input switcher; original member name unknown.
  mm::mtl::FixedVector<unknown003, 8> unknown188; // Inferred role: layer parameters; original member name unknown.
};

static_assert(offsetof(GfMenuFullScreen::unknown001, unknown08) == 0x08, "");
static_assert(offsetof(GfMenuFullScreen::unknown001, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuFullScreen::unknown001, unknown34) == 0x34, "");
static_assert(sizeof(GfMenuFullScreen::unknown001) == 0x38, "");
static_assert(sizeof(GfMenuFullScreen::unknown003) == 0x28, "");
static_assert(offsetof(GfMenuFullScreen, unknown08) == 0x08, "");
static_assert(offsetof(GfMenuFullScreen, unknown18) == 0x18, "");
static_assert(offsetof(GfMenuFullScreen, unknownf8) == 0xf8, "");
static_assert(offsetof(GfMenuFullScreen, unknown110) == 0x110, "");
static_assert(offsetof(GfMenuFullScreen, unknown130) == 0x130, "");
static_assert(offsetof(GfMenuFullScreen, unknown138) == 0x138, "");
static_assert(offsetof(GfMenuFullScreen, unknown15c) == 0x15c, "");
static_assert(offsetof(GfMenuFullScreen, unknown160) == 0x160, "");
static_assert(offsetof(GfMenuFullScreen, unknown188) == 0x188, "");
static_assert(sizeof(GfMenuFullScreen) == 0x2d0, "");

} // namespace gf
