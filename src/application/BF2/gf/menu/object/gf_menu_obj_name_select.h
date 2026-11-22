#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace gf {

class GfMenuCallContext;

class GfMenuObjNameSelect : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    MainListener(GfMenuObjNameSelect *owner) : _0c(), m_menuObjNameSelect(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjNameSelect *m_menuObjNameSelect; // Inferred role: owner; original member name unknown.
  };

  GfMenuObjNameSelect(u32 handle);
  ~GfMenuObjNameSelect() override;
  void initialize() override;
  void finalize() override;
  void update() override;

  u8 _24[0x28 - 0x24];
  GfMenuCallContext *m_menuCallContext; // Inferred role: call context; original member name unknown.
  u8 _30[0x30 - 0x30];
};

static_assert(offsetof(GfMenuObjNameSelect::MainListener, m_menuObjNameSelect) == 0x20, "");
static_assert(sizeof(GfMenuObjNameSelect::MainListener) == 0x28, "");
static_assert(offsetof(GfMenuObjNameSelect, m_menuCallContext) == 0x28, "");
static_assert(sizeof(GfMenuObjNameSelect) == 0x30, "");

} // namespace gf
