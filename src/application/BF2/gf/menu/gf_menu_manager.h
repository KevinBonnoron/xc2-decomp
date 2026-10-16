#pragma once
#include "types.h"

namespace mm {
struct Col4;
}

namespace gf {

struct SDataOption;

class GfMenuManager {
public:
  static void initOptionData(SDataOption &option);
  static void setupGame();
  static bool isFading(u32 fade);
  static void getFadeColor(u32 fade, mm::Col4 &color);
  static void openCommonWindow(u16 window);
  static void closeCommonWindow();
  static bool isOpenCommonWindow();
  static bool isEnableQuestOpen();
  static bool isOpenFullScreen();
  static void openNameSelect();
  static bool isOpenNameSelect();
  static void openOpeningTelop();
  static void closeOpeningTelop();
  static void openStaffroll();
  static void closeStaffroll();
};

} // namespace gf
