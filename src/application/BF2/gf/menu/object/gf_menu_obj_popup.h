#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "types.h"

namespace gf {

class GfMenuObjPopup : public GfMenuObject {
public:
  // Inferred role: kind of popup (1 arts, 2 pouch, 3 idea, 4 achievement, 5 affinity, 6 develop, 7 mercenary add, 8 mercenary return,
  // 9 quest, 10 crystal); original enum and enumerator names unknown.
  enum unknown005 {
    unknown005_1 = 1,
    unknown005_2 = 2,
    unknown005_3 = 3,
    unknown005_4 = 4,
    unknown005_5 = 5,
    unknown005_6 = 6,
    unknown005_7 = 7,
    unknown005_8 = 8,
    unknown005_9 = 9,
    unknown005_10 = 10,
  };

  // Layout from SCOM_POPUP::SCOM_POPUP (0x71005d1208), which copies it in two 8-byte moves, and the SCOM_POPUP::create* functions.
  struct OpenParam {
    unknown005 unknown00; // Inferred role: kind of popup; original member name unknown.
    u32 unknown04;        // Inferred role: first value, depends on the kind; original member name unknown.
    u32 unknown08;        // Inferred role: second value, depends on the kind; original member name unknown.
    u32 unknown0c;        // Inferred role: third value, depends on the kind; original member name unknown.
  };

  static void open(const OpenParam &param);
  static void pausePickup();
  static void continuePickup(u32 type);
  static void sendEvent(u32 handle, u32 type, u32 param);
  static int setFadeIn(u32 handle, u32 type);
  static int setFadeOut(u32 handle, u32 type);
  void initialize() override;
  void finalize() override;
  void update() override;
  static void closeAll();

  u8 _24[0x60 - 0x24];
  GfMenuSequence<GfMenuObjPopup, 8> unknown60; // Inferred role: popup steps; original member name unknown.
};

static_assert(offsetof(GfMenuObjPopup::OpenParam, unknown04) == 0x04, "");
static_assert(offsetof(GfMenuObjPopup::OpenParam, unknown08) == 0x08, "");
static_assert(offsetof(GfMenuObjPopup::OpenParam, unknown0c) == 0x0c, "");
static_assert(sizeof(GfMenuObjPopup::OpenParam) == 0x10, "");
static_assert(offsetof(GfMenuObjPopup, unknown60) == 0x60, "");
static_assert(sizeof(GfMenuObjPopup) == 0x2f0, "");

} // namespace gf
