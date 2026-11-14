#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace ui {
struct EventData;
class UICtrlCursorSelect;
class UICtrlRevolveSelect;
class UIListInfoBase;
class UISelectObjList;
} // namespace ui

namespace gf {

class GfMenuObjLinkJump : public GfMenuObject {
public:
  class RootListener : public ui::UIObjectListener {
  public:
    RootListener(GfMenuObjLinkJump *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjLinkJump *unknown20; // Inferred role: owner; original member name unknown.
  };

  class CategoryListener : public ui::UIObjectListener {
  public:
    CategoryListener(GfMenuObjLinkJump *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjLinkJump *unknown20; // Inferred role: owner; original member name unknown.
  };

  class NotifyListener : public ui::UIObjectListener {
  public:
    NotifyListener(GfMenuObjLinkJump *owner) : unknown0c(0), _10(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    int unknown0c; // Inferred role: fade control id; original member name unknown.
    u8 _10[0x1c - 0x10];
    GfMenuObjLinkJump *unknown20; // Inferred role: owner; original member name unknown.
  };

  // Inferred role: list shown on one side of the screen; original type name unknown.
  struct unknown002 {
    u32 unknown00; // Inferred role: UI object handle; original member name unknown.
    u8 _04[0x08 - 0x04];
    ui::UIListInfoBase *unknown08;     // Inferred role: referenced list; original member name unknown.
    ui::UISelectObjList *unknown10;    // Inferred role: list objects; original member name unknown.
    ui::UICtrlCursorSelect *unknown18; // Inferred role: list cursor; original member name unknown.
  };

  class ListListener : public ui::UIObjectListener {
  public:
    ListListener(GfMenuObjLinkJump *owner, unknown002 *list) : _0c(), unknown20(owner), unknown28(list) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjLinkJump *unknown20; // Inferred role: owner; original member name unknown.
    unknown002 *unknown28;        // Inferred role: list of the listened object; original member name unknown.
  };

  GfMenuObjLinkJump(u32 handle);
  ~GfMenuObjLinkJump() override;
  static void open();
  void initialize() override;
  void finalize() override;
  void update() override;
  static void close();
  void changeCategory(int index);
  void setupListObject(u32 index);
  void listenerCategorySelect(const ui::EventData &event);

  u8 _24[0x28 - 0x24];
  unknown002 unknown28[2];
  ui::UISelectObjList *unknown68;     // Inferred role: category objects; original member name unknown.
  ui::UICtrlRevolveSelect *unknown70; // Inferred role: category revolve cursor; original member name unknown.
  bool unknown78;                     // Inferred role: category list shown flag; original member name unknown.
  u8 _79[0x80 - 0x79];
};

static_assert(offsetof(GfMenuObjLinkJump::unknown002, unknown08) == 0x08, "");
static_assert(offsetof(GfMenuObjLinkJump::unknown002, unknown10) == 0x10, "");
static_assert(offsetof(GfMenuObjLinkJump::unknown002, unknown18) == 0x18, "");
static_assert(sizeof(GfMenuObjLinkJump::unknown002) == 0x20, "");
static_assert(offsetof(GfMenuObjLinkJump::RootListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjLinkJump::RootListener) == 0x28, "");
static_assert(offsetof(GfMenuObjLinkJump::CategoryListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjLinkJump::CategoryListener) == 0x28, "");
static_assert(offsetof(GfMenuObjLinkJump::NotifyListener, unknown0c) == 0x0c, "");
static_assert(offsetof(GfMenuObjLinkJump::NotifyListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjLinkJump::NotifyListener) == 0x28, "");
static_assert(offsetof(GfMenuObjLinkJump::ListListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjLinkJump::ListListener, unknown28) == 0x28, "");
static_assert(sizeof(GfMenuObjLinkJump::ListListener) == 0x30, "");
static_assert(offsetof(GfMenuObjLinkJump, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjLinkJump, unknown68) == 0x68, "");
static_assert(offsetof(GfMenuObjLinkJump, unknown70) == 0x70, "");
static_assert(offsetof(GfMenuObjLinkJump, unknown78) == 0x78, "");
static_assert(sizeof(GfMenuObjLinkJump) == 0x80, "");

} // namespace gf
