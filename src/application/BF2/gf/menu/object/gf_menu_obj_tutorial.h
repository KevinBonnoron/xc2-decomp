#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace gf {

class GfMenuObjTutorial : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    MainListener(GfMenuObjTutorial *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjTutorial *unknown20; // Inferred role: owner; original member name unknown.
  };

  struct TextParam {
    u32 unknown00; // Inferred role: text id in the tutorial bdat; original member name unknown.
  };

  struct FocusParam {
    u16 unknown00; // Inferred role: event parameter; original member name unknown.
    u16 unknown02; // Inferred role: event parameter; original member name unknown.
    u16 unknown04; // Inferred role: event parameter; original member name unknown.
  };

  struct IconParam {
    u16 unknown00; // Inferred role: event parameter; original member name unknown.
    u16 unknown02; // Inferred role: event parameter; original member name unknown.
  };

  GfMenuObjTutorial(u32 handle);
  ~GfMenuObjTutorial() override;
  static void closeAll();
  static void openText(u32 param, const TextParam &text);
  static void closeText(u32 param);
  static void openFocus(u32 param, const FocusParam &focus);
  static void closeFocus(u32 param);
  static void openIcon(u32 param, const IconParam &icon);
  static void closeIcon(u32 param);
  static void start();
  void initialize() override;
  void finalize() override;
  void update() override;
  static bool isWaiting();
  bool seqTelopStart();
  bool seqTelopEnd();
  bool seqEnd();

  GfMenuSequence<GfMenuObjTutorial, 8> unknown28; // Inferred role: telop steps; original member name unknown.
  bool unknown2b8;                                // Inferred role: animation started flag; original member name unknown.
  int unknown2bc;                                 // Inferred role: frames left before the call context ends; original member name unknown.
};

static_assert(offsetof(GfMenuObjTutorial, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjTutorial, unknown2b8) == 0x2b8, "");
static_assert(offsetof(GfMenuObjTutorial, unknown2bc) == 0x2bc, "");
static_assert(sizeof(GfMenuObjTutorial) == 0x2c0, "");

static_assert(sizeof(GfMenuObjTutorial::TextParam) == 0x4, "");
static_assert(offsetof(GfMenuObjTutorial::FocusParam, unknown04) == 0x4, "");
static_assert(sizeof(GfMenuObjTutorial::FocusParam) == 0x6, "");
static_assert(offsetof(GfMenuObjTutorial::IconParam, unknown02) == 0x2, "");
static_assert(sizeof(GfMenuObjTutorial::IconParam) == 0x4, "");

static_assert(offsetof(GfMenuObjTutorial::MainListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjTutorial::MainListener) == 0x28, "");

} // namespace gf
