#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace gf {

class GfMenuObjMainRoot : public GfMenuObject {
public:
  struct OpenParam {
    u32 menu;
  };

  class MainListener : public ui::UIObjectListener {
  public:
    MainListener(GfMenuObjMainRoot *owner) : _0c(), owner(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjMainRoot *owner;
  };

  GfMenuObjMainRoot(u32 handle);
  ~GfMenuObjMainRoot() override;
  static void registOpenParam(const OpenParam &param);
  void initialize() override;
  void finalize() override;
  void update() override;
};

static_assert(offsetof(GfMenuObjMainRoot::MainListener, owner) == 0x20, "");
static_assert(sizeof(GfMenuObjMainRoot::MainListener) == 0x28, "");

} // namespace gf
