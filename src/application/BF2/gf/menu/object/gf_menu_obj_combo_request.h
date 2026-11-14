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
  struct RequestParam {
    u16 unknown00;  // Inferred role: combo id; original member name unknown.
    u32 unknown04;  // Inferred role: button; original member name unknown.
    bool unknown08; // Inferred role: enable flag; original member name unknown.
  };

  GfMenuObjComboRequest(u32 handle);
  ~GfMenuObjComboRequest() override;
  static void attachComboRequest(GfMenuCallContext *context);
  static void openComboRequest(u16 index, const RequestParam &param);
  static void closeComboRequest(u16 index, bool isImmediate);
  static void resetComboRequest(u16 index, const RequestParam &param);
  void initialize() override;
  void finalize() override;
  void update() override;
  void setupComboReq(const ui::UIObjectAcc &acc, u16 index, u16 combo, bool isEnable, u32 button);
};

static_assert(offsetof(GfMenuObjComboRequest::MainListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjComboRequest::RequestParam, unknown04) == 0x4, "");
static_assert(offsetof(GfMenuObjComboRequest::RequestParam, unknown08) == 0x8, "");
static_assert(sizeof(GfMenuObjComboRequest::RequestParam) == 0xc, "");

static_assert(sizeof(GfMenuObjComboRequest::MainListener) == 0x28, "");

} // namespace gf
