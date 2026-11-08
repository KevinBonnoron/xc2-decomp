#pragma once
#include "gf/menu/gf_menu_bdat.h"
#include "gf/menu/gf_menu_object.h"
#include "types.h"
#include <stddef.h>

namespace gf {

struct GF_OBJ_HANDLE;
class GfMenuCallContext;

class GfMenuObjTargetInfo : public GfMenuObject {
public:
  // Layout from GfComBehaviorGmk::createMenuObj (1.0.0: 0x710052ab0c), which builds it on the stack before openOther; the 0x60 byte
  // size is the one of its stack slot (the bytes after 0x54 are never written there).
  struct OpenOtherParam {
    OpenOtherParam() : unknown38(0), unknown3c(false), unknown40(0), unknown48(nullptr), unknown50(0) {}

    GF_OBJ_HANDLE *unknown00; // Inferred role: gimmick object; original member name unknown.
    u8 _08[0x10 - 0x08];
    MenuOffset unknown10; // Inferred role: offset; original member name unknown.
    u8 _28[0x30 - 0x28];
    u8 *unknown30;  // Inferred role: bdat of the gimmick names; original member name unknown.
    u32 unknown38;  // Inferred role: name id; original member name unknown.
    bool unknown3c; // Inferred role: shows the name; original member name unknown.
    u32 unknown40;  // Inferred role: kind of the display, 0 salvage point, 1 kizuna talk, 2 collection; original member name unknown.
    u8 *unknown48;  // Inferred role: bdat of the salvage point names; original member name unknown.
    u32 unknown50;  // Inferred role: salvage point name id; original member name unknown.
    u8 _54[0x60 - 0x54];
  };

  GfMenuObjTargetInfo(u32 handle);
  ~GfMenuObjTargetInfo() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  static void close(GfMenuCallContext *context);
  static void openOther(GfMenuCallContext *context, const OpenOtherParam &param);
  static void dispAllSymbol(bool disp);
  static void dispAllOther(bool disp);
  static void dispAllEnemy(bool disp);
  static void disp(bool disp);
  static void startOpen(u32 handle, u32 object, int param0, int param1);
};

static_assert(offsetof(GfMenuObjTargetInfo::OpenOtherParam, unknown10) == 0x10, "");
static_assert(offsetof(GfMenuObjTargetInfo::OpenOtherParam, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjTargetInfo::OpenOtherParam, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjTargetInfo::OpenOtherParam, unknown3c) == 0x3c, "");
static_assert(offsetof(GfMenuObjTargetInfo::OpenOtherParam, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjTargetInfo::OpenOtherParam, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuObjTargetInfo::OpenOtherParam, unknown50) == 0x50, "");
static_assert(sizeof(GfMenuObjTargetInfo::OpenOtherParam) == 0x60, "");

} // namespace gf
