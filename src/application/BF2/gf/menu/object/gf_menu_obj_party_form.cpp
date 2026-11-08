#include "gf/menu/object/gf_menu_obj_party_form.h"

namespace gf {

GfMenuObjPartyForm::GfMenuObjPartyForm(u32 handle) : GfMenuObject(handle) {}

GfMenuObjPartyForm::~GfMenuObjPartyForm() {}

void GfMenuObjPartyForm::finalize() { GfMenuObject::finalize(); }

void GfMenuObjPartyForm::update() { GfMenuObject::update(); }

} // namespace gf
