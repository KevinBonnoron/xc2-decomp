#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace gf {

class GfMenuObjEnvironmentInfo : public GfMenuObject {
public:
  class ListListener : public ui::UIObjectListener {
  public:
    // Inferred role: enabled flag and fade control of the list, assigned as one 8 byte value (the game stores both with one 64-bit constant at 0x710045d9b4); original type name unknown.
    struct unknown004 {
      int unknown00; // Inferred role: enabled flag; original member name unknown.
      int unknown04; // Inferred role: fade control, -1 when none; original member name unknown.
    };

    ListListener(GfMenuObjEnvironmentInfo *owner) : unknown0c(0), unknown10(), _18(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    int unknown0c; // Inferred role: opened flag; original member name unknown.
    unknown004 unknown10;
    u8 _18[0x1c - 0x18];
    GfMenuObjEnvironmentInfo *unknown20; // Inferred role: owner; original member name unknown.
  };

  static void close();
  static void open();
  static void disable();
  static void enable();
  static void createAdapter(u32 handle, const char *name, u32 type);
  static void setupScreen(u32 handle);
  GfMenuObjEnvironmentInfo(u32 handle);
  ~GfMenuObjEnvironmentInfo() override;
  void initialize() override;
  void finalize() override;
  void update() override;
};

static_assert(offsetof(GfMenuObjEnvironmentInfo::ListListener, unknown0c) == 0x0c, "");
static_assert(offsetof(GfMenuObjEnvironmentInfo::ListListener, unknown10) == 0x10, "");
static_assert(offsetof(GfMenuObjEnvironmentInfo::ListListener::unknown004, unknown04) == 0x04, "");
static_assert(offsetof(GfMenuObjEnvironmentInfo::ListListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjEnvironmentInfo::ListListener) == 0x28, "");

} // namespace gf
