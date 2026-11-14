#pragma once
#include "gf/menu/gf_menu_bdat.h"
#include "gf/menu/gf_menu_object.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"
#include <stddef.h>

namespace gf {

struct GF_OBJ_HANDLE;
class GfMenuCallContext;

class GfMenuObjTargetInfo : public GfMenuObject {
public:
  class EnemyListener : public ui::UIObjectListener {
  public:
    EnemyListener(GfMenuObjTargetInfo *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];            // Actively zero-initialized unknown byte range, NOT padding; original name/role unknown.
    GfMenuObjTargetInfo *unknown20; // Inferred role: owner; original member name unknown.
  };

  class OtherListener : public ui::UIObjectListener {
  public:
    OtherListener(GfMenuObjTargetInfo *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];            // Actively zero-initialized unknown byte range, NOT padding; original name/role unknown.
    GfMenuObjTargetInfo *unknown20; // Inferred role: owner; original member name unknown.
  };

  class SymbolListener : public ui::UIObjectListener {
  public:
    SymbolListener(GfMenuObjTargetInfo *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];            // Actively zero-initialized unknown byte range, NOT padding; original name/role unknown.
    GfMenuObjTargetInfo *unknown20; // Inferred role: owner; original member name unknown.
  };

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

  // Layout from GfComBehaviorEnemy::createMenuObj (1.0.0: 0x710051701c), which builds it on the stack before openEnemy; the 0x30
  // byte size is the one of its stack slot (the bytes after 0x28 are never written there).
  struct OpenEnemyParam {
    GF_OBJ_HANDLE *unknown00; // Inferred role: enemy object; original member name unknown.
    u8 _08[0x10 - 0x08];
    MenuOffset unknown10; // Inferred role: offset; original member name unknown.
    u8 _28[0x30 - 0x28];
  };

  // Layout from openOther (1.0.0: 0x71004dc238), which builds it on the stack from its OpenOtherParam before openSymbol; the 0x50 byte
  // size is the one of its stack slot.
  struct OpenSymbolParam {
    GF_OBJ_HANDLE *unknown00; // Inferred role: gimmick object; original member name unknown.
    u8 _08[0x10 - 0x08];
    MenuOffset unknown10; // Inferred role: offset; original member name unknown.
    u8 _28[0x30 - 0x28];
    u8 *unknown30; // Inferred role: bdat of the gimmick names; original member name unknown.
    u32 unknown38; // Inferred role: name id; original member name unknown.
    u8 *unknown40; // Inferred role: bdat of the point names; original member name unknown.
    u32 unknown48; // Inferred role: point name id; original member name unknown.
    u32 unknown4c; // Inferred role: icon image index; original member name unknown.
  };

  GfMenuObjTargetInfo(u32 handle);
  ~GfMenuObjTargetInfo() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  static void close(GfMenuCallContext *context);
  static void openOther(GfMenuCallContext *context, const OpenOtherParam &param);
  static void openEnemy(GfMenuCallContext *context, const OpenEnemyParam &param);
  static void openSymbol(GfMenuCallContext *context, const OpenSymbolParam &param);
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
static_assert(offsetof(GfMenuObjTargetInfo::OpenEnemyParam, unknown10) == 0x10, "");
static_assert(sizeof(GfMenuObjTargetInfo::OpenEnemyParam) == 0x30, "");
static_assert(offsetof(GfMenuObjTargetInfo::OpenSymbolParam, unknown10) == 0x10, "");
static_assert(offsetof(GfMenuObjTargetInfo::OpenSymbolParam, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjTargetInfo::OpenSymbolParam, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjTargetInfo::OpenSymbolParam, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjTargetInfo::OpenSymbolParam, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuObjTargetInfo::OpenSymbolParam, unknown4c) == 0x4c, "");
static_assert(sizeof(GfMenuObjTargetInfo::OpenSymbolParam) == 0x50, "");
static_assert(offsetof(GfMenuObjTargetInfo::EnemyListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjTargetInfo::EnemyListener) == 0x28, "");
static_assert(offsetof(GfMenuObjTargetInfo::OtherListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjTargetInfo::OtherListener) == 0x28, "");
static_assert(offsetof(GfMenuObjTargetInfo::SymbolListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjTargetInfo::SymbolListener) == 0x28, "");

} // namespace gf
