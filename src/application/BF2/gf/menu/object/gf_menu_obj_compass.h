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

  // Parameter of addLocator, copied whole into the icon list entry (the game moves it with one 64-bit load and store); the type name comes from the symbol of addLocator.
  struct LocatorParam {
    u16 unknown00; // Inferred role: locator type; original member name unknown.
    u16 unknown02; // Inferred role: locator index; original member name unknown.
    int unknown04; // Role unknown; the game passes 50 for the last locator type and 0 for the others; original member name unknown.
  };

  // Entry of the compass icon list; the name comes from the symbol of mm::mtl::FixedVector<gf::GfMenuObjCompass::IconObj, 32>.
  struct IconObj {
    u32 unknown00;          // Inferred role: icon object handle; original member name unknown.
    LocatorParam unknown04; // Inferred role: locator; original member name unknown.
    int unknown0c;          // Inferred role: frames left before the icon is hidden; original member name unknown.
  };

  GfMenuObjCompass(u32 handle);
  ~GfMenuObjCompass() override;
  static void close();
  static void open();
  static void dispInBattle(bool isDisp);
  static void addLocator(const LocatorParam &param);
  void initialize() override;
  void finalize() override;
  void update() override;

  static mm::mtl::FixedVector<IconObj, 32> m_IconObjList;
};

static_assert(offsetof(GfMenuObjCompass::MainListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjCompass::MainListener) == 0x28, "");
static_assert(sizeof(GfMenuObjCompass::LocatorParam) == 0x8, "");
static_assert(offsetof(GfMenuObjCompass::IconObj, unknown04) == 0x4, "");
static_assert(sizeof(GfMenuObjCompass::IconObj) == 0x10, "");
static_assert(sizeof(GfMenuObjCompass) == 0x28, "");

} // namespace gf
