#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace gf {

struct GF_OBJ_HANDLE;

class GfMenuObjActionWindow : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    MainListener(GfMenuObjActionWindow *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjActionWindow *unknown20; // Inferred role: owner; original member name unknown.
  };

  struct OpenParam {
    GF_OBJ_HANDLE *unknown00; // Inferred role: target handle; original member name unknown.
    u32 unknown08;            // Inferred role: pad key; original member name unknown.
  };

  static void open(const OpenParam &param);
  static void openBattle(const OpenParam &param);
  static void close();
  static void closeBattle();
  static void disp(bool disp);
  GfMenuObjActionWindow(u32 handle);
  ~GfMenuObjActionWindow() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  void eventHudSceneChange(u32 scene) override;
};

static_assert(offsetof(GfMenuObjActionWindow::MainListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjActionWindow::MainListener) == 0x28, "");

} // namespace gf
