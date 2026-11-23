#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace gf {

class GfMenuPosAdapter;

class GfMenuObjOtherCursor : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    MainListener(GfMenuObjOtherCursor *owner) : _0c(), m_menuObjOtherCursor(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjOtherCursor *m_menuObjOtherCursor; // Inferred role: owner; original member name unknown.
  };

  GfMenuObjOtherCursor(u32 handle);
  ~GfMenuObjOtherCursor() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  static void disp(bool disp);

  u32 unknown24; // Role and original member name unknown, zeroed by the constructor.
  u8 _28[0x30 - 0x28];
  GfMenuPosAdapter *m_menuPosAdapter; // Inferred role: cursor position adapter, cleared by the constructor; original member name unknown.
};

static_assert(offsetof(GfMenuObjOtherCursor::MainListener, m_menuObjOtherCursor) == 0x20, "");
static_assert(sizeof(GfMenuObjOtherCursor::MainListener) == 0x28, "");
static_assert(offsetof(GfMenuObjOtherCursor, unknown24) == 0x24, "");
static_assert(offsetof(GfMenuObjOtherCursor, m_menuPosAdapter) == 0x30, "");
static_assert(sizeof(GfMenuObjOtherCursor) == 0x38, "");

} // namespace gf
