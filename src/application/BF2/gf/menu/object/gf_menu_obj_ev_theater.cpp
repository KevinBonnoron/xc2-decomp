#include "gf/menu/object/gf_menu_obj_ev_theater.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_ev_theater_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_id_list.h"
#include "gf/menu/list/gf_menu_msg_list.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/list/ui_list_info.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_str.h"

namespace gf {

// Inferred role: call id; original name unknown.
constexpr u32 unknown001 = 0x19;

// Inferred role: off screen call id; original name unknown.
constexpr u32 unknown002 = 0x1a;

GfMenuObjEvTheater::GfMenuObjEvTheater(u32 handle) : GfMenuObject(handle), unknown24(1), unknown28(nullptr), unknown30(nullptr), unknown38(nullptr), unknown40(nullptr) {
  unknown28 = GfMenuMsgList::create();
  unknown38 = GfMenuIDList::create();
}

GfMenuObjEvTheater::~GfMenuObjEvTheater() {
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown40);
  mm::mtl::safeRelease(unknown38);
}

void GfMenuObjEvTheater::initialize() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
// __LINE__ must be 134 as in the original file: it is the line argument of operator new.
#line 134
  MainListener *mainListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
  mainListener->addRef();
  ui::UIEventManager::get()->registObjectListener(main.unknown10, mainListener);
  if (mainListener != nullptr) {
    mainListener->release();
  }
  attachExternalCall(unknown001, main.unknown10);
  {
    ui::UIObjectAcc top(main.unknown10, "LAY_top");
// __LINE__ must be 145 as in the original file: it is the line argument of operator new.
#line 145
    TopListener *topListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) TopListener(this);
    topListener->addRef();
    ui::UIEventManager::get()->registObjectListener(top.unknown10, topListener);
    if (topListener != nullptr) {
      topListener->release();
    }
    setFSInputObject(0, top.unknown10);
    sendOpenEvent(top.unknown10, 0, 0.0f);
  }
  {
    ui::UIObjectAcc sub(main.unknown10, "LAY_sub");
    unknown30 = ui::UISelectObjList::create({getAllocator(ALLOCATOR_UNKNOWN_0)});
    unknown30->pickupObject(sub.unknown10, "LAY_sub_item@%02d", 1);
// __LINE__ must be 162 as in the original file: it is the line argument of operator new.
#line 162
    SubListener *subListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SubListener(this);
    subListener->addRef();
    ui::UIEventManager::get()->registObjectListener(sub.unknown10, subListener);
    if (subListener != nullptr) {
      subListener->release();
    }
    setFSInputObject(1, sub.unknown10);
  }
  {
    ui::UIObjectAcc select(main.unknown10, "LAY_select");
    mm::mtl::FixStr<32> name;
    unknown40 = ui::UISelectObjList::create({getAllocator(ALLOCATOR_UNKNOWN_0)});
    unknown40->pickupObject(select.unknown10, "LAY_select_item@%02d", 1);
    ui::UIListInfoBase::SetupParam param;
    param.unknown08 = unknown40->getSize();
    unknown38->setup(getAllocator(ALLOCATOR_UNKNOWN_0), param);
    GfMenuEvTherterAdapter::createFromList(select.searchChild("IMG_select_cur"), 1, unknown38, -1, false);
    GfMenuEvTherterAdapter::createFromList(select.searchChild("TXT_select_cur_title"), 0, unknown38, -1, false);
    for (u32 i = 0; i < unknown40->getSize(); i++) {
      name.format("IMG_select_item@%02d", i + 1);
      GfMenuEvTherterAdapter *adapter = GfMenuEvTherterAdapter::createFromList(select.searchChild(name.c_str()), 1, unknown38, i, false);
      if (adapter != nullptr) {
        name.format("LAY_select_item@%02d", i + 1);
        adapter->unknown24 = select.searchChild(name.c_str());
      }
    }
// __LINE__ must be 205 as in the original file: it is the line argument of operator new.
#line 205
    SelectListener *selectListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SelectListener(this);
    selectListener->addRef();
    ui::UIEventManager::get()->registObjectListener(select.unknown10, selectListener);
    if (selectListener != nullptr) {
      selectListener->release();
    }
    setFSInputObject(2, select.unknown10);
  }
  {
    ui::UIObjectAcc header(main.unknown10, "LAY_header");
// __LINE__ must be 215 as in the original file: it is the line argument of operator new.
#line 215
    HeaderListener *headerListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) HeaderListener(this);
    headerListener->addRef();
    ui::UIEventManager::get()->registObjectListener(header.unknown10, headerListener);
    if (headerListener != nullptr) {
      headerListener->release();
    }
  }
  disableFSInput();
  {
    ui::UIObjectAcc screen(unknown18, "LAY_mdl_view");
// __LINE__ must be 224 as in the original file: it is the line argument of operator new.
#line 224
    ScreenListener *screenListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ScreenListener(this);
    screenListener->addRef();
    ui::UIEventManager::get()->registObjectListener(screen.unknown10, screenListener);
    if (screenListener != nullptr) {
      screenListener->release();
    }
    attachExternalCall(unknown002, screen.unknown10);
  }
  GfMenuObject::initialize();
}

void GfMenuObjEvTheater::finalize() { GfMenuObject::finalize(); }

void GfMenuObjEvTheater::update() { GfMenuObject::update(); }

void GfMenuObjEvTheater::refreshSelctList() {
  u32 index = unknown38->getIndex(true);
  mm::mtl::FixStr<32> name;
  for (u32 i = 0; i < unknown40->getSize(); i++) {
    name.format("IMG_select_frame@%02d", i + 1);
    ui::UIObjectAcc frame(unknown40->getObject(i), name.c_str());
    frame.startAnimation(index == i ? "select" : "non", false);
  }
}

void GfMenuObjEvTheater::updateSubMsgList() {
  if (unknown28 != nullptr) {
    switch (unknown24) {
    case 1: {
      unknown28->setBdat(0x127, 0x102);
      u8 *bdat = unknown28->unknown68;
      {
        ui::UIListInfoBase::SetupParam param;
        param.unknown08 = unknown30->getSize();
        unknown28->setup(getAllocator(ALLOCATOR_UNKNOWN_0), param);
      }
      for (int i = 0; i < Bdat::getIdCount(bdat); i++) {
        MsgID id = {};
        id.unknown00 = Bdat::getIdTop(bdat) + i;
        unknown28->addContents(id);
      }
      break;
    }
    case 2: {
      unknown28->setBdat(0x126, 0x102);
      u8 *bdat = unknown28->unknown68;
      {
        ui::UIListInfoBase::SetupParam param;
        param.unknown08 = unknown30->getSize();
        unknown28->setup(getAllocator(ALLOCATOR_UNKNOWN_0), param);
      }
      for (int i = 0; i < Bdat::getIdCount(bdat); i++) {
        MsgID id = {};
        id.unknown00 = Bdat::getIdTop(bdat) + i;
        unknown28->addContents(id);
      }
      break;
    }
    }
    unknown28->setIndex(0);
  }
}

void GfMenuObjEvTheater::refreshSubList() {
  ui::UIStr msg;
  mm::mtl::FixStr<32> name;
  u32 index = unknown28->getIndex(true);
  for (u32 i = 0; i < unknown30->getSize(); i++) {
    ui::UIObjectAcc item(unknown30->getObject(i));
    if (i < unknown28->getSize()) {
      item.setDisp(true);
      unknown28->getMsg(i, msg, true);
      name.format("TXT_sub_item_def@%02d", i + 1);
      {
        ui::UIObjectAcc def(unknown30->getObject(i), name.c_str());
        def.setText(msg);
        def.setDisp(i != index);
      }
      name.format("TXT_sub_item_sel@%02d", i + 1);
      {
        ui::UIObjectAcc sel(unknown30->getObject(i), name.c_str());
        sel.setText(msg);
        sel.setDisp(i == index);
      }
      name.format("IMG_sub_item_base@%02d", i + 1);
      {
        ui::UIObjectAcc base(unknown30->getObject(i), name.c_str());
        base.startAnimation(i == index ? "select" : "non", false);
      }
    } else {
      item.setDisp(false);
    }
  }
}

bool GfMenuObjEvTheater::attach(GfMenuCallContext *context) { return unknown151(context, unknown001); }

void GfMenuObjEvTheater::fadein(GfMenuCallContext *context) {
  if (GfMenuObjUtil::checkCCNext(context, unknown001)) {
    ui::EventData event;
    event.unknown00 = 0x102;
    GfMenuObject::sendEvent(context->unknown14, event, 0.0f);
  }
}

void GfMenuObjEvTheater::fadeout(GfMenuCallContext *context) {
  if (GfMenuObjUtil::checkCCNext(context, unknown001)) {
    ui::EventData event;
    event.unknown00 = 0x101;
    GfMenuObject::sendEvent(context->unknown14, event, 0.0f);
  }
}

void GfMenuObjEvTheater::dispOffScreen(bool isDisp) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown002));
  if (acc.isValid()) {
    ui::EventData event;
    event.unknown00 = isDisp ? GfMenuTypes::unknown003_33 : GfMenuTypes::unknown003_34;
    GfMenuObject::sendEvent(acc.unknown10, event, 0.0f);
  }
}

void GfMenuObjEvTheater::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1: {
    ui::UIObjectAcc bg(acc.unknown10, "IMG_bg");
    bg.startAnimation("start", false);
    GfMenuObject::hookAnimationEvent(acc.unknown10, bg.unknown10);
    break;
  }
  case 2:
    GfMenuObject::termCallContext(acc.unknown10);
    acc.setTerm();
    break;
  case 3:
    if (event.unknown08 == 1) {
      GfMenuObject::enableFSInput(2);
    }
    break;
  case 0xc: {
    ui::UIObjectAcc bg(acc.unknown10, "IMG_bg");
    bg.startAnimation("loop", false);
    break;
  }
  case 0x100: {
    u32 result = event.unknown08;
    GfMenuObject::addResultCallContext(acc.unknown10, result, 0);
    break;
  }
  case GfMenuTypes::unknown003_257: {
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown00 = 6;
    param.unknown04 = 1;
    param.unknown10 = 3;
    GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
    break;
  }
  case GfMenuTypes::unknown003_258: {
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown00 = 6;
    param.unknown04 = 0;
    param.unknown10 = 1;
    GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
    if (unknown20->unknown24 == 3) {
      ui::UIObjectAcc view(acc.searchSibiling("LAY_mdl_view"));
      view.setDisp(false);
    }
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjEvTheater::TopListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    break;
  case 3:
    if (event.unknown08 == 1) {
      GfMenuObject::enableFSInput(0);
    }
    break;
  case GfMenuTypes::unknown003_33: {
    GfMenuObjUtil::CtrlParam param;
    param.unknown004("fade_in_l");
    param.unknown11 = true;
    param.unknown04 = 1;
    GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    GfMenuObject::setupInputSelection(acc.unknown10, unknown20->unknown24 - 1, 3);
    break;
  }
  case GfMenuTypes::unknown003_34: {
    GfMenuObjUtil::CtrlParam param;
    param.unknown004("fade_out_l");
    param.unknown14 = 10;
    param.unknown04 = 2;
    GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    break;
  }
  case 6: {
    u32 index = event.unknown08;
    if (index != 0xffffffff) {
      mm::mtl::FixStr<32> name;
      if (event.unknown0c != 0xffffffff) {
        u32 prev = event.unknown0c + 1;
        name.format("IMG_top_item_base@%02d", prev);
        ui::UIObjectAcc base(acc.unknown10, name.c_str());
        base.startAnimation("non", false);
        name.format("TXT_top_item_sel@%02d", prev);
        acc.setDispChild(false, name.c_str());
        name.format("TXT_top_item_def@%02d", prev);
        acc.setDispChild(true, name.c_str());
      }
      u32 current = index + 1;
      {
        name.format("IMG_top_item_base@%02d", current);
        ui::UIObjectAcc base(acc.unknown10, name.c_str());
        base.startAnimation("select", false);
        name.format("TXT_top_item_sel@%02d", current);
        acc.setDispChild(true, name.c_str());
        name.format("TXT_top_item_def@%02d", current);
        acc.setDispChild(false, name.c_str());
      }
      unknown20->unknown24 = current;
    }
    break;
  }
  case 8:
    if (event.unknown0c == 1) {
      if (unknown20->unknown24 == 1 || unknown20->unknown24 == 2) {
        unknown20->updateSubMsgList();
        GfMenuObject::sendOpenEvent(acc.searchSibiling("LAY_sub"), 0, 0.0f);
      } else {
        unknown20->updateEvthIDList();
        GfMenuObject::sendOpenEvent(acc.searchSibiling("LAY_select"), 0, 0.0f);
      }
      GfMenuObject::sendCloseEvent(acc.unknown10, 0, 0.0f);
      GfMenuObject::disableFSInput();
    } else if (event.unknown0c == 2) {
      GfMenuObject::disableFSInput();
      GfMenuObject::closeFSLayer(acc.unknown10, true, true);
    }
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjEvTheater::SubListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(false);
    break;
  case 3:
    if (event.unknown08 == 1) {
      GfMenuObject::setupInputSelectionFromList(acc.unknown10, *unknown20->unknown28);
      GfMenuObject::enableFSInput(1);
    }
    break;
  case 6:
    if (event.unknown08 != 0xffffffff) {
      unknown20->unknown28->setIndex(event.unknown08);
      unknown20->refreshSubList();
    }
    break;
  case 8:
    if (event.unknown0c == 1) {
      GfMenuObject::sendOpenEvent(acc.searchSibiling("LAY_select"), 0, 0.0f);
    } else if (event.unknown0c == 2) {
      GfMenuObject::sendCloseEvent(acc.searchSibiling("LAY_header"), 0, 0.0f);
      GfMenuObject::sendOpenEvent(acc.searchSibiling("LAY_top"), 0, 0.0f);
    } else {
      break;
    }
    GfMenuObject::sendCloseEvent(acc.unknown10, 0, 0.0f);
    GfMenuObject::disableFSInput();
    break;
  case GfMenuTypes::unknown003_33: {
    GfMenuObjUtil::CtrlParam param;
    param.unknown004("fade_in_l");
    param.unknown11 = true;
    param.unknown04 = 1;
    GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    unknown20->refreshSubList();
    acc.setDispChild(unknown20->unknown28->getSize() > unknown20->unknown30->getSize(), "LAY_sub_arrow");
    GfMenuObject::sendOpenEvent(acc.searchSibiling("LAY_header"), 0, 0.0f);
    break;
  }
  case GfMenuTypes::unknown003_34: {
    GfMenuObjUtil::CtrlParam param;
    param.unknown004("fade_out_l");
    param.unknown14 = 10;
    param.unknown04 = 2;
    GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    GfMenuObject::disableFSInput();
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjEvTheater::SelectListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(false);
    break;
  case 3:
    if (event.unknown08 == 1) {
      GfMenuObject::enableFSInput(2);
    }
    break;
  case GfMenuTypes::unknown003_33: {
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown00 = 6;
    param.unknown04 = 0;
    param.unknown10 = 1;
    GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
    unknown20->updateEvthIDList();
    GfMenuObject::setupInputSelectionFromList(acc.unknown10, *unknown20->unknown38);
    acc.setDispChild(unknown20->unknown38->getSize() > unknown20->unknown40->getSize(), "LAY_select_arrow");
    if (unknown20->unknown24 == 1 || unknown20->unknown24 == 2) {
      ui::EventData header;
      header.unknown00 = GfMenuTypes::unknown003_259;
      GfMenuObject::sendEvent(acc.searchSibiling("LAY_header"), header, 0.0f);
    } else {
      GfMenuObject::sendOpenEvent(acc.searchSibiling("LAY_header"), 0, 0.0f);
    }
    break;
  }
  case GfMenuTypes::unknown003_34: {
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown00 = 6;
    param.unknown04 = 1;
    param.unknown10 = 2;
    GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
    if (unknown20->unknown24 == 1 || unknown20->unknown24 == 2) {
      ui::EventData header;
      header.unknown00 = GfMenuTypes::unknown003_260;
      GfMenuObject::sendEvent(acc.searchSibiling("LAY_header"), header, 0.0f);
    }
    break;
  }
  case 6:
    if (event.unknown08 != 0xffffffff) {
      unknown20->unknown38->setIndex(event.unknown08);
      unknown20->refreshSelctList();
      GfMenuObjUtil::CtrlParam param;
      param.unknown08 = 1;
      param.unknown00 = 0.2f;
      GfMenuObjUtil::startCtrl(acc.unknown10, param, "IMG_select_cur");
    }
    break;
  case 8:
    if (event.unknown0c == 1) {
      u16 id = unknown20->unknown38->getContents(unknown20->unknown38->getIndex(false)).unknown00;
      u8 *bdat = GfDataBdat::getFP(BDAT_MNU_EVENT_THEATER);
      if (bdat != nullptr) {
        u16 eventId = Bdat::getVal(bdat, "event_id", id).valueU16;
        if (eventId) {
          ui::EventData result;
          result.unknown00 = GfMenuTypes::unknown003_256;
          result.unknown08 = eventId;
          GfMenuObject::sendEvent(acc.getParentHandle(), result, 0.0f);
          GfMenuObject::disableFSInput();
        }
      }
    } else if (event.unknown0c == 2) {
      if (unknown20->unknown24 == 1 || unknown20->unknown24 == 2) {
        GfMenuObject::sendOpenEvent(acc.searchSibiling("LAY_sub"), 0, 0.0f);
      } else {
        GfMenuObject::sendCloseEvent(acc.searchSibiling("LAY_header"), 0, 0.0f);
        GfMenuObject::sendOpenEvent(acc.searchSibiling("LAY_top"), 0, 0.0f);
      }
      GfMenuObject::sendCloseEvent(acc.unknown10, 0, 0.0f);
      GfMenuObject::disableFSInput();
    }
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjEvTheater::HeaderListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    unknown0c = 0;
    break;
  case GfMenuTypes::unknown003_33:
    if (unknown0c == 0) {
      GfMenuObjUtil::CtrlParam param;
      param.unknown004("fade_in_r");
      param.unknown11 = true;
      GfMenuObjUtil::startCtrl(acc.unknown10, param, "LAY_header_body");
      {
        ui::UIObjectAcc base(acc.unknown10, "IMG_header_base");
        base.startAnimation("fade_in", false);
        base.setDisp(true);
      }
      u32 count = acc.countChild("TXT_header_title@%02d", 1);
      mm::mtl::FixStr<32> name;
      for (u32 i = 0; i < count; i++) {
        name.format("TXT_header_title@%02d", i + 1);
        acc.setDispChild(i + 1 == unknown20->unknown24, name.c_str());
      }
      acc.setDispChild(false, "LAY_header_item");
      acc.setDispChild(false, "LAY_header_input");
      unknown0c = 1;
    }
    break;
  case GfMenuTypes::unknown003_34:
    if (unknown0c == 1) {
      GfMenuObjUtil::CtrlParam param;
      param.unknown004("fade_out_r");
      param.unknown14 = 10;
      param.unknown04 = 2;
      GfMenuObjUtil::startCtrl(acc.unknown10, param, "LAY_header_body");
      {
        ui::UIObjectAcc base(acc.unknown10, "IMG_header_base");
        base.startAnimation("fade_out", false);
      }
      unknown0c = 0;
    }
    break;
  case GfMenuTypes::unknown003_259: {
    ui::UIObjectAcc text(acc.unknown10, "TXT_header_item");
    ui::UIStr msg;
    unknown20->unknown28->getMsg(-1, msg, false);
    text.setText(msg);
    acc.setDispChild(true, "LAY_header_item");
    acc.setDispChild(true, "LAY_header_input");
    u32 count = acc.countChild("TXT_header_input@%02d", 1);
    mm::mtl::FixStr<32> name;
    for (u32 i = 0; i < count; i++) {
      name.format("TXT_header_input@%02d", i + 1);
      acc.setDispChild(i + 1 == unknown20->unknown24, name.c_str());
    }
    break;
  }
  case GfMenuTypes::unknown003_260:
    acc.setDispChild(false, "LAY_header_item");
    acc.setDispChild(false, "LAY_header_input");
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjEvTheater::ScreenListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    break;
  case GfMenuTypes::unknown003_33:
    acc.setDisp(true);
    break;
  case GfMenuTypes::unknown003_34:
    acc.setDisp(false);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}
} // namespace gf
