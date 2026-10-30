#include "gf/menu/object/gf_menu_obj_party_form3.h"

#include "gf/menu/gf_menu_fullscreen.h"
#include "gf/menu/gf_menu_types.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: menu id; original name unknown.
constexpr u32 unknown001 = 0x24;

void GfMenuObjPartyForm3::finalize() { GfMenuObject::finalize(); }

void GfMenuObjPartyForm3::registOpenParam(const OpenParam &param) {
  GfMenuTypes::Param layerParam;
  layerParam.set(param);
  GfMenuFullScreen::registLayerParam(getMenuLayerID(unknown001), layerParam);
}

void GfMenuObjPartyForm3::setupBGLayout(ui::UIObjectAcc &, u32, bool) {}

void GfMenuObjPartyForm3::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

bool GfMenuObjPartyForm3::seqWaitOpenEnd() {
  ui::UIObjectAcc acc(unknown18, "LAY_dr_select");
  enableInput(acc.unknown10);
  return true;
}

} // namespace gf
