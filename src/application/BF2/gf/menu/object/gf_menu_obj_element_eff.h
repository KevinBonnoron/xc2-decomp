#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace gf {

class GfMenuCallContext;

class GfMenuObjElementEff : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    MainListener(GfMenuObjElementEff *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjElementEff *unknown20; // Inferred role: owner; original member name unknown.
  };

  GfMenuObjElementEff(u32 handle);
  ~GfMenuObjElementEff() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  struct StartParam {
    u32 attribute;
  };

  static void start(GfMenuCallContext *context, const StartParam &param);
  static void cancel(GfMenuCallContext *context);
  bool seqInit();
  bool seqOpen();
  bool seqLoop();
  bool seqComboName();
  bool seqClose();

  u8 _24[0x28 - 0x24];
  GfMenuSequence<GfMenuObjElementEff, 8> unknown28; // Inferred role: queued steps; original member name unknown.
  int unknown2b8;                                   // Inferred role: control of the current step, -1 when idle; original member name unknown.
  u32 unknown2bc;                                   // Role and original member name unknown, cleared by the constructor.
  int unknown2c0;                                   // Inferred role: frames left before the combo name fades out; original member name unknown.
};

static_assert(offsetof(GfMenuObjElementEff::MainListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjElementEff, unknown2b8) == 0x2b8, "");
static_assert(offsetof(GfMenuObjElementEff, unknown2bc) == 0x2bc, "");
static_assert(offsetof(GfMenuObjElementEff, unknown2c0) == 0x2c0, "");
static_assert(sizeof(GfMenuObjElementEff) == 0x2c8, "");

} // namespace gf
