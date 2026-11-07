#include "gf/menu/object/gf_menu_obj_arts_palette.h"

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/object/gf_menu_obj_blade_change.h"
#include "mm_mtl/fixstr.h"
#include "types.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: ui event type; original name unknown.
constexpr u16 unknown003 = 0x10b;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown004 = 0x101;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown005 = 0x100;

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x27;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown002 = 0x10a;

void GfMenuObjArtsPalette::finalize() { GfMenuObject::finalize(); }

void GfMenuObjArtsPalette::push(unsigned int slot) { unknown149(unknown001, unknown002, slot); }

void GfMenuObjArtsPalette::startChainAttack() { unknown157(unknown001, unknown003, 1); }

void GfMenuObjArtsPalette::exitChainAttack() { unknown144(unknown001, unknown003); }

void GfMenuObjArtsPalette::close() { unknown145(unknown001, unknown004); }

void GfMenuObjArtsPalette::open() { unknown145(unknown001, unknown005); }

void GfMenuObjArtsPalette::pushReverseBtn(u32 button) { unknown149(unknown001, 0x10d, button); }

void GfMenuObjArtsPalette::reverse(bool isReverse) { unknown150(unknown001, 0x10c, isReverse); }

void GfMenuObjArtsPalette::dispInfo(bool isDisp) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid() && !acc.isTerm()) {
    acc.setDispChild(isDisp, "LAY_arts_info");
    GfMenuObjBladeChange::dispInfo(isDisp);
  }
}

GfMenuObjArtsPalette::~GfMenuObjArtsPalette() { ; }

void GfMenuObjArtsPalette::update() {
  unknown7f0->unknown003();
  unknown7f8->unknown003();
  unknown800->unknown003();
  unknown808.unknown003();
  GfMenuObject::update();
}

void GfMenuObjArtsPalette::updateArtsIconDisp(u32 slot) {
  mm::mtl::FixStr<32> name;
  name.format("LAY_arts_icon@%02d", slot + 1);
  ui::UIObjectAcc icon(unknown18, name.c_str());
  if ((unknown30[slot] & 3) == 3) {
    icon.setMulColor("white");
  } else {
    icon.setMulColor("gray");
  }
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuSequence<gf::GfMenuObjArtsPalette, 4>>(const mm::mtl::Delegate<bool()> *);
template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuSequence<gf::GfMenuObjArtsPalette, 8>>(const mm::mtl::Delegate<bool()> *);
