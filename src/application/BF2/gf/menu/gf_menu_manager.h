#pragma once
#include "mm_mtl/bitflag.h"
#include "mm_mtl/singleton.h"
#include "types.h"
#include <stddef.h>

namespace fw {
struct UpdateInfo;
}

namespace mm {
struct Col4;
}

namespace gf {

struct GF_OBJ_HANDLE;
struct GfSetupParam;
struct MenuCommonWindowParam;
struct QuestCompleteParam;
struct SDataOption;
class GfMenuCallContext;

class GfMenuManager : public mm::mtl::PtrSingleton<GfMenuManager> {
public:
  enum REGION {
    REGION_JP,
    REGION_US,
  };

  GfMenuManager(const GfSetupParam &param);
  static void build(const GfSetupParam &param);
  static void destroy();
  void finalize();
  static bool isInitialized();
  static bool isRegionJP();
  static void update(const fw::UpdateInfo &info);
  static void initOptionData(SDataOption &option);
  static void setupGame();
  static bool isFading(u32 fade);
  static void getFadeColor(u32 fade, mm::Col4 &color);
  static void applyGammaCorrectValue(f32 value);
  static void applyOptionData(const SDataOption &option);
  static f32 getUpdateDT();
  static GF_OBJ_HANDLE *getTargetObjHandle();
  static GF_OBJ_HANDLE *getAccessObjHandle();
  static bool isTargetChanged();
  static bool isAccessChanged();
  static u32 getCurCameraType();
  void gevCameraControl(u32 type);
  static bool isBattleState(u32 state);
  static void setBattleState(u32 state, bool isEnable);
  static bool isDispHud(int hud);
  static void setDispAll(bool isDisp);
  static void openCommonWindow(u16 window);
  static void openCommonWindow(const MenuCommonWindowParam &param);
  static void closeCommonWindow();
  static bool isOpenCommonWindow();
  static int getCommonWindowResult();
  static u32 getLatestCommonWinID();
  static void openPreciousWindow(u16 item);
  static bool isOpenPreciousWindow();
  static void openChapterTelop(u8 chapter);
  static void openChapterEndTelop(u8 chapter);
  static bool isOpenChapterTelop();
  static void openZoneTelop(u16 zone);
  static bool isOpenZoneTelop();
  static void openDummyTutorial(u8 tutorial);
  static u32 startTutorial(u32 tutorial);
  static bool isOpenDummyTutorial();
  static void setEnableQuestOpen(bool isEnable);
  static bool isEnableQuestOpen();
  static REGION getRegion();
  static bool isRegionUS();
  void postUpdate(const fw::UpdateInfo &info);
  void qevCompleteQuest(const QuestCompleteParam &param);
  static bool isOpenFullScreen();
  static bool isSwitchingFullScreen();
  static void changeHUDScene(u32 scene);
  static void openFullScreen(u32 screen, bool isFadeOut, bool isFadeIn);
  static void openMenu(u32 menu);
  static void openBladeCreateFromEvent(u32 event);
  static void openBtlModelView();
  static void closeBtlModelView();
  static bool isOpenBtlModelView();
  static void openNameSelect();
  static bool isOpenNameSelect();
  static void openOpeningTelop();
  static void closeOpeningTelop();
  static bool isOpenOpeningTelop();
  static void openStaffroll();
  static void closeStaffroll();
  static void setMainmenuOpenMap();
  static void setMainmenuOpenSystem();
  static void acceptAccess(GF_OBJ_HANDLE *handle);
  static void closeFullScreen(bool isFadeOut, bool isFadeIn);
  static void execMinimap(bool isExec);
  static bool isFieldHudInputEnable();
  static void openSave();

  u8 _08[0x4090 - 0x08];
  bool unknown4090; // Inferred role: initialized; original member name unknown.
  bool unknown4091; // Inferred role: finalized; original member name unknown.
  u8 _4092[0x40b8 - 0x4092];
  GF_OBJ_HANDLE *unknown40b8; // Inferred role: target object; original member name unknown.
  GF_OBJ_HANDLE *unknown40c0; // Inferred role: access object; original member name unknown.
  bool unknown40c8;           // Inferred role: target object changed; original member name unknown.
  bool unknown40c9;           // Inferred role: access object changed; original member name unknown.
  bool unknown40ca;           // Inferred role: battle state enable; original member name unknown.
  u8 _40cb[0x40cc - 0x40cb];
  u32 unknown40cc;                     // Inferred role: camera type; original member name unknown.
  GfMenuCallContext *unknown40d0;      // Inferred role: call context; original member name unknown.
  int unknown40d8;                     // Inferred role: common window result; original member name unknown.
  mm::mtl::unknown027<32> unknown40dc; // Inferred role: battle state; original member name unknown.
  mm::mtl::unknown027<32> unknown40e0; // Inferred role: previous battle state; original member name unknown.
  mm::mtl::unknown027<32> unknown40e4; // Inferred role: hud state; original member name unknown.
  mm::mtl::unknown027<32> unknown40e8; // Inferred role: previous hud state; original member name unknown.
  u8 _40ec[0x40f8 - 0x40ec];
  f32 unknown40f8; // Inferred role: update dt; original member name unknown.
  u8 _40fc[0x40fd - 0x40fc];
  bool unknown40fd;   // Inferred role: btl model view open; original member name unknown.
  bool unknown40fe;   // Inferred role: name select open; original member name unknown.
  bool unknown40ff;   // Inferred role: opening telop open; original member name unknown.
  bool unknown4100;   // Inferred role: display all; original member name unknown.
  bool unknown4101;   // Inferred role: quest open enable; original member name unknown.
  REGION unknown4104; // Inferred role: region; original member name unknown.
  u8 _4108[0x4154 - 0x4108];
  u32 unknown4154; // Inferred role: latest common window; original member name unknown.
};

static_assert(offsetof(GfMenuManager, unknown4090) == 0x4090, "");
static_assert(offsetof(GfMenuManager, unknown4091) == 0x4091, "");
static_assert(offsetof(GfMenuManager, unknown40b8) == 0x40b8, "");
static_assert(offsetof(GfMenuManager, unknown40ca) == 0x40ca, "");
static_assert(offsetof(GfMenuManager, unknown40cc) == 0x40cc, "");
static_assert(offsetof(GfMenuManager, unknown40d0) == 0x40d0, "");
static_assert(offsetof(GfMenuManager, unknown40dc) == 0x40dc, "");
static_assert(offsetof(GfMenuManager, unknown40e0) == 0x40e0, "");
static_assert(offsetof(GfMenuManager, unknown40e4) == 0x40e4, "");
static_assert(offsetof(GfMenuManager, unknown40e8) == 0x40e8, "");
static_assert(offsetof(GfMenuManager, unknown40f8) == 0x40f8, "");
static_assert(offsetof(GfMenuManager, unknown40fd) == 0x40fd, "");
static_assert(offsetof(GfMenuManager, unknown4100) == 0x4100, "");
static_assert(offsetof(GfMenuManager, unknown4104) == 0x4104, "");
static_assert(offsetof(GfMenuManager, unknown4154) == 0x4154, "");
static_assert(sizeof(GfMenuManager) == 0x4158, "");

} // namespace gf
