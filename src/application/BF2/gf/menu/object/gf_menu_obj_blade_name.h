#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace gf {

class GfMenuCallContext;

class GfMenuObjBladeName : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    MainListener(GfMenuObjBladeName *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjBladeName *unknown20; // Inferred role: owner; original member name unknown.
  };

  // Inferred helper: zooms in the blade name text and its shadow; original name unknown.
  void unknown002() {
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 0x10000000;
    param.unknown50 = "cmn_fade_motion_zoom";
    param.unknown58 = "fade_in";
    param.unknown14 = 10;
    GfMenuObjUtil::startCtrl(unknown18, param, "TXT_bl_name");
    GfMenuObjUtil::startCtrl(unknown18, param, "TXT_bl_name_shadow");
  }

  GfMenuObjBladeName(u32 handle);
  ~GfMenuObjBladeName() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  static void open(GfMenuCallContext *context);
  static void pause(GfMenuCallContext *context);
  static void close();
  bool seqStart();
  bool seqApperNormal();
  bool seqApperRare();
  bool seqApperName();
  bool seqApperWait();
  bool seqLeave();

  GfMenuSequence<GfMenuObjBladeName, 8> unknown28; // Inferred role: appear and leave steps; original member name unknown.
  bool unknown2b8;                                 // Inferred role: leave control started flag; original member name unknown.
};

static_assert(offsetof(GfMenuObjBladeName::MainListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjBladeName, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjBladeName, unknown2b8) == 0x2b8, "");
static_assert(sizeof(GfMenuObjBladeName) == 0x2c0, "");

} // namespace gf
