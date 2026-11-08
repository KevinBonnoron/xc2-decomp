#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace ui {
class UIObjectAcc;
} // namespace ui

namespace gf {
class GfMenuCallContext;

class GfMenuObjComboRequest : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    MainListener(GfMenuObjComboRequest *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjComboRequest *unknown20; // Inferred role: owner; original member name unknown.
  };

  GfMenuObjComboRequest(u32 handle);
  ~GfMenuObjComboRequest() override;
  static void attachComboRequest(GfMenuCallContext *context);
  static void closeComboRequest(u16 index, bool isImmediate);
  void initialize() override;
  void finalize() override;
  void update() override;
  void setupComboReq(const ui::UIObjectAcc &acc, u16 index, u16 combo, bool isEnable, u32 button);
};

static_assert(offsetof(GfMenuObjComboRequest::MainListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjComboRequest::MainListener) == 0x28, "");

} // namespace gf
