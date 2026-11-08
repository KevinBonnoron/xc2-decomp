#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace gf {

class GfMenuObjCompass : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    // Inferred role: control of the battle frame and opened flag of the compass; original type name unknown.
    struct unknown005 {
      int unknown00; // Inferred role: control of the battle frame, -1 when none; original member name unknown.
      int unknown04; // Inferred role: opened flag; original member name unknown.
    };

    MainListener(GfMenuObjCompass *owner) : unknown0c(0), unknown10(), _18(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    int unknown0c; // Inferred role: control of the open and close fade; original member name unknown.
    unknown005 unknown10;
    u8 _18[0x1c - 0x18];
    GfMenuObjCompass *unknown20; // Inferred role: owner; original member name unknown.
  };

  // Inferred role: entry of the compass icon list; original name unknown.
  struct unknown004 {
    u32 unknown00; // Inferred role: icon object handle; original member name unknown.
    u32 unknown04; // Inferred role: locator ids; original member name unknown.
    u32 unknown08; // Role and original member name unknown.
    int unknown0c; // Inferred role: frames left before the icon is hidden; original member name unknown.
  };

  GfMenuObjCompass(u32 handle);
  ~GfMenuObjCompass() override;
  static void close();
  static void open();
  static void dispInBattle(bool isDisp);
  void initialize() override;
  void finalize() override;

  static mm::mtl::FixedVector<unknown004, 32> m_IconObjList;
};

static_assert(offsetof(GfMenuObjCompass::MainListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjCompass::MainListener) == 0x28, "");
static_assert(sizeof(GfMenuObjCompass::unknown004) == 0x10, "");
static_assert(sizeof(GfMenuObjCompass) == 0x28, "");

} // namespace gf
