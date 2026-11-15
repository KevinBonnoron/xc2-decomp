#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "mm_math/mm_rect.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace ui {
class UICtrlRadarGraph;
class UISelectObjList;
} // namespace ui

namespace gf {

class GfMenuCallContext;

class GfMenuObjBlDetail : public GfMenuObject {
public:
  struct CreateParam {
    CreateParam() : unknown00(0x3ff), unknown04(0), unknown10(false), unknown14(0), unknown18(-1), unknown1c(0.3f), unknown20(0) {}

    u32 unknown00;           // Inferred role: mask of the pages to create; original member name unknown.
    u32 unknown04;           // Inferred role: first page; original member name unknown.
    mm::Rect<s16> unknown08; // Inferred role: layout rect; original member name unknown.
    bool unknown10;          // Role and original member name unknown.
    u32 unknown14;           // Inferred role: parent object handle, 0 for the detail layout itself; original member name unknown.
    int unknown18;           // Role and original member name unknown.
    f32 unknown1c;           // Inferred role: time of the open and close controls; original member name unknown.
    int unknown20;           // Inferred role: kind of the open and close controls, 0 fade, 1 from the left, 2 from the right; original member name unknown.
  };

  // Inferred role: pages of a created detail; original type name unknown.
  struct unknown001 {
    unknown001() : unknown00(false), unknown38(nullptr), unknown40(nullptr), unknown48(false), unknown50(nullptr) {}

    bool unknown00;                                         // Inferred role: created flag; original member name unknown.
    CreateParam unknown04;                                  // Inferred role: param of the detail; original member name unknown.
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown28; // Inferred role: current page; original member name unknown.
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown30; // Inferred role: number of pages; original member name unknown.
    ui::UISelectObjList *unknown38;                         // Inferred role: page layouts; original member name unknown.
    ui::UISelectObjList *unknown40;                         // Inferred role: page index layouts; original member name unknown.
    bool unknown48;                                         // Inferred role: page loop flag; original member name unknown.
    ui::UICtrlRadarGraph *unknown50;                        // Inferred role: radar graph of the status page; original member name unknown.
  };

  class DetailListener : public ui::UIObjectListener {
  public:
    DetailListener() {
      unknown0c = unknown142();
      unknown20 = nullptr;
    }
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    unknown142 unknown0c;         // Inferred role: work values; original member name unknown.
    GfMenuObjBlDetail *unknown20; // Inferred role: owner, always null; original member name unknown.
    unknown001 unknown28;         // Inferred role: pages; original member name unknown.
  };

  GfMenuObjBlDetail(u32 handle);
  ~GfMenuObjBlDetail() override;
  void initialize() override;
  void finalize() override;
  static void create(GfMenuCallContext *context, const CreateParam &param, bool isOpen);
  void update() override;
  static void open(GfMenuCallContext *context);
  static void close(GfMenuCallContext *context, bool flag);
  static void nextPage(GfMenuCallContext *context);
  static void prevPage(GfMenuCallContext *context);
  static void disp(GfMenuCallContext *context, bool flag);
};

static_assert(offsetof(GfMenuObjBlDetail::CreateParam, unknown08) == 0x08, "");
static_assert(offsetof(GfMenuObjBlDetail::CreateParam, unknown10) == 0x10, "");
static_assert(offsetof(GfMenuObjBlDetail::CreateParam, unknown14) == 0x14, "");
static_assert(offsetof(GfMenuObjBlDetail::CreateParam, unknown18) == 0x18, "");
static_assert(offsetof(GfMenuObjBlDetail::CreateParam, unknown1c) == 0x1c, "");
static_assert(offsetof(GfMenuObjBlDetail::CreateParam, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjBlDetail::CreateParam) == 0x24, "");
static_assert(offsetof(GfMenuObjBlDetail::unknown001, unknown04) == 0x04, "");
static_assert(offsetof(GfMenuObjBlDetail::unknown001, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjBlDetail::unknown001, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjBlDetail::unknown001, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjBlDetail::unknown001, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjBlDetail::unknown001, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuObjBlDetail::unknown001, unknown50) == 0x50, "");
static_assert(sizeof(GfMenuObjBlDetail::unknown001) == 0x58, "");
static_assert(offsetof(GfMenuObjBlDetail::DetailListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjBlDetail::DetailListener, unknown28) == 0x28, "");
static_assert(sizeof(GfMenuObjBlDetail::DetailListener) == 0x80, "");

} // namespace gf
