#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuCallContext;
struct MenuCommonWindowParam;

class GfMenuObjCommonText : public GfMenuObject {
public:
  void initialize() override;
  void finalize() override;
  void update() override;
  struct OpenKizunaParam {
    const u8 *unknown00; // Inferred role: bdat; original member name unknown.
    u32 unknown08;       // Inferred role: text id; original member name unknown.
    u32 unknown0c;       // Inferred role: condition; original member name unknown.
  };

  static void close();
  static void open(GfMenuCallContext *context, const MenuCommonWindowParam &param);
  static void open(GfMenuCallContext *context, u32 window, u32 param);
  static void openItem(GfMenuCallContext *context, u32 type, u32 item);
  static void openKizunaDialog(GfMenuCallContext *context, const OpenKizunaParam &param);
};

} // namespace gf
