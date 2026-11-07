#include "gf/menu/object/gf_menu_obj_opening_telop.h"

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x82;
// Inferred role: telop position; original name unknown.
constexpr u32 unknown002_0 = 0;
constexpr u32 unknown002_1 = 1;
constexpr u32 unknown002_2 = 2;

void GfMenuObjOpeningTelop::openCenter(u32 telop) { unknown141(unknown001, GfMenuTypes::unknown003_33, unknown002_0, telop); }

void GfMenuObjOpeningTelop::closeCenter() { unknown144(unknown001, GfMenuTypes::unknown003_34); }

void GfMenuObjOpeningTelop::openLeft(u32 telop) { unknown141(unknown001, GfMenuTypes::unknown003_33, unknown002_1, telop); }

void GfMenuObjOpeningTelop::closeLeft() { unknown157(unknown001, GfMenuTypes::unknown003_34, unknown002_1); }

void GfMenuObjOpeningTelop::openRight(u32 telop) { unknown141(unknown001, GfMenuTypes::unknown003_33, unknown002_2, telop); }

void GfMenuObjOpeningTelop::closeRight() { unknown157(unknown001, GfMenuTypes::unknown003_34, unknown002_2); }

void GfMenuObjOpeningTelop::finalize() { GfMenuObject::finalize(); }

void GfMenuObjOpeningTelop::ctrlFadeIn(u32 handle, u32 type) {
  GfMenuObjUtil::CtrlParam param;
  param.unknown08 = 1;
  param.unknown00 = 0.5f;
  param.unknown04 = type;
  GfMenuObjUtil::startCtrl(handle, param, nullptr);
}

void GfMenuObjOpeningTelop::ctrlFadeOut(u32 handle, u32 type) {
  GfMenuObjUtil::CtrlParam param;
  param.unknown08 = 2;
  param.unknown00 = 0.5f;
  param.unknown04 = type;
  GfMenuObjUtil::startCtrl(handle, param, nullptr);
}

} // namespace gf
