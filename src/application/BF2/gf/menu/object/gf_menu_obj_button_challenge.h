#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace gf {

class GfMenuCallContext;

class GfMenuObjButtonChallenge : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    MainListener(GfMenuObjButtonChallenge *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjButtonChallenge *unknown20; // Inferred role: owner; original member name unknown.
    u8 _28[0x38 - 0x28];                 // Not initialized by the constructor; original members unknown.
  };

  GfMenuObjButtonChallenge(u32 handle);
  ~GfMenuObjButtonChallenge() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  static void cancel(GfMenuCallContext *context);
};

static_assert(offsetof(GfMenuObjButtonChallenge::MainListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjButtonChallenge::MainListener) == 0x38, "");

} // namespace gf
