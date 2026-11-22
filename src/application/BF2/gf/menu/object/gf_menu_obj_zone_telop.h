#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace gf {

class GfMenuCallContext;

class GfMenuObjZoneTelop : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    MainListener(GfMenuObjZoneTelop *owner) : _0c(), m_menuObjZoneTelop(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjZoneTelop *m_menuObjZoneTelop; // Inferred role: owner; original member name unknown.
  };

  GfMenuObjZoneTelop(u32 handle);
  ~GfMenuObjZoneTelop() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  static void open(GfMenuCallContext *context, u16 zone);
  static void close(f32 wait);
  bool seqFadeIn();
  bool seqFadeOut();

  u8 _24[0x28 - 0x24];
  GfMenuSequence<GfMenuObjZoneTelop, 4> unknown28; // Inferred role: telop steps; original member name unknown.
  bool unknown188;                                 // Inferred role: fade control started flag; original member name unknown.
  f32 unknown18c;                                  // Inferred role: fade out time; original member name unknown.
};

static_assert(offsetof(GfMenuObjZoneTelop::MainListener, m_menuObjZoneTelop) == 0x20, "");
static_assert(sizeof(GfMenuObjZoneTelop::MainListener) == 0x28, "");
static_assert(offsetof(GfMenuObjZoneTelop, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjZoneTelop, unknown188) == 0x188, "");
static_assert(offsetof(GfMenuObjZoneTelop, unknown18c) == 0x18c, "");
static_assert(sizeof(GfMenuObjZoneTelop) == 0x190, "");

} // namespace gf
