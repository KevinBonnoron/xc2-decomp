#include "gf/menu/object/gf_menu_obj_balloon.h"

#include <string.h>

#include "gf/data/gf_data_save.h"
#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_pos_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/call/gf_menu_call_manager.h"
#include "gf/menu/gf_menu_reference_item.h"
#include "gf/menu/gf_menu_str_linker.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_fade.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/request/gf_req_command.h"
#include "gf/request/gf_req_manager.h"
#include "mm_math/mm_pnt.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
#include "ui/event/ui_event_data.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/text/ui_tag_parser.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_str.h"
#include "ui/ui_util.h"

// Inferred role: window, text, window image, extended window image and tail layout names of the talk and select balloons; original name unknown.
static const char *const unknown003[][5] = {{"LAY_talk_win", "LAY_text", "IMG_win", "IMG_win_ex", "IMG_tail00"}, {"LAY_select_win", "LAY_text_sel", "IMG_win_sel", "IMG_win_ex_sel", "IMG_tail00_sel"}};

// Inferred role: layouts duplicated by openCommon; original name unknown.
static const char *const unknown001[] = {"LAY_talk_main", "LAY_select_main"};

// Inferred role: feeling tag value and its color; original name unknown.
struct unknown002 {
  const char *unknown00;
  const char *unknown08;
};

namespace gf {

GfMenuObjBalloon::GfMenuObjBalloon(u32 handle)
    : GfMenuObject(handle), unknown28(nullptr), unknown30(nullptr), unknown38(nullptr), unknown40(nullptr), unknown78(this), unknown1d8(false), unknown1dc(0xffffffff) {
  unknown60.assign(mm::mtl::IntrusivePtr<GfMenuReferenceItem>());
}

GfMenuObjBalloon::~GfMenuObjBalloon() {
  unknown60.assign(mm::mtl::IntrusivePtr<GfMenuReferenceItem>());
  unknown48.clear();
  mm::mtl::safeRelease(unknown40);
  mm::mtl::safeRelease(unknown38);
}

void GfMenuObjBalloon::finalize() { GfMenuObject::finalize(); }

void GfMenuObjBalloon::update() {
  unknown78.unknown003();
  GfMenuObject::update();
}

void GfMenuObjBalloon::resetFeeling(ui::UIObjectAcc &acc) { acc.setAddColor("black"); }

void GfMenuObjBalloon::setFeeling(ui::UIObjectAcc &acc, const ui::UIStr &string) {
  unknown002 feelings[] = {{"Normal", "black"}, {"Anger", "red"}, {"Think", "yellow"}};
  const char *color = "black";
  const char *kind = ui::UITagParser::get()->parseTagParam(string.c_str(), "ML:Feeling", "kind");
  if (kind != nullptr) {
    for (u32 i = 0; i < 3; i++) {
      if (strcmp(kind, feelings[i].unknown00) == 0) {
        color = feelings[i].unknown08;
        break;
      }
    }
  }
  acc.setAddColor(color);
}

u32 GfMenuObjBalloon::getFeeling(const ui::UIStr &string) {
  const char *kind = ui::UITagParser::get()->parseTagParam(string.c_str(), "ML:Feeling", "kind");
  if (kind == nullptr) {
    return 0;
  }
  if (strcmp(kind, "Normal") == 0) {
    return 0;
  }
  if (strcmp(kind, "Anger") == 0) {
    return 1;
  }
  if (strcmp(kind, "Think") == 0) {
    return 2;
  }
  return 0;
}

void GfMenuObjBalloon::setup(u32 object, GF_OBJ_HANDLE *handle, const MenuOffset &offset, bool isUpdate, u32 type, bool isAutoTalk) {
  ui::UIObjectAcc acc(object);
  {
    ui::UIObjectAcc window(acc.unknown10, unknown003[type][0]);
    if (isUpdate) {
      GfMenuPosAdapter::createWorld(window.unknown10, handle, &offset);
    } else {
      GfMenuPosAdapter *adapter = GfMenuPosAdapter::create(window.unknown10, handle, &offset);
      adapter->setPosOffsMode(1);
      adapter->setPosAdjustScreen(isAutoTalk);
    }
  }
  u32 image = 0;
  {
    ui::UIObjectAcc text(acc.unknown10, unknown003[type][1]);
    if (text.isValid()) {
      ui::UIObjectAcc win(acc.unknown10, unknown003[type][2]);
      if (win.isValid()) {
        GfMenuObjUtil::FitOption option;
        GfMenuObjUtil::createFitPlugin(win.unknown10, text.unknown10, 0x20, 0x20, option);
        image = win.unknown10;
      }
      ui::UIObjectAcc winEx(acc.unknown10, unknown003[type][3]);
      if (winEx.isValid()) {
        GfMenuObjUtil::FitOption option;
        GfMenuObjUtil::createFitPlugin(winEx.unknown10, text.unknown10, 0x20, 0x20, option);
      }
    }
  }
  if (ui::UIObjectAcc(image).isValid()) {
    ui::UIObjectAcc tail(acc.unknown10, unknown003[type][4]);
    if (tail.isValid()) {
      GfMenuObjUtil::createDockPlugin(tail.unknown10, image, 3, mm::Pnt<s16>(0x10, -0x15), 0);
    }
  }
  if (type == 0) {
    ui::UIObjectAcc cursor(acc.unknown10, "IMG_cur00");
    ui::UIObjectAcc text(acc.unknown10, "LAY_text");
    if (cursor.isValid() && text.isValid()) {
      s16 width;
      s16 height;
      cursor.getSize(true, width, height);
      GfMenuObjUtil::createDockPlugin(cursor.unknown10, text.unknown10, 7, mm::Pnt<s16>(2, -height), 0);
    }
  }
}

u32 GfMenuObjBalloon::openCommon(GfMenuCallContext *context, u32 call, GF_OBJ_HANDLE *handle, const MenuOffset &offset, u32 type, bool isAutoTalk) {
  u32 object = GfMenuObject::getAttachedObject(call);
  if (ui::UIObjectAcc(object).isValid()) {
    if (!ui::UIObjectAcc(object).isTerm()) {
      u32 child = ui::UIObjectAcc(object).duplicateChild(unknown001[type]);
      if (ui::UIObjectAcc(child).isValid()) {
        setup(child, handle, offset, false, type, isAutoTalk);
        if (context != nullptr) {
          GfMenuObject::startCallContext(context, call, child);
        }
        return child;
      }
    }
  }
  return 0;
}

bool GfMenuObjBalloon::seqSave() {
  unknown1dc = GfReqCommand::reqSave(SAVESLOT_UNKNOWN_22);
  GfMenuObjFade::dispSaving(true, 0);
  return true;
}

bool GfMenuObjBalloon::seqSaveWait() {
  if (!GfReqManager::isValid(unknown1dc)) {
    GfMenuObjFade::dispSaving(false, 0);
    unknown1dc = -1;
    ui::UIObjectAcc acc(unknown18, "LAY_select");
    GfMenuObject::addResultCallContext(acc.unknown10, 2, 0);
    return true;
  }
  return false;
}

void GfMenuObjBalloon::nextEvent(GfMenuCallContext *context, const NextParam &param) {
  if (context->isActive() && (context->unknown10 & 0xfffffffe) == 2) {
    u32 object = GfMenuObject::getAttachedObject(2);
    u32 handle = context->unknown14;
    if (ui::UIUtil::isValid(handle)) {
      GfMenuObject::nextCallContext(context, 3);
      u16 id = GfMenuObject::registString(ui::UIStr(param.unknown00, param.unknown08));
      ui::EventData event;
      event.unknown00 = 0x104;
      event.unknown08 = id;
      event.unknown14 = ui::UIObjectAcc(handle).getDuplicateIndex();
      GfMenuObject::sendEvent(object, event, 0.0f);
    }
  }
}

void GfMenuObjBalloon::close(GfMenuCallContext *context, bool isImmediate) {
  if (!context->isActive()) {
    return;
  }
  if (context->isTerm()) {
    return;
  }
  u32 object = 0;
  switch (context->unknown10) {
  case 2:
  case 3:
    object = GfMenuObject::getAttachedObject(2);
    break;
  case 4:
    object = GfMenuObject::getAttachedObject(4);
    break;
  case 5:
    object = GfMenuObject::getAttachedObject(5);
    break;
  case 7:
    object = GfMenuObject::getAttachedObject(7);
    break;
  case 8:
    object = GfMenuObject::getAttachedObject(8);
    break;
  case 9:
    object = GfMenuObject::getAttachedObject(9);
    break;
  }
  u32 handle = context->unknown14;
  if (ui::UIUtil::isValid(handle)) {
    GfMenuObject::nextCallContext(context, 6);
    ui::EventData event;
    event.unknown00 = 0x103;
    event.unknown10 = isImmediate;
    event.unknown14 = ui::UIObjectAcc(handle).getDuplicateIndex();
    GfMenuObject::sendEvent(object, event, 0.0f);
  }
}

void GfMenuObjBalloon::openEventSelectBox(GfMenuCallContext *context, const OpenSelectBoxParam &param) {
  if (context->getState() == GfMenuCallContext::STATE_UNKNOWN_0 && param.unknown18.size() != 0) {
    u32 object = GfMenuObject::getAttachedObject(7);
    u16 id = GfMenuObject::registString(ui::UIStr(param.unknown00, param.unknown08));
    for (int i = 0; i < static_cast<int>(param.unknown18.size()); i++) {
      GfMenuCallManager::get()->unknown228.addSelectString(ui::UIStr(param.unknown10, param.unknown18[i]));
    }
    if (context != nullptr) {
      GfMenuObject::startCallContext(context, 7, object);
    }
    ui::EventData event;
    event.unknown00 = 0x105;
    event.unknown08 = id;
    GfMenuObject::sendEvent(object, event, 0.0f);
    ui::UIObjectAcc(object).setSuspend(false);
  }
}

void GfMenuObjBalloon::AutoTalkListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    break;
  case GfMenuTypes::unknown003_256: {
    u32 text = event.unknown08;
    ui::UIObjectAcc talk(acc.searchDuplicatedChild("LAY_auto_talk", event.unknown14));
    if (talk.isValid()) {
      {
        ui::UIObjectAcc message(talk.unknown10, "TXT_auto_talk_msg");
        GfMenuObject::setText(message.unknown10, text);
      }
      GfMenuObjUtil::CtrlParam param;
      param.unknown08 = 0x10000000;
      param.unknown50 = "cmn_fade_emotion";
      param.unknown58 = "fade_in";
      GfMenuObjUtil::startCtrl(talk.unknown10, param, nullptr);
    }
    break;
  }
  case GfMenuTypes::unknown003_259: {
    ui::UIObjectAcc talk(acc.searchDuplicatedChild("LAY_auto_talk", event.unknown14));
    if (talk.isValid()) {
      GfMenuObjUtil::CtrlParam param;
      param.unknown08 = 0x10000000;
      param.unknown50 = "cmn_fade_emotion";
      param.unknown58 = "fade_out";
      param.unknown14 = 1;
      GfMenuObjUtil::startCtrl(talk.unknown10, param, nullptr);
      GfMenuObject::termCallContext(talk.unknown10);
    }
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjBalloon::EvSelectListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    unknown0c = 0;
    GfMenuObject::disableInput(acc.unknown10);
    break;
  case 3:
    if (event.unknown08 == 1) {
      ui::UIObjectAcc select(unknown0c);
      if (select.isValid()) {
        GfMenuObject::enableInput(acc.unknown10);
        GfMenuObjOperationInfo::open(acc.unknown10, 0, 0, 0);
        GfMenuObjOperationInfo::setGuideDisp(false);
        GfMenuObjOperationInfo::setActionEnable(acc.unknown10, 1, false);
      }
    }
    break;
  case 6: {
    u32 index = event.unknown08;
    int previous = event.unknown0c;
    ui::UIObjectAcc select(unknown0c);
    if (index == 0xffffffff) {
      select.setDispChild(false, "LAY_ev_select_cursor");
    } else {
      mm::mtl::FixStr<32> name;
      unknown20->unknown30->setIndex(index);
      if (previous != -1) {
        name.format("TXT_ev_select_msg@%02d", previous + 1);
        ui::UIObjectAcc message(select.unknown10, name.c_str());
        message.loadDefColor();
      }
      name.format("TXT_ev_select_msg@%02d", index + 1);
      ui::UIObjectAcc message(select.unknown10, name.c_str());
      GfMenuObjUtil::setColMulandAdd(message.unknown10, "txt_normal");
      select.setDispChild(true, "LAY_ev_select_cursor");
      GfMenuObjOperationInfo::setActionEnable(acc.unknown10, 1, true);
    }
    break;
  }
  case 8:
    if (event.unknown0c == 1) {
      int index = event.unknown08;
      ui::UIObjectAcc select(unknown0c);
      if (index != -1 && select.isValid()) {
        GfMenuObject::addResultCallContext(select.unknown10, 2, event.unknown08);
        GfMenuObject::disableInput(acc.unknown10);
        GfMenuObjOperationInfo::close();
        GfMenuObjUtil::playSECommonDecide();
      }
    }
    break;
  case GfMenuTypes::unknown003_256: {
    int title = event.unknown08;
    u64 params = event.unknown10_u64;
    ui::UIObjectAcc select(acc.searchDuplicatedChild("LAY_ev_select", params >> 32));
    if (select.isValid()) {
      setupEvSelect(select.unknown10, title, params);
      GfMenuObjUtil::CtrlParam param;
      param.unknown08 = 0x10000000;
      param.unknown50 = "cmn_fade_emotion";
      param.unknown58 = "fade_in";
      param.unknown04 = 1;
      int ctrl = GfMenuObjUtil::startCtrl(select.unknown10, param, nullptr);
      GfMenuObject::hookCtrlEvent(acc.unknown10, ctrl);
      GfMenuObject::disableInput(acc.unknown10);
      if (unknown20->unknown28 != nullptr) {
        unknown20->unknown28->release();
        unknown20->unknown28 = nullptr;
      }
      if (unknown20->unknown30 != nullptr) {
        unknown20->unknown30->release();
        unknown20->unknown30 = nullptr;
      }
      {
        ui::UISelectObjList::CreateParam createParam;
        createParam.allocator = getAllocator(ALLOCATOR_UNKNOWN_0);
        unknown20->unknown30 = ui::UISelectObjList::create(createParam);
      }
      unknown20->unknown30->pickupObject(select.unknown10, "LAY_ev_select_msg@%02d", 1);
      ui::UICtrlCursorSelect::CursorSetting setting;
      setting.setType(0);
      setting.unknown18 = 0;
      setting.unknown20 = false;
      unknown20->unknown28 = ui::UICtrlCursorSelect::create(select.searchChild("LAY_ev_select_cursor"), setting, unknown20->unknown30);
      GfMenuObject::setupInputSelection(acc.unknown10, -1, unknown20->unknown30->getSize());
      unknown0c = select.unknown10;
    }
    break;
  }
  case GfMenuTypes::unknown003_259: {
    ui::UIObjectAcc select(acc.searchDuplicatedChild("LAY_ev_select", event.unknown14));
    if (select.isValid()) {
      GfMenuObjUtil::CtrlParam param;
      param.unknown08 = 0x10000000;
      param.unknown50 = "cmn_fade_emotion";
      param.unknown58 = "fade_out";
      param.unknown04 = 1;
      param.unknown14 = 1;
      GfMenuObjUtil::startCtrl(select.unknown10, param, nullptr);
      if (select.unknown10 == unknown0c) {
        GfMenuObject::disableInput(acc.unknown10);
        unknown0c = 0;
      }
      GfMenuObject::termCallContext(select.unknown10);
    }
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjBalloon::openEventSelectMoney(GfMenuCallContext *context, const OpenSelectMoneyParam &param) {
  if (GfMenuObjUtil::checkCCStart(context) && param.unknown10.size() != 0) {
    u32 object = GfMenuObject::getAttachedObject(8);
    if (param.unknown00 != nullptr && param.unknown08 != 0) {
      GfMenuObject::registString(ui::UIStr(param.unknown00, param.unknown08));
    }
    if (context != nullptr) {
      GfMenuObject::startCallContext(context, 8, object);
    }
    ui::EventData event;
// __LINE__ must be 2741 as in the original file: it is the line argument of operator new.
#line 2741
    OpenSelectMoneyParam *copy = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) OpenSelectMoneyParam();
    *copy = param;
    event.unknown00 = GfMenuTypes::unknown003_33;
    event.unknown08_u64 = reinterpret_cast<u64>(copy);
    GfMenuObject::sendEvent(object, event, 0.0f);
    ui::UIObjectAcc(object).setSuspend(false);
  }
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjBalloon>(const mm::mtl::Delegate<bool()> *);
template void mm::mtl::FixedArray<mm::mtl::IntrusivePtr<gf::GfMenuReferenceItem>, 3>::assign(const mm::mtl::IntrusivePtr<gf::GfMenuReferenceItem> &);
template mm::mtl::FixedArray<mm::mtl::IntrusivePtr<gf::GfMenuReferenceItem>, 3>::~FixedArray();
