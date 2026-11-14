#include "gf/menu/object/gf_menu_obj_staffroll.h"

#include "framework/resource/common_resource.h"
#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_manager.h"
#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_math/mm_pnt.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_str.h"
#include "ui/ui_util.h"

namespace gf {

// Inferred role: name of the text object of each column alignment; original name unknown.
const char *const unknown002[] = {"TXT_left", "TXT_center", "TXT_right", "TXT_right2"};

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x85;

GfMenuObjStaffroll::GfMenuObjStaffroll(u32 handle) : GfMenuObject(handle), unknown28(nullptr), unknown58(0), unknown5c(0), unknown60(0), unknown64(0.0f), unknown68(0.0f), unknown6c(false) {
  ui::UISelectObjList::CreateParam param;
  param.allocator = getAllocator(ALLOCATOR_UNKNOWN_0);
  unknown70 = ui::UISelectObjList::create(param);
}

GfMenuObjStaffroll::~GfMenuObjStaffroll() {
  mm::mtl::safeRelease(unknown70);
  mm::mtl::safeRelease(unknown28);
}

void GfMenuObjStaffroll::initialize() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
// __LINE__ must be 107 as in the original file: it is the line argument of operator new.
#line 107
  MainListener *listener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
  listener->addRef();
  ui::UIEventManager::get()->registObjectListener(main.unknown10, listener);
  if (listener != nullptr) {
    listener->release();
  }
  attachExternalCall(unknown001, main.unknown10);
  const char *path = GfMenuManager::isRegionJP() ? "/menu/credit/endroll.crt" : "/menu/credit/endroll_us.crt";
  unknown28 = fw::CommonResource::request(ui::UIUtil::getResourceAllocator(), path, 10, false);
  GfMenuObject::initialize();
}

void GfMenuObjStaffroll::finalize() {
  if (unknown78.capacity() != 0) {
    unknown78.destroy();
  }
  GfMenuObject::finalize();
}

u32 GfMenuObjStaffroll::createText(u32 index, const CreditReader::Column &column) {
  mm::mtl::FixStr<32> name;
  const char *size;
  if (column.unknown04 < 22) {
    size = "_px20";
  } else if (column.unknown04 < 24) {
    size = "_px22";
  } else if (column.unknown04 < 28) {
    size = "_px24";
  } else {
    size = "_px28";
  }
  if (index == 1 && column.unknown08 == 0) {
    index = 3;
  }
  name.format("%s%s", unknown002[index], size);
  ui::UIObjectAcc main(unknown18, "LAY_main");
  ui::UIObjectAcc text(main.duplicateChild(name.c_str()));
  if (!text.isValid()) {
    return 0;
  }
  switch (column.unknown08) {
  case 0:
    text.setTextAlignH(0);
    break;
  case 1:
    text.setTextAlignH(1);
    break;
  case 2:
    text.setTextAlignH(2);
    break;
  }
  text.setBorderWeight(-0.5f);
  text.setSlopeRot(-12.0f);
  if (column.unknown00) {
    text.setBorderWeight(1.0f);
    text.setAddColor("white");
  }
  text.setText(ui::UIStr(column.unknown10, false));
  text.setDisp(true);
  return text.unknown10;
}

void GfMenuObjStaffroll::start(f32 time, int type) {
  ui::UIObjectAcc acc(getAttachedObject(unknown001));
  if (acc.isValid()) {
    ui::EventData event;
    event.unknown00 = GfMenuTypes::unknown003_33;
    event.unknown08_f32 = time;
    event.unknown0c = type;
    sendEvent(acc.unknown10, event, 0.0f);
  }
}

void GfMenuObjStaffroll::fadeout() { unknown144(unknown001, GfMenuTypes::unknown003_34); }

void GfMenuObjStaffroll::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(false);
    break;
  case GfMenuTypes::unknown003_33: {
    f32 time = event.unknown08_f32;
    int x = event.unknown0c;
    unknown20->unknown68 = unknown20->unknown5c / (time * 30.0f);
    unknown20->unknown58 = 2;
    mm::Pnt<s16> pos(x, 0);
    acc.setPos(pos);
    acc.setDisp(true);
    ui::UIObjectAcc grade(acc.searchSibiling("LAY_grade"));
    grade.setDisp(true);
    break;
  }
  case GfMenuTypes::unknown003_34: {
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 2;
    param.unknown00 = 2.0f;
    GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    ui::UIObjectAcc grade(acc.searchSibiling("LAY_grade"));
    grade.setDisp(false);
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf
