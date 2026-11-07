#include "gf/menu/object/gf_menu_obj_operation_info.h"

#include "gf/menu/gf_menu_types.h"
#include "types.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x47;

void GfMenuObjOperationInfo::finalize() { GfMenuObject::finalize(); }

void GfMenuObjOperationInfo::open(u32 handle, u32 unknown0, u32 unknown1, u32 unknown2) { GF_MENU_REQUEST_EVENT4(unknown001, GfMenuTypes::unknown003_33, handle, unknown0, unknown1, unknown2); }

void GfMenuObjOperationInfo::update() { GfMenuObject::update(); }

void GfMenuObjOperationInfo::close() { GF_MENU_REQUEST_EVENT(unknown001, GfMenuTypes::unknown003_34); }

void GfMenuObjOperationInfo::setDisp(bool isDisp) { unknown154(unknown001, isDisp); }

void GfMenuObjOperationInfo::setGuideText(u32 param0, u32 param1) { GF_MENU_REQUEST_EVENT2(unknown001, 0x101, param0, param1); }

void GfMenuObjOperationInfo::setGuideDisp(bool param0) { GF_MENU_REQUEST_EVENT1(unknown001, 0x106, param0); }

void GfMenuObjOperationInfo::add(u32 param0, u32 param1, u32 param2, u32 param3) { GF_MENU_REQUEST_EVENT4(unknown001, 0x102, param0, param1, param2, param3); }

void GfMenuObjOperationInfo::remove(u32 param0, u32 param1, u32 param2, u32 param3) { GF_MENU_REQUEST_EVENT4(unknown001, 0x103, param0, param1, param2, param3); }

void GfMenuObjOperationInfo::changeText(u32 param0, u32 param1, bool param2) { GF_MENU_REQUEST_EVENT3(unknown001, 0x104, param0, param1, param2); }

void GfMenuObjOperationInfo::changeText(u32 param0, u32 param1, u32 param2) { GF_MENU_REQUEST_EVENT3(unknown001, 0x104, param0, param1, param2); }

void GfMenuObjOperationInfo::setActionEnable(u32 param0, u32 param1, bool param2) { GF_MENU_REQUEST_EVENT3(unknown001, 0x105, param0, param1, param2); }

void GfMenuObjOperationInfo::moveGuide(u32 param0, bool param1) { GF_MENU_REQUEST_EVENT2(unknown001, 0x107, param0, param1); }

void GfMenuObjOperationInfo::fadeGuide(bool param0) { GF_MENU_REQUEST_EVENT1(unknown001, 0x108, param0); }

} // namespace gf
