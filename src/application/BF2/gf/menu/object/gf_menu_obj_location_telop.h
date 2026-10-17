#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace gf {

class GfMenuObjLocationTelop : public GfMenuObject {
public:
  struct OpenParam {
    u8 *bdat;
    u32 textId;
    u16 type;
    u16 mapId;
    bool isNew;
  };

  class MainListener : public ui::UIObjectListener {
  public:
    MainListener(GfMenuObjLocationTelop *owner) : _0c(), owner(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjLocationTelop *owner;
  };

  GfMenuObjLocationTelop(u32 handle);
  ~GfMenuObjLocationTelop() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  static void open(const OpenParam &param);
  static void close();
  static void cancel();
};

static_assert(offsetof(GfMenuObjLocationTelop::OpenParam, type) == 0x0c, "");
static_assert(offsetof(GfMenuObjLocationTelop::OpenParam, mapId) == 0x0e, "");
static_assert(offsetof(GfMenuObjLocationTelop::OpenParam, isNew) == 0x10, "");
static_assert(offsetof(GfMenuObjLocationTelop::MainListener, owner) == 0x20, "");
static_assert(sizeof(GfMenuObjLocationTelop::MainListener) == 0x28, "");

} // namespace gf
