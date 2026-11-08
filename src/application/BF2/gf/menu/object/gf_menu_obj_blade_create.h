#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "types.h"
#include "ui/list/ui_list_info.h"

namespace ui {
class UIListInfoBase;
} // namespace ui

namespace gf {

class GfMenuCallContext;
class GfMenuModelView;

class GfMenuObjBladeCreate : public GfMenuObject {
public:
  struct OpenParam {
    u32 unknown00; // Inferred role: event; original member name unknown.
  };

  struct PageContext {
    int unknown00; // Inferred role: current page; original member name unknown.
    int unknown04; // Inferred role: previous page; original member name unknown.
    u8 _08[0x28 - 0x08];
    u32 unknown28;  // Inferred role: created blade; original member name unknown.
    bool unknown2c; // Inferred role: ideagram page skipped; original member name unknown.
    u8 _2d[0x38 - 0x2d];
    ui::UIListInfoBase *unknown38;  // Inferred role: list released when the result is full; original member name unknown.
    ui::UIListInfo<u32> *unknown40; // Inferred role: driver list; original member name unknown.
    u8 _48[0xac8 - 0x48];
    GfMenuModelView *unknownac8; // Inferred role: model view; original member name unknown.
  };

  static void registOpenParam(const OpenParam &param);
  void initialize() override;
  void finalize() override;
  static void openCreatedBladeName(GfMenuCallContext *context);
  void update() override;
  u32 getPageObject(u32 handle, u32 page, bool isSibling);
  static u32 getDriverCameraIndex(u32 driver);
  void nextPage(u32 handle, PageContext *context, bool isSibling);
  void changePage(u32 handle, PageContext *context, u32 page, bool isSibling, bool isReturn);
  void returnPage(u32 handle, PageContext *context, bool isSibling);
  void setGuideText(u32 id);
  void stopAllSound();
  bool seqStart();
  bool seqWaitLoading();
  bool seqEnd();
  bool seqSave();
  bool seqSaveWait();
  bool seqSetupDriverObj();
  bool seqResultStart();
  bool seqResultConfirm();
  bool seqResultBladeFull();
  bool seqResultEnd();
  bool seqCreateStartSE();
  bool seqCreatePlayJingle();
  bool seqCreatePlayBgmAfter();
  bool seqCreateWaitEvent();
  bool seqCreateSetup();
  bool seqCreateStartDriver();
  bool seqCreateWaitDriver();
  bool seqCreateWaitFade();
  bool seqCreateBuildBlade();
  bool isValidCrystal(u32 item);
  u32 getInvalidCrystalMsgID(u32 item);
  void dispGuideText(bool isDisp);

  u8 _24[0x28 - 0x24];
  PageContext unknown28;                               // Inferred role: page state; original member name unknown.
  GfMenuSequence<GfMenuObjBladeCreate, 20> unknownaf8; // Inferred role: creation steps; original member name unknown.
  bool *unknown1118;                                   // Inferred role: event finished flag; original member name unknown.
  bool unknown1120;                                    // Inferred role: result shown flag; original member name unknown.
  u8 _1121[0x1148 - 0x1121];
  int unknown1148; // Inferred role: creation effect step; original member name unknown.
  u8 _114c[0x11b0 - 0x114c];
  u32 unknown11b0; // Inferred role: save request; original member name unknown.
  u8 _11b4[0x11c0 - 0x11b4];
  u32 unknown11c0;    // Inferred role: bgm handle; original member name unknown.
  u32 unknown11c4[3]; // Inferred role: sound effect handles; original member name unknown.
};

static_assert(offsetof(GfMenuObjBladeCreate::PageContext, unknown04) == 0x04, "");
static_assert(offsetof(GfMenuObjBladeCreate::PageContext, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjBladeCreate::PageContext, unknown2c) == 0x2c, "");
static_assert(offsetof(GfMenuObjBladeCreate::PageContext, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjBladeCreate::PageContext, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjBladeCreate::PageContext, unknownac8) == 0xac8, "");
static_assert(sizeof(GfMenuObjBladeCreate::PageContext) == 0xad0, "");
static_assert(offsetof(GfMenuObjBladeCreate, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjBladeCreate, unknownaf8) == 0xaf8, "");
static_assert(offsetof(GfMenuObjBladeCreate, unknown1118) == 0x1118, "");
static_assert(offsetof(GfMenuObjBladeCreate, unknown1120) == 0x1120, "");
static_assert(offsetof(GfMenuObjBladeCreate, unknown11b0) == 0x11b0, "");
static_assert(offsetof(GfMenuObjBladeCreate, unknown1148) == 0x1148, "");
static_assert(offsetof(GfMenuObjBladeCreate, unknown11c0) == 0x11c0, "");
static_assert(offsetof(GfMenuObjBladeCreate, unknown11c4) == 0x11c4, "");
static_assert(sizeof(GfMenuObjBladeCreate) == 0x11d0, "");

} // namespace gf
