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
  static bool isOpenCommonWindow();
  static bool isEnableQuestOpen();
  static bool isOpenFullScreen();
};

} // namespace gf
