#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace ui {
class UISelectObjList;
} // namespace ui

namespace gf {

class GfMenuCallContext;

class GfMenuObjMainSubmenu : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    MainListener(GfMenuObjMainSubmenu *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjMainSubmenu *unknown20; // Inferred role: owner; original member name unknown.
  };

  class ListListener : public ui::UIObjectListener {
  public:
    ListListener(GfMenuObjMainSubmenu *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjMainSubmenu *unknown20; // Inferred role: owner; original member name unknown.
  };

  GfMenuObjMainSubmenu(u32 handle);
  ~GfMenuObjMainSubmenu() override;
  void initialize() override;
  void finalize() override;
  void update() override;

  static bool isEnableSkipTime();

  u32 unknown24;                          // Role and original member name unknown, cleared by the constructor.
  u32 unknown28;                          // Role and original member name unknown, cleared by the constructor.
  u32 unknown2c;                          // Role and original member name unknown, cleared by the constructor.
  ui::UISelectObjList *unknown30;         // Inferred role: menu objects; original member name unknown.
  mm::mtl::FixedVector<int, 8> unknown38; // Inferred role: enabled menu entries; original member name unknown.
  u32 unknown60;                          // Inferred role: entry selected when the list opens; original member name unknown.
  bool unknown64;                         // Role and original member name unknown, set by the constructor.
  u8 _65[0x68 - 0x65];
  GfMenuCallContext *unknown68; // Inferred role: call context; original member name unknown.
  int unknown70[3];             // Inferred role: glow control of each entry, -1 at start (the list listener indexes it with the entry); original member name unknown.
  u8 _7c[0x80 - 0x7c];
};

static_assert(offsetof(GfMenuObjMainSubmenu::MainListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjMainSubmenu::MainListener) == 0x28, "");
static_assert(offsetof(GfMenuObjMainSubmenu::ListListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjMainSubmenu::ListListener) == 0x28, "");
static_assert(offsetof(GfMenuObjMainSubmenu, unknown24) == 0x24, "");
static_assert(offsetof(GfMenuObjMainSubmenu, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjMainSubmenu, unknown2c) == 0x2c, "");
static_assert(offsetof(GfMenuObjMainSubmenu, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjMainSubmenu, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjMainSubmenu, unknown64) == 0x64, "");
static_assert(offsetof(GfMenuObjMainSubmenu, unknown68) == 0x68, "");
static_assert(offsetof(GfMenuObjMainSubmenu, unknown70) == 0x70, "");
static_assert(offsetof(GfMenuObjMainSubmenu, unknown60) == 0x60, "");
static_assert(sizeof(GfMenuObjMainSubmenu) == 0x80, "");

} // namespace gf
