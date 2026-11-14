#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"
#include "ui/list/ui_list_info.h"

namespace mm {
namespace mtl {
class ReferenceObject;
} // namespace mtl
} // namespace mm

namespace ui {
class UIListInfoBase;
class UISelectObjList;
} // namespace ui

namespace gf {

class GfMenuBladeCreateCamera;
class GfMenuCallContext;
class GfMenuItemList;
class GfMenuReferenceNumber;
struct GfSequentialPlaySignal;
class GfMenuModelView;

class GfMenuObjBladeCreate : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x20 - 0x0c];
    GfMenuObjBladeCreate *unknown20; // Inferred role: owner; original member name unknown.
  };

  struct OpenParam {
    u32 unknown00; // Inferred role: event; original member name unknown.
  };

  // Inferred role: entry of the idea list; original type name unknown.
  struct unknown005 {
    u8 _00[0x04 - 0x00];
    int unknown04; // Inferred role: idea bdat id; original member name unknown.
    s16 unknown08; // Inferred role: idea level; original member name unknown.
    u8 _0a[0x10 - 0x0a];
  };

  struct PageContext {
    u32 unknown00; // Inferred role: current page; original member name unknown.
    int unknown04; // Inferred role: previous page; original member name unknown.
    u8 _08[0x28 - 0x08];
    u32 unknown28;  // Inferred role: created blade; original member name unknown.
    bool unknown2c; // Inferred role: ideagram page skipped; original member name unknown.
    u8 _2d[0x30 - 0x2d];
    mm::mtl::ReferenceObject *unknown30;   // Inferred role: reference-counted object; type and original member name unknown.
    ui::UIListInfoBase *unknown38;         // Inferred role: list released when the result is full; original member name unknown.
    ui::UIListInfo<u32> *unknown40;        // Inferred role: driver list; original member name unknown.
    GfMenuItemList *unknown48;             // Inferred role: crystal list; original member name unknown.
    ui::UIListInfo<unknown005> *unknown50; // Inferred role: idea list; original member name unknown.
    u8 _58[0xac8 - 0x58];
    GfMenuModelView *unknownac8; // Inferred role: model view; original member name unknown.
  };

  class ResultListener : public ui::UIObjectListener {
  public:
    ResultListener(GfMenuObjBladeCreate *owner, PageContext *context) : _0c(), unknown20(owner), unknown28(context) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x20 - 0x0c];
    GfMenuObjBladeCreate *unknown20; // Inferred role: owner; original member name unknown.
    PageContext *unknown28;          // Inferred role: page state of the owner; original member name unknown.
  };

  class BoosterNumListener : public ui::UIObjectListener {
  public:
    BoosterNumListener(GfMenuObjBladeCreate *owner) : unknown0c(0), unknown10(0), _14(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    int unknown0c; // Inferred role: number select opened flag; original member name unknown.
    int unknown10; // Inferred role: number confirmed flag; original member name unknown.
    u8 _14[0x20 - 0x14];
    GfMenuObjBladeCreate *unknown20; // Inferred role: owner; original member name unknown.
  };

  class IdeagramListener : public ui::UIObjectListener {
  public:
    IdeagramListener(GfMenuObjBladeCreate *owner) : unknown0c(0), _10(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    int unknown0c; // Inferred role: opened flag; original member name unknown.
    u8 _10[0x20 - 0x10];
    GfMenuObjBladeCreate *unknown20; // Inferred role: owner; original member name unknown.
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
  void updateIdea(bool isSave);
  void refreshCrystalList();
  bool seqSetupCrystal();
  bool seqResultAppearBlade();
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
  bool seqCreateDriverObj();
  bool seqCreateWaitFade();
  bool seqCreateStart();
  bool seqCreateBuildBlade();
  bool seqCreateCtrlBlade();
  bool seqCreateWaitBlade();
  bool seqCreateStartEvent();
  bool isValidCrystal(u32 item);
  u32 getInvalidCrystalMsgID(u32 item);
  void dispGuideText(bool isDisp);

  u8 _24[0x28 - 0x24];
  PageContext unknown28;                               // Inferred role: page state; original member name unknown.
  GfMenuSequence<GfMenuObjBladeCreate, 20> unknownaf8; // Inferred role: creation steps; original member name unknown.
  GfSequentialPlaySignal *unknown1118;                 // Inferred role: event signal; original member name unknown.
  bool unknown1120;                                    // Inferred role: result shown flag; original member name unknown.
  u8 _1121[0x1128 - 0x1121];
  mm::mtl::FixedVector<u32, 4> unknown1128; // Inferred role: blades of the creation; original member name unknown.
  int unknown1140;                          // Inferred role: maximum number of blades; original member name unknown.
  u32 unknown1144;                          // Inferred role: step of the blade animation; original member name unknown.
  int unknown1148;                          // Inferred role: creation effect step; original member name unknown.
  int unknown114c;                          // Inferred role: vibration timer; original member name unknown.
  ui::UISelectObjList *unknown1150;         // Inferred role: crystal select object list; original member name unknown.
  u8 _1158[0x1174 - 0x1158];
  int unknown1174[4]; // Inferred role: idea levels added by the result; original member name unknown.
  u8 _1184[0x1188 - 0x1184];
  mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown1188; // Inferred role: idea level reference number; original member name unknown.
  GfMenuBladeCreateCamera *unknown1190;                     // Inferred role: camera of the pages; original member name unknown.
  u32 unknown1198;                                          // Inferred role: camera index of the pages; original member name unknown.
  f32 unknown119c;                                          // Inferred role: angle between two drivers of the driver select page; original member name unknown.
  int unknown11a0;                                          // Inferred role: first camera index of the driver; original member name unknown.
  u8 _11a4[0x11b0 - 0x11a4];
  u32 unknown11b0;  // Inferred role: save request; original member name unknown.
  bool unknown11b4; // Inferred role: opened from an event; original member name unknown.
  u8 _11b5[0x11b8 - 0x11b5];
  int unknown11b8;  // Inferred role: limited item of the event; original member name unknown.
  bool unknown11bc; // Inferred role: blade joins the party after the event; original member name unknown.
  u8 _11bd[0x11c0 - 0x11bd];
  u32 unknown11c0;    // Inferred role: bgm handle; original member name unknown.
  u32 unknown11c4[3]; // Inferred role: sound effect handles; original member name unknown.
};

static_assert(offsetof(GfMenuObjBladeCreate::PageContext, unknown04) == 0x04, "");
static_assert(sizeof(GfMenuObjBladeCreate::unknown005) == 0x10, "");
static_assert(offsetof(GfMenuObjBladeCreate::PageContext, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuObjBladeCreate, unknown1174) == 0x1174, "");
static_assert(offsetof(GfMenuObjBladeCreate, unknown1188) == 0x1188, "");
static_assert(offsetof(GfMenuObjBladeCreate, unknown1198) == 0x1198, "");
static_assert(offsetof(GfMenuObjBladeCreate, unknown11a0) == 0x11a0, "");
static_assert(offsetof(GfMenuObjBladeCreate::PageContext, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjBladeCreate::PageContext, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuObjBladeCreate::PageContext, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjBladeCreate::PageContext, unknown2c) == 0x2c, "");
static_assert(offsetof(GfMenuObjBladeCreate::PageContext, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjBladeCreate, unknown1190) == 0x1190, "");
static_assert(offsetof(GfMenuObjBladeCreate, unknown119c) == 0x119c, "");
static_assert(offsetof(GfMenuObjBladeCreate::PageContext, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjBladeCreate::PageContext, unknownac8) == 0xac8, "");
static_assert(sizeof(GfMenuObjBladeCreate::PageContext) == 0xad0, "");
static_assert(offsetof(GfMenuObjBladeCreate, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjBladeCreate, unknownaf8) == 0xaf8, "");
static_assert(offsetof(GfMenuObjBladeCreate, unknown1118) == 0x1118, "");
static_assert(offsetof(GfMenuObjBladeCreate, unknown1120) == 0x1120, "");
static_assert(offsetof(GfMenuObjBladeCreate, unknown11b0) == 0x11b0, "");
static_assert(offsetof(GfMenuObjBladeCreate, unknown1148) == 0x1148, "");
static_assert(offsetof(GfMenuObjBladeCreate, unknown1128) == 0x1128, "");
static_assert(offsetof(GfMenuObjBladeCreate, unknown1144) == 0x1144, "");
static_assert(offsetof(GfMenuObjBladeCreate, unknown114c) == 0x114c, "");
static_assert(offsetof(GfMenuObjBladeCreate, unknown1150) == 0x1150, "");
static_assert(offsetof(GfMenuObjBladeCreate, unknown11c0) == 0x11c0, "");
static_assert(offsetof(GfMenuObjBladeCreate, unknown11c4) == 0x11c4, "");
static_assert(sizeof(GfMenuObjBladeCreate) == 0x11d0, "");
static_assert(offsetof(GfMenuObjBladeCreate::unknown005, unknown08) == 0x08, "");
static_assert(offsetof(GfMenuObjBladeCreate::ResultListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjBladeCreate::ResultListener, unknown28) == 0x28, "");
static_assert(sizeof(GfMenuObjBladeCreate::ResultListener) == 0x30, "");
static_assert(offsetof(GfMenuObjBladeCreate::BoosterNumListener, unknown0c) == 0x0c, "");
static_assert(offsetof(GfMenuObjBladeCreate::BoosterNumListener, unknown10) == 0x10, "");
static_assert(offsetof(GfMenuObjBladeCreate::BoosterNumListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjBladeCreate::BoosterNumListener) == 0x28, "");
static_assert(offsetof(GfMenuObjBladeCreate::IdeagramListener, unknown0c) == 0x0c, "");
static_assert(offsetof(GfMenuObjBladeCreate::IdeagramListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjBladeCreate::IdeagramListener) == 0x28, "");

} // namespace gf
