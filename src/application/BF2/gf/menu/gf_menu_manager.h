#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
}

namespace mm {
struct Col4;
}

namespace gf {

struct GfSetupParam;
struct SDataOption;

class GfMenuManager : public mm::mtl::PtrSingleton<GfMenuManager> {
public:
  static void build(const GfSetupParam &param);
  static void destroy();
  static bool isInitialized();
  static void update(const fw::UpdateInfo &info);
  static void initOptionData(SDataOption &option);
  static void setupGame();
  static bool isFading(u32 fade);
  static void getFadeColor(u32 fade, mm::Col4 &color);
  static void openCommonWindow(u16 window);
  static void closeCommonWindow();
  static bool isOpenCommonWindow();
  static void openPreciousWindow(u16 item);
  static bool isOpenPreciousWindow();
  static void openChapterTelop(u8 chapter);
  static void openChapterEndTelop(u8 chapter);
  static bool isOpenChapterTelop();
  static void openZoneTelop(u16 zone);
  static bool isOpenZoneTelop();
  static void openDummyTutorial(u8 tutorial);
  static bool isOpenDummyTutorial();
  static bool isEnableQuestOpen();
  void postUpdate(const fw::UpdateInfo &info);
  static bool isOpenFullScreen();
  static void openFullScreen(u32 screen, bool isFadeOut, bool isFadeIn);
  static void openMenu(u32 menu);
  static void openNameSelect();
  static bool isOpenNameSelect();
  static void openOpeningTelop();
  static void closeOpeningTelop();
  static void openStaffroll();
  static void closeStaffroll();
  static void setMainmenuOpenMap();
  static void setMainmenuOpenSystem();
  static void closeFullScreen(bool isFadeOut, bool isFadeIn);
  static void openSave();
};

} // namespace gf
