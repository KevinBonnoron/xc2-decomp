#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_bdat.h"
#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "gf/object/gf_obj_handle.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace ui {
class UICtrlCursorSelect;
class UIObjectAcc;
class UISelectObjList;
class UIStr;
} // namespace ui

namespace gf {

class GfMenuCallContext;
class GfMenuReferenceItem;
struct GF_OBJ_HANDLE;

class GfMenuObjBalloon : public GfMenuObject {
public:
  class AutoTalkListener : public ui::UIObjectListener {
  public:
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjBalloon *unknown20; // Inferred role: owner; original member name unknown.
  };

  class EvSelectListener : public ui::UIObjectListener {
  public:
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u32 unknown0c; // Inferred role: select object handle; original member name unknown.
    u8 _10[0x1c - 0x10];
    GfMenuObjBalloon *unknown20; // Inferred role: owner; original member name unknown.
  };

  GfMenuObjBalloon(u32 handle);
  ~GfMenuObjBalloon() override;
  static void setFeeling(ui::UIObjectAcc &acc, const ui::UIStr &string);
  static void resetFeeling(ui::UIObjectAcc &acc);
  void initialize() override;
  void finalize() override;
  void update() override;
  struct NextParam {
    u8 *unknown00; // Inferred role: bdat; original member name unknown.
    u32 unknown08; // Inferred role: text id; original member name unknown.
  };

  struct OpenParam : NextParam {
    OpenParam() : unknown10(nullptr), unknown18(0), unknown20(unknown020) {}

    u8 *unknown10;            // Inferred role: name bdat; original member name unknown.
    u32 unknown18;            // Inferred role: name id; original member name unknown.
    GF_OBJ_HANDLE *unknown20; // Inferred role: handle; original member name unknown.
    u8 _28[0x30 - 0x28];
    MenuOffset unknown30; // Inferred role: offset; original member name unknown.
    u8 _48[0x50 - 0x48];
  };

  struct OpenSelectParam : OpenParam {
    OpenSelectParam() : unknown50(nullptr) {}

    u8 *unknown50;                          // Inferred role: select bdat; original member name unknown.
    mm::mtl::FixedVector<u32, 2> unknown58; // Inferred role: select ids; original member name unknown.
    u8 _68[0x70 - 0x68];
  };

  struct OpenSelectBoxParam : NextParam {
    u8 *unknown10;                          // Inferred role: select bdat; original member name unknown.
    mm::mtl::FixedVector<u32, 3> unknown18; // Inferred role: select ids; original member name unknown.
  };

  struct OpenSelectMoneyParam {
    OpenSelectMoneyParam() : unknown00(nullptr), unknown08(0), unknown0c(0) {}

    u8 *unknown00;                          // Inferred role: bdat; original member name unknown.
    u32 unknown08;                          // Inferred role: text id; original member name unknown.
    u16 unknown0c;                          // Inferred role: message id; original member name unknown.
    mm::mtl::FixedVector<u32, 3> unknown10; // Inferred role: moneys; original member name unknown.
    mm::mtl::FixedVector<u16, 3> unknown28; // Inferred role: name ids; original member name unknown.
  };

  struct OpenGetItemParam {
    u32 unknown00; // Inferred role: item; original member name unknown.
  };

  static void openEvent(GfMenuCallContext *context, const OpenParam &param);
  static void openAutoTalk(GfMenuCallContext *context, const OpenParam &param);
  static void openEventSelect(GfMenuCallContext *context, const OpenSelectParam &param);
  static void close(GfMenuCallContext *context, bool isImmediate);
  static void nextEvent(GfMenuCallContext *context, const NextParam &param);
  static void openEventSelectBox(GfMenuCallContext *context, const OpenSelectBoxParam &param);
  static void openEventSelectMoney(GfMenuCallContext *context, const OpenSelectMoneyParam &param);
  static bool openGetItem(GfMenuCallContext *context, const OpenGetItemParam &param);
  static u32 openCommon(GfMenuCallContext *context, u32 call, GF_OBJ_HANDLE *handle, const MenuOffset &offset, u32 type, bool isAutoTalk);
  static void setup(u32 object, GF_OBJ_HANDLE *handle, const MenuOffset &offset, bool isUpdate, u32 type, bool isAutoTalk);
  static u32 getFeeling(const ui::UIStr &string);
  static int setupEvTalk(u32 handle, int text, int name);
  static void setupEvSelect(u32 handle, int title, int name);
  bool seqSave();
  bool seqSaveWait();

  u8 _24[0x28 - 0x24];
  ui::UICtrlCursorSelect *unknown28;                                            // Inferred role: cursor of the event select messages; original member name unknown.
  ui::UISelectObjList *unknown30;                                               // Inferred role: event select message objects; original member name unknown.
  ui::UISelectObjList *unknown38;                                               // Inferred role: select item objects; original member name unknown.
  ui::UISelectObjList *unknown40;                                               // Inferred role: select money item objects; original member name unknown.
  mm::mtl::FixedVector<u32, 4> unknown48;                                       // Inferred role: unused; original member name unknown.
  mm::mtl::FixedArray<mm::mtl::IntrusivePtr<GfMenuReferenceItem>, 3> unknown60; // Inferred role: select items; original member name unknown.
  GfMenuSequence<GfMenuObjBalloon, 4> unknown78;                                // Inferred role: queued steps; original member name unknown.
  bool unknown1d8;                                                              // Role and original member name unknown, cleared by the constructor.
  u8 _1d9[0x1dc - 0x1d9];
  u32 unknown1dc; // Inferred role: save request, 0xffffffff when none; original member name unknown.
};

static_assert(offsetof(GfMenuObjBalloon, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjBalloon, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjBalloon, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjBalloon, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjBalloon, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuObjBalloon, unknown60) == 0x60, "");
static_assert(offsetof(GfMenuObjBalloon, unknown78) == 0x78, "");
static_assert(offsetof(GfMenuObjBalloon, unknown1d8) == 0x1d8, "");
static_assert(offsetof(GfMenuObjBalloon, unknown1dc) == 0x1dc, "");
static_assert(sizeof(GfMenuObjBalloon) == 0x1e0, "");

static_assert(offsetof(GfMenuObjBalloon::OpenParam, unknown10) == 0x10, "");
static_assert(offsetof(GfMenuObjBalloon::OpenParam, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjBalloon::OpenParam, unknown30) == 0x30, "");
static_assert(sizeof(GfMenuObjBalloon::OpenParam) == 0x50, "");
static_assert(offsetof(GfMenuObjBalloon::OpenSelectParam, unknown58) == 0x58, "");
static_assert(sizeof(GfMenuObjBalloon::OpenSelectParam) == 0x70, "");
static_assert(offsetof(GfMenuObjBalloon::OpenSelectBoxParam, unknown18) == 0x18, "");
static_assert(sizeof(GfMenuObjBalloon::OpenSelectBoxParam) == 0x30, "");
static_assert(offsetof(GfMenuObjBalloon::OpenSelectMoneyParam, unknown0c) == 0x0c, "");
static_assert(offsetof(GfMenuObjBalloon::OpenSelectMoneyParam, unknown28) == 0x28, "");
static_assert(sizeof(GfMenuObjBalloon::OpenSelectMoneyParam) == 0x38, "");
static_assert(offsetof(GfMenuObjBalloon::AutoTalkListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjBalloon::AutoTalkListener) == 0x28, "");
static_assert(offsetof(GfMenuObjBalloon::EvSelectListener, unknown0c) == 0x0c, "");
static_assert(offsetof(GfMenuObjBalloon::EvSelectListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjBalloon::EvSelectListener) == 0x28, "");

} // namespace gf
