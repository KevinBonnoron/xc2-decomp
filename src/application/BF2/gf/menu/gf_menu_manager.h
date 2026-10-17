#pragma once
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
  static f32 getUpdateDT();
  static GF_OBJ_HANDLE *getTargetObjHandle();
  static GF_OBJ_HANDLE *getAccessObjHandle();
  static bool isTargetChanged();
  static bool isAccessChanged();
  static u32 getCurCameraType();
  static bool isBattleState(u32 state);
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
  static bool isOpenDummyTutorial();
  static void setEnableQuestOpen(bool isEnable);
  static bool isEnableQuestOpen();
  static REGION getRegion();
  static bool isRegionUS();
  void postUpdate(const fw::UpdateInfo &info);
  static bool isOpenFullScreen();
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
  bool initialized;
  u8 _4091[0x40b8 - 0x4091];
  GF_OBJ_HANDLE *targetObj;
  GF_OBJ_HANDLE *accessObj;
  bool isTargetObjChanged;
  bool isAccessObjChanged;
  u8 _40ca[0x40cc - 0x40ca];
  u32 cameraType;
  GfMenuCallContext *callContext;
  int commonWindowResult;
  u8 _40dc[0x40f8 - 0x40dc];
  f32 updateDT;
  u8 _40fc[0x40fd - 0x40fc];
  bool isBtlModelViewOpen;
  bool isNameSelectOpen;
  bool isOpeningTelopOpen;
  u8 _4100[0x4101 - 0x4100];
  bool isQuestOpenEnable;
  REGION region;
  u8 _4108[0x4154 - 0x4108];
  u32 latestCommonWindow;
};

static_assert(offsetof(GfMenuManager, initialized) == 0x4090, "");
static_assert(offsetof(GfMenuManager, targetObj) == 0x40b8, "");
static_assert(offsetof(GfMenuManager, cameraType) == 0x40cc, "");
static_assert(offsetof(GfMenuManager, callContext) == 0x40d0, "");
static_assert(offsetof(GfMenuManager, updateDT) == 0x40f8, "");
static_assert(offsetof(GfMenuManager, isBtlModelViewOpen) == 0x40fd, "");
static_assert(offsetof(GfMenuManager, region) == 0x4104, "");
static_assert(offsetof(GfMenuManager, latestCommonWindow) == 0x4154, "");
static_assert(sizeof(GfMenuManager) == 0x4158, "");

} // namespace gf
