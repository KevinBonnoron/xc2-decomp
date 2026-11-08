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
    ListListener(GfMenuObjEnvironmentInfo *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
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

static_assert(offsetof(GfMenuObjEnvironmentInfo::ListListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjEnvironmentInfo::ListListener) == 0x28, "");

} // namespace gf
