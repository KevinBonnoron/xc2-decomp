#pragma once
#include <stddef.h>

#include "types.h"

namespace gf {
class GfMenuCallContext;
} // namespace gf

namespace tl {

class TitleMenu {
public:
  TitleMenu() : unknown00(0), unknown08(nullptr) {}

  gf::GfMenuCallContext *getMenuCallContext();
  void destroyMenuCallContext();
  void openTitle(bool isFadeOut);
  bool isOpenTitle() const;
  void setupTitle();
  bool hasResultSelect() const;
  int getResult() const;
  void closeTitle(bool isFadeOut, bool isFadeIn);
  bool isCloseTitle() const;
  bool isCloseOption() const;
  void openEventTheater();
  bool isOpenEventTheater() const;
  void setupEventTheater();
  bool hasResultEventTheater() const;
  bool isExitEventTheater() const;
  void openOption();
  bool isOpenOption() const;
  void setupOption();
  bool hasResultOption() const;
  bool isExitOption() const;
  void exitOption();
  u32 getPlayEventID() const;
  void exitEventTheater();
  void fadeoutEventTheater();
  void fadeinEventTheater();

  u32 unknown00;                    // Inferred role: result of the title menu, set from getResult; original member name unknown.
  gf::GfMenuCallContext *unknown08; // Inferred role: call context of the menu in use; original member name unknown.
};

static_assert(offsetof(TitleMenu, unknown08) == 0x08, "");
static_assert(sizeof(TitleMenu) == 0x10, "");

} // namespace tl
