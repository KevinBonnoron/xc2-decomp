#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace gf {

class GfMenuObjSaveLoad : public GfMenuObject {
public:
  class ListListener : public ui::UIObjectListener {
  public:
    ListListener(GfMenuObjSaveLoad *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    u8 _1c[0x20 - 0x1c];
    GfMenuObjSaveLoad *unknown20; // Inferred role: owner; original member name unknown.
  };

  GfMenuObjSaveLoad(u32 handle);
  ~GfMenuObjSaveLoad() override;
  void initialize() override;
  void finalize() override;
  void update() override;

  u32 unknown24; // Role and original member name unknown, zeroed by the constructor.
};

static_assert(offsetof(GfMenuObjSaveLoad, unknown24) == 0x24, "");
static_assert(offsetof(GfMenuObjSaveLoad::ListListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjSaveLoad::ListListener) == 0x28, "");

} // namespace gf
