#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace ui {
class UISelectObjList;
} // namespace ui

namespace gf {

class GfMenuCallContext;
class GfMenuIDList;
class GfMenuMsgList;

class GfMenuObjEvTheater : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    MainListener(GfMenuObjEvTheater *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];           // Actively zero-initialized unknown byte range, NOT padding; original name/role unknown.
    GfMenuObjEvTheater *unknown20; // Inferred role: owner; original member name unknown.
  };

  class TopListener : public ui::UIObjectListener {
  public:
    TopListener(GfMenuObjEvTheater *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];           // Actively zero-initialized unknown byte range, NOT padding; original name/role unknown.
    GfMenuObjEvTheater *unknown20; // Inferred role: owner; original member name unknown.
  };

  class SubListener : public ui::UIObjectListener {
  public:
    SubListener(GfMenuObjEvTheater *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];           // Actively zero-initialized unknown byte range, NOT padding; original name/role unknown.
    GfMenuObjEvTheater *unknown20; // Inferred role: owner; original member name unknown.
  };

  class SelectListener : public ui::UIObjectListener {
  public:
    SelectListener(GfMenuObjEvTheater *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];           // Actively zero-initialized unknown byte range, NOT padding; original name/role unknown.
    GfMenuObjEvTheater *unknown20; // Inferred role: owner; original member name unknown.
  };

  class HeaderListener : public ui::UIObjectListener {
  public:
    HeaderListener(GfMenuObjEvTheater *owner) : unknown0c(0), _10(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u32 unknown0c;                 // Inferred role: header shown flag; original member name unknown.
    u8 _10[0x1c - 0x10];           // Actively zero-initialized unknown byte range, NOT padding; original name/role unknown.
    GfMenuObjEvTheater *unknown20; // Inferred role: owner; original member name unknown.
  };

  class ScreenListener : public ui::UIObjectListener {
  public:
    ScreenListener(GfMenuObjEvTheater *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];           // Actively zero-initialized unknown byte range, NOT padding; original name/role unknown.
    GfMenuObjEvTheater *unknown20; // Inferred role: owner; original member name unknown.
  };

  GfMenuObjEvTheater(u32 handle);
  ~GfMenuObjEvTheater() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  static bool attach(GfMenuCallContext *context);
  static void fadeout(GfMenuCallContext *context);
  static void fadein(GfMenuCallContext *context);
  static void dispOffScreen(bool isDisp);
  void refreshSelctList();
  void updateSubMsgList();
  void updateEvthIDList();
  void refreshSubList();

  int unknown24;                  // Role and original member name unknown, 1 at start.
  GfMenuMsgList *unknown28;       // Inferred role: event messages; original member name unknown.
  ui::UISelectObjList *unknown30; // Inferred role: message objects; original member name unknown.
  GfMenuIDList *unknown38;        // Inferred role: event ids; original member name unknown.
  ui::UISelectObjList *unknown40; // Inferred role: event objects; original member name unknown.
};

static_assert(offsetof(GfMenuObjEvTheater::MainListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjEvTheater::MainListener) == 0x28, "");
static_assert(offsetof(GfMenuObjEvTheater::TopListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjEvTheater::TopListener) == 0x28, "");
static_assert(offsetof(GfMenuObjEvTheater::SubListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjEvTheater::SubListener) == 0x28, "");
static_assert(offsetof(GfMenuObjEvTheater::SelectListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjEvTheater::SelectListener) == 0x28, "");
static_assert(offsetof(GfMenuObjEvTheater::HeaderListener, unknown0c) == 0x0c, "");
static_assert(offsetof(GfMenuObjEvTheater::HeaderListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjEvTheater::HeaderListener) == 0x28, "");
static_assert(offsetof(GfMenuObjEvTheater::ScreenListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjEvTheater::ScreenListener) == 0x28, "");
static_assert(offsetof(GfMenuObjEvTheater, unknown24) == 0x24, "");
static_assert(offsetof(GfMenuObjEvTheater, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjEvTheater, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjEvTheater, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjEvTheater, unknown40) == 0x40, "");
static_assert(sizeof(GfMenuObjEvTheater) == 0x48, "");

} // namespace gf
