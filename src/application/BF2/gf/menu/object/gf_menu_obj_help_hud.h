#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace gf {

class GfMenuObjHelpHud : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    MainListener(GfMenuObjHelpHud *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjHelpHud *unknown20; // Inferred role: owner; original member name unknown.
  };

  GfMenuObjHelpHud(u32 handle);
  ~GfMenuObjHelpHud() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  static void enable();
  static void disable();
  static void ctrlFadeOut(u32 handle);
  static void ctrlFadeIn(u32 handle);
  bool seqPageFadeIn();
  bool seqPageFadeOut();
  bool seqPageLoad();

  u32 unknown24; // Inferred role: unused; original member name unknown.
  u8 _28[0x30 - 0x28];
  GfMenuSequence<GfMenuObjHelpHud, 8> unknown30; // Inferred role: page steps; original member name unknown.
  bool unknown2c0;                               // Inferred role: page fade control started flag; original member name unknown.
};

static_assert(offsetof(GfMenuObjHelpHud, unknown24) == 0x24, "");
static_assert(offsetof(GfMenuObjHelpHud, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjHelpHud, unknown2c0) == 0x2c0, "");
static_assert(offsetof(GfMenuObjHelpHud::MainListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjHelpHud::MainListener) == 0x28, "");

} // namespace gf
