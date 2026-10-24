#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace gf {

class GfMenuObjMainRoot : public GfMenuObject {
public:
  struct OpenParam {
    u32 unknown00; // Inferred role: menu; original member name unknown.
  };

  class MainListener : public ui::UIObjectListener {
  public:
    MainListener(GfMenuObjMainRoot *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjMainRoot *unknown20; // Inferred role: owner; original member name unknown.
  };

  GfMenuObjMainRoot(u32 handle);
  ~GfMenuObjMainRoot() override;
  static void registOpenParam(const OpenParam &param);
  void initialize() override;
  void finalize() override;
  void update() override;
};

static_assert(offsetof(GfMenuObjMainRoot::MainListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjMainRoot::MainListener) == 0x28, "");

} // namespace gf
