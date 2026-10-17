#pragma once
#include "types.h"

namespace gf {

class GfMenuCallContext;
struct MenuCommonWindowParam;

class GfMenuObjCommonText {
public:
  struct OpenKizunaParam {
    const u8 *bdat;
    u32 textId;
    u32 condition;
  };

  static void close();
  static void open(GfMenuCallContext *context, const MenuCommonWindowParam &param);
  static void open(GfMenuCallContext *context, u32 window, u32 param);
  static void openItem(GfMenuCallContext *context, u32 type, u32 item);
  static void openKizunaDialog(GfMenuCallContext *context, const OpenKizunaParam &param);
};

} // namespace gf
