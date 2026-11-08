#include "gf/menu/object/gf_menu_obj_party_form.h"

#include "mm_mtl/fixstr.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: animation of each selection state; original name unknown.
static const char *const unknown001[] = {"none", "select", "hold"};

// Inferred role: finds the background image of a party member slot; original name unknown.
static u32 unknown002(u32 handle, const char *format, u32 index) {
  mm::mtl::FixStr<32> name;
  name.format(format, index + 1, "bg");
  return ui::UIObjectAcc(handle).searchChild(name.c_str());
}

void GfMenuObjPartyForm::selectDriver(u32 handle, u32 index, u32 state) {
  ui::UIObjectAcc image(unknown002(handle, "IMG_driver%02d_%s", index));
  if (image.isValid()) {
    image.startAnimation(unknown001[state], false);
  }
}

void GfMenuObjPartyForm::selectBlade(u32 handle, u32 index, u32 state) {
  ui::UIObjectAcc image(unknown002(handle, "IMG_blade%02d_%s", index));
  if (image.isValid()) {
    image.startAnimation(unknown001[state], false);
  }
}

GfMenuObjPartyForm::GfMenuObjPartyForm(u32 handle) : GfMenuObject(handle) {}

GfMenuObjPartyForm::~GfMenuObjPartyForm() {}

void GfMenuObjPartyForm::finalize() { GfMenuObject::finalize(); }

void GfMenuObjPartyForm::update() { GfMenuObject::update(); }

} // namespace gf
