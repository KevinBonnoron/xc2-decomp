#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace gf {

class GfMenuCallContext;
class GfMenuReferenceNumber;

class GfMenuObjDummyTutorial : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    MainListener(GfMenuObjDummyTutorial *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    u8 _1c[0x20 - 0x1c];
    GfMenuObjDummyTutorial *unknown20; // Inferred role: owner; original member name unknown.
  };

  GfMenuObjDummyTutorial(u32 handle);
  ~GfMenuObjDummyTutorial() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  struct OpenParam {
    u32 unknown00; // Inferred role: tutorial; original member name unknown.
  };

  static void open(GfMenuCallContext *context, const OpenParam &param);

  u8 _24[0x28 - 0x24];
  mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown28; // Inferred role: reference number; original member name unknown.
};

static_assert(offsetof(GfMenuObjDummyTutorial::MainListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjDummyTutorial, unknown28) == 0x28, "");

} // namespace gf
