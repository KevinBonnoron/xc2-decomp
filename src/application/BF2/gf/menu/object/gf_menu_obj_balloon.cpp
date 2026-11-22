#include "gf/menu/object/gf_menu_obj_balloon.h"

#include <string.h>

#include "gf/data/gf_data_save.h"
#include "gf/data/gf_data_util.h"
#include "gf/data/gf_object_type.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_party.h"
#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_pos_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/call/gf_menu_call_manager.h"
#include "gf/menu/gf_menu_manager.h"
#include "gf/menu/gf_menu_reference_item.h"
#include "gf/menu/gf_menu_str_linker.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_fade.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/request/gf_req_command.h"
#include "gf/request/gf_req_manager.h"
#include "gf/request/gf_req_scom.h"
#include "mm_math/mm_col3.h"
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

int GfMenuObjBalloon::setupEvTalk(u32 handle, int text, int name) {
  ui::UIObjectAcc acc(handle);
  u32 feeling;
  {
    ui::UIObjectAcc message(acc.unknown10, "TXT_ev_talk_msg");
    if (message.isValid()) {
      ui::UIStr string(GfMenuObject::getString(text));
      feeling = getFeeling(string);
      message.setText(string);
      GfMenuObject::releaseString(text);
    } else {
      feeling = 0;
    }
  }
  {
    ui::UIObjectAcc layout(acc.unknown10, "LAY_ev_talk_msg");
    layout.updateLayoutSize();
  }
  if (name != -1) {
    ui::UIObjectAcc title(acc.unknown10, "TXT_ev_talk_name");
    if (title.isValid()) {
      GfMenuObject::setText(title.unknown10, name);
    }
  }
  {
    mm::mtl::FixStr<32> image;
    for (int i = 0; i < 3; i++) {
      image.format("IMG_ev_talk_win@%02d", i + 1);
      acc.setDispChild(feeling == i, image.c_str());
      image.format("IMG_ev_talk_arrow@%02d", i + 1);
      acc.setDispChild(feeling == i, image.c_str());
      image.format("IMG_ev_talk_arrow_sh@%02d", i + 1);
      acc.setDispChild(feeling == i, image.c_str());
    }
  }
  ui::UIObjectAcc(acc.unknown10, "IMG_ev_talk_cursor").setMulColor(mm::Col3(144 / 255.0f, 150 / 255.0f, 178 / 255.0f));
  acc.updateLayoutSize();
  return feeling;
}

void GfMenuObjBalloon::setupEvSelect(u32 handle, int title, int name) {
  ui::UIObjectAcc acc(handle);
  {
    ui::UIObjectAcc message(acc.unknown10, "TXT_ev_select_msg_title");
    if (message.isValid()) {
      GfMenuObject::setText(message.unknown10, title);
    }
  }
  if (name != -1) {
    ui::UIObjectAcc text(acc.unknown10, "TXT_ev_select_name");
    if (text.isValid()) {
      GfMenuObject::setText(text.unknown10, name);
    }
  }
  GfMenuStrLinker &linker = GfMenuCallManager::get()->m_menuStrLinker;
  mm::mtl::FixStr<32> layout;
  for (int i = 0; i < 2; i++) {
    layout.format("TXT_ev_select_msg@%02d", i + 1);
    ui::UIObjectAcc item(acc.searchChild(layout.c_str()));
    if (item.isValid()) {
      layout.format("LAY_ev_select_msg@%02d", i + 1);
      int count = linker.unknowne18.size();
      if (i < count) {
        item.setText(linker.unknowne18[i]);
        acc.setDispChild(true, layout.c_str());
      } else {
        acc.setDispChild(false, layout.c_str());
      }
    }
  }
  linker.clearSelectString();
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
      GfMenuCallManager::get()->m_menuStrLinker.addSelectString(ui::UIStr(param.unknown10, param.unknown18[i]));
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

void GfMenuObjBalloon::openEvent(GfMenuCallContext *context, const OpenParam &param) {
  if (context->getState() == GfMenuCallContext::STATE_UNKNOWN_0) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(2));
    ui::UIObjectAcc talk(acc.duplicateChild("LAY_ev_talk"));
    if (talk.isValid()) {
      GfMenuPosAdapter *adapter = GfMenuPosAdapter::create(talk.searchChild("LAY_ev_talk_main"), param.m_GF_OBJ_HANDLE, &param.m_menuOffset);
      adapter->setPosOffsMode(1);
      adapter->unknown84 = mm::Pnt<s16>(0x20, -0x20);
      adapter->setPosAdjustSizeOffs(-0x40, -0x20);
      adapter->setPosAdjustScreen(true);
      GfMenuPosAdapter::createDiffOffset(talk.searchChild("LAY_ev_talk_arrow"), param.m_GF_OBJ_HANDLE, &param.m_menuOffset, 0x60, 0);
      GfMenuObjUtil::createDockPlugin(talk.searchChild("LAY_ev_talk_arrow"), talk.searchChild("LAY_ev_talk_main"), 3, mm::Pnt<s16>(0, -0x23), 0);
      GfMenuObjUtil::createSyncPlugin(talk.searchChild("LAY_ev_talk_arrow_sh"), talk.searchChild("LAY_ev_talk_arrow"), 0x3e);
      {
        mm::mtl::FixStr<32> name;
        GfMenuObjUtil::FitOption option;
        option.unknown00 = true;
        option.unknown08.x = 0x1c2;
        for (int i = 1; i <= 3; i++) {
          name.format("IMG_ev_talk_win@%02d", i);
          ui::UIObjectAcc window(talk.unknown10, name.c_str());
          GfMenuObjUtil::createFitPlugin(window.unknown10, talk.searchChild("LAY_ev_talk_msg"), 0, 0, option);
        }
        GfMenuObjUtil::createDockPlugin(talk.searchChild("IMG_ev_talk_cursor"), talk.searchChild("LAY_ev_talk_msg"), 3, mm::Pnt<s16>(0, 0), 0);
        // The game keeps both fit options in one stack slot (sp+40) while the name string and the window handles use others: one variable, reset
        // (stores 0x71003ef550 to 0x71003ef55c: byte 1, the two zero words, byte 2, byte 0) rather than a second one in a sibling scope.
        option = GfMenuObjUtil::FitOption();
        option.unknown02 = true;
        option.unknown00 = true;
        GfMenuObjUtil::createFitPlugin(talk.searchChild("IMG_ev_talk_name_base"), talk.searchChild("TXT_ev_talk_name"), 0, 0, option);
        {
          ui::UIObjectAcc nameLayer(talk.unknown10, "LAY_ev_talk_name");
          s16 width;
          s16 height;
          nameLayer.getSize(false, width, height);
          // The two lookups are locals so that the game's order holds (0x71003ef5dc): both searchChild calls, then x and y of the offset loaded and
          // stored one after the other; the Pnt temporary of the call loads both values first.
          u32 target = talk.searchChild("LAY_ev_talk_name");
          u32 dock = talk.searchChild("LAY_ev_talk_win");
          mm::Pnt<s16> offset;
          offset.x = width;
          offset.y = height;
          GfMenuObjUtil::createDockPlugin(target, dock, 4, offset, 0);
        }
      }
      u32 nameId = 0xffffffff;
      if (param.unknown10 != nullptr && param.unknown18 != 0) {
        nameId = GfMenuObject::registString(ui::UIStr(param.unknown10, param.unknown18));
        if (GfGameParty::getPartyId(param.m_GF_OBJ_HANDLE) == PARTY_UNKNOWN_4294967295) {
          if (GfGameManager::isEvent(false)) {
            GfObjAcc objAcc(param.m_GF_OBJ_HANDLE);
            // The game calls getType (0x71003ef664), tests it against 3 (0x71003ef668), calls getType again when it differs (0x71003ef674) and uses neither
            // result nor anything after it: statement without effect that the game holds (ruling 5, P3).
            if (objAcc.getType() != OBJECT_TYPE_PC) {
              objAcc.getType();
            }
          }
          ui::UIObjectAcc base(talk.unknown10, "IMG_ev_talk_name_base");
          base.setMulColor("green");
        }
      }
      u32 textId = 0xffffffff;
      if (param.unknown00 != nullptr && param.unknown08 != 0) {
        textId = GfMenuObject::registString(ui::UIStr(param.unknown00, param.unknown08));
      }
      ui::EventData event;
      event.unknown00 = GfMenuTypes::unknown003_256;
      event.unknown08 = textId;
      event.unknown0c = 0;
      event.unknown10 = nameId;
      event.unknown14 = talk.getDuplicateIndex();
      GfMenuObject::sendEvent(acc.unknown10, event, 0.0f);
      GfMenuObject::startCallContext(context, 2, talk.unknown10);
    }
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
      m_menuObjBalloon->unknown30->setIndex(index);
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
      if (m_menuObjBalloon->unknown28 != nullptr) {
        m_menuObjBalloon->unknown28->release();
        m_menuObjBalloon->unknown28 = nullptr;
      }
      if (m_menuObjBalloon->unknown30 != nullptr) {
        m_menuObjBalloon->unknown30->release();
        m_menuObjBalloon->unknown30 = nullptr;
      }
      {
        ui::UISelectObjList::CreateParam createParam;
        createParam.allocator = getAllocator(ALLOCATOR_UNKNOWN_0);
        m_menuObjBalloon->unknown30 = ui::UISelectObjList::create(createParam);
      }
      m_menuObjBalloon->unknown30->pickupObject(select.unknown10, "LAY_ev_select_msg@%02d", 1);
      ui::UICtrlCursorSelect::CursorSetting setting;
      setting.setType(0);
      setting.unknown18 = 0;
      setting.unknown20 = false;
      m_menuObjBalloon->unknown28 = ui::UICtrlCursorSelect::create(select.searchChild("LAY_ev_select_cursor"), setting, m_menuObjBalloon->unknown30);
      GfMenuObject::setupInputSelection(acc.unknown10, -1, m_menuObjBalloon->unknown30->getSize());
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

// Inferred helper: shows the object and starts its fade out control; original name unknown. Evidence: the game repeats this block in
// SelMoneyListener::reciveEvent (0x71003ed7b4) for case 8 and for the end event 0x103, and in BoxListener::reciveEvent (0x71003ed0b8)
// for 0x103 (0x71003ed544); its CtrlParam slot sits below the object accessor like an allocation of an inlined callee.
static void unknown004(u32 handle) {
  ui::UIObjectAcc root(handle);
  root.setDisp(true);
  GfMenuObjUtil::CtrlParam param;
  param.unknown00 = 0.25f;
  param.unknown04 = 2;
  param.unknown08 = 2;
  GfMenuObjUtil::startCtrl(root.unknown10, param, nullptr);
}

// Inferred helper: shows the object and starts its fade in control from half alpha; original name unknown. Evidence: the same block
// is in the game's BoxListener::reciveEvent (0x71003ed0b8, event 0x105) and SelMoneyListener::reciveEvent (0x71003ed7b4, start event).
static void unknown005(u32 handle) {
  ui::UIObjectAcc root(handle);
  root.setDisp(true);
  GfMenuObjUtil::CtrlParam param;
  param.unknown00 = 0.25f;
  param.unknown08 = 1;
  root.setAlpha(0.5f);
  param.unknown3c = 1.0f;
  param.unknown04 = 1;
  GfMenuObjUtil::startCtrl(root.unknown10, param, nullptr);
}

void GfMenuObjBalloon::BoxListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    GfMenuObject::disableInput(acc.unknown10);
    acc.setDisp(false);
    acc.setSuspend(true);
    break;
  case 3:
    // Written out in EvSelectListener, here and in SelMoneyListener alike (the game repeats the enable input / operation info block): a shared helper changes the string pool addresses of
    // the three functions (first difference at 0x71003ed100, 0x71003eedc8 and 0x71003ed800).
    if (event.unknown08 == 1) {
      GfMenuObject::enableInput(acc.unknown10);
      GfMenuObjOperationInfo::open(acc.unknown10, 0, 0, 0);
      GfMenuObjOperationInfo::setGuideDisp(false);
      GfMenuObjOperationInfo::setActionEnable(acc.unknown10, 1, false);
    } else if (event.unknown08 == 2) {
      GfMenuObject::termCallContext(acc.unknown10);
      acc.setSuspend(true);
    }
    break;
  case 4:
    if (event.unknown08 != -1) {
      if (GfMenuManager::getLatestCommonWinID() == 0xe0 && GfDataUtil::getScenarioFlag() > 10000 && ((GfDataUtil::getScenarioFlag() >> 6) & 0x3ff) < 0x9d && event.unknown08 == 0) {
        m_menuObjBalloon->unknown78.unknown005();
        m_menuObjBalloon->unknown78.unknown002(&GfMenuObjBalloon::seqSave);
        m_menuObjBalloon->unknown78.unknown002(&GfMenuObjBalloon::seqSaveWait);
        GfMenuObject::disableInput(acc.unknown10);
        GfMenuObjUtil::playSECommonDecide();
      } else {
        GfMenuObject::addResultCallContext(acc.unknown10, 2, event.unknown08);
        GfMenuObjUtil::playSECommonDecide();
      }
    }
    break;
  case 6: {
    u32 index = event.unknown08;
    if (index == 0xffffffff) {
      acc.setDispChild(false, "LAY_select_cursor");
      break;
    }
    u32 previous = event.unknown0c;
    mm::mtl::FixStr<32> name;
    if (previous != 0xffffffff) {
      name.format("TXT_sel_item@%02d", previous + 1);
      ui::UIObjectAcc item(m_menuObjBalloon->unknown38->getObject(previous), name.c_str());
      item.loadDefColor();
    }
    m_menuObjBalloon->unknown38->setIndex(index);
    name.format("TXT_sel_item@%02d", index + 1);
    {
      ui::UIObjectAcc item(m_menuObjBalloon->unknown38->getSelectObject(), name.c_str());
      GfMenuObjUtil::setColMulandAdd(item.unknown10, "txt_normal");
      // The game writes the cursor docking out in full (0x71003ed650, 0x71003ed68c); see the note in SelMoneyListener::reciveEvent.
      GfMenuObjUtil::setDockPos(acc.searchChild("IMG_select_cursor_l"), item.unknown10, 1, true);
      GfMenuObjUtil::addPos(acc.searchChild("IMG_select_cursor_l"), -10, 0);
      GfMenuObjUtil::setDockPos(acc.searchChild("IMG_select_cursor_r"), item.unknown10, 2, true);
      GfMenuObjUtil::addPos(acc.searchChild("IMG_select_cursor_r"), 10, 0);
    }
    acc.setDispChild(true, "LAY_select_cursor");
    GfMenuObjUtil::playSECommonCursor();
    GfMenuObjOperationInfo::setActionEnable(acc.unknown10, 1, true);
    break;
  }
  case GfMenuTypes::unknown003_259:
    unknown004(acc.unknown10);
    GfMenuObject::disableInput(acc.unknown10);
    GfMenuObjOperationInfo::close();
    break;
  case 0x105: {
    unknown005(acc.unknown10);
    GfMenuObject::setText(acc.searchChild("TXT_sel_title"), event.unknown08);
    GfMenuStrLinker &linker = GfMenuCallManager::get()->m_menuStrLinker;
    mm::mtl::FixStr<32> name;
    for (int i = 0; i < 3; i++) {
      name.format("TXT_sel_item@%02d", i + 1);
      ui::UIObjectAcc item(m_menuObjBalloon->unknown38->getObject(i), name.c_str());
      if (item.isValid()) {
        int count = linker.unknowne18.size();
        if (i < count) {
          item.setText(linker.unknowne18[i]);
          item.loadDefColor();
        }
        ui::UIObjectAcc(m_menuObjBalloon->unknown38->getObject(i)).setDisp(i < count);
        if (i > 0) {
          mm::mtl::FixStr<32> accent;
          accent.format("IMG_sel_item_accent@%02d", i);
          acc.setDispChild(i < count, accent.c_str());
        }
      }
    }
    GfMenuObject::setupInputSelection(handle, -1, linker.unknowne18.size());
    linker.clearSelectString();
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjBalloon::SelMoneyListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    GfMenuObject::disableInput(acc.unknown10);
    unknown0c = 0;
    acc.setDisp(false);
    acc.setSuspend(true);
    break;
  case 3:
    if (event.unknown08 == 1) {
      GfMenuObject::enableInput(acc.unknown10);
      GfMenuObjOperationInfo::open(acc.unknown10, 0, 0, 0);
      GfMenuObjOperationInfo::setGuideDisp(false);
      GfMenuObjOperationInfo::setActionEnable(acc.unknown10, 1, false);
    } else if (event.unknown08 == 2) {
      GfMenuObject::termCallContext(acc.unknown10);
      acc.setSuspend(true);
    }
    break;
  case 6: {
    u64 pair = event.unknown08_u64;
    int index = pair;
    if (index == -1) {
      acc.setDispChild(false, "LAY_select_money_cursor");
      break;
    }
    mm::mtl::FixStr<32> name;
    int previous = pair >> 32;
    if (previous != -1) {
      name.format("TXT_sel_money_item@%02d", previous + 1);
      ui::UIObjectAcc item(m_menuObjBalloon->unknown40->getObject(previous), name.c_str());
      if (m_menuObjBalloon->unknown48.size() == previous || GfDataUtil::getMoney() >= m_menuObjBalloon->unknown48[previous]) {
        item.loadDefColor();
      }
    }
    m_menuObjBalloon->unknown40->setIndex(index);
    name.format("TXT_sel_money_item@%02d", index + 1);
    {
      ui::UIObjectAcc item(m_menuObjBalloon->unknown40->getSelectObject(), name.c_str());
      if (m_menuObjBalloon->unknown48.size() == index || GfDataUtil::getMoney() >= m_menuObjBalloon->unknown48[index]) {
        GfMenuObjUtil::setColMulandAdd(item.unknown10, "txt_normal");
      }
      // Written out as in BoxListener::reciveEvent: the game repeats the four calls (0x71003edf90 and 0x71003edfcc here, 0x71003ed650 and 0x71003ed68c there), as GfMenuObjCommonText's
      // listeners do. A shared helper taking the item and the two layer names gives one instruction more in each function (403 against 402, 585 against 584).
      GfMenuObjUtil::setDockPos(acc.searchChild("IMG_select_money_cursor_l"), item.unknown10, 1, true);
      GfMenuObjUtil::addPos(acc.searchChild("IMG_select_money_cursor_l"), -10, 0);
      GfMenuObjUtil::setDockPos(acc.searchChild("IMG_select_money_cursor_r"), item.unknown10, 2, true);
      GfMenuObjUtil::addPos(acc.searchChild("IMG_select_money_cursor_r"), 10, 0);
    }
    acc.setDispChild(true, "LAY_select_money_cursor");
    GfMenuObjUtil::playSECommonCursor();
    GfMenuObjOperationInfo::setActionEnable(acc.unknown10, 1, true);
    break;
  }
  case 8: {
    u64 pair = event.unknown08_u64;
    int index = pair;
    int kind = pair >> 32;
    if (kind != 2) {
      if (kind != 1) {
        break;
      }
      if (index == -1) {
        break;
      }
      if (unknown0c != index) {
        if (index >= m_menuObjBalloon->unknown48.size()) {
          break;
        }
        int money = m_menuObjBalloon->unknown48[index];
        if (money > static_cast<int>(GfDataUtil::getMoney())) {
          GfMenuObjUtil::playSECommon(2);
          break;
        }
        GfMenuObject::addResultCallContext(acc.unknown10, 3, money);
        SCOM_ADD_MONEY::create(-money);
      }
      GfMenuObjUtil::playSECommonDecide();
    }
    unknown004(acc.unknown10);
    GfMenuObject::disableInput(acc.unknown10);
    GfMenuObjOperationInfo::close();
    break;
  }
  case GfMenuTypes::unknown003_33: {
    // The sender (openEventSelectMoney) stores the pointer of the copied parameter in the 64-bit view of the first two slots. The EventData has no pointer view, so the cast is
    // the one GfMenuObjQuestReward::RewardListener::reciveEvent already uses for its OpenParam; a pointer member in ui::EventData would remove it.
    OpenSelectMoneyParam *param = reinterpret_cast<OpenSelectMoneyParam *>(event.unknown08_u64);
    int cancel = param->unknown10.size();
    if (param->unknown08 == 0 || param->unknown00 == nullptr) {
      acc.setDispChild(false, "TXT_sel_money_title");
    } else {
      ui::UIObjectAcc title(acc.unknown10, "TXT_sel_money_title");
      title.setText(ui::UIStr(param->unknown00, param->unknown08));
      title.setDisp(true);
    }
    // Scope (ruling 3, no destructor): in the game the string slot is the CtrlParam slot shared with the unknown004 and unknown005 blocks
    // (sp+160); without the scope the string gets its own slot (the frame moves by 24 bytes, measured).
    {
      mm::mtl::FixStr<32> name;
      for (u32 i = 0; i < m_menuObjBalloon->unknown40->getSize(); i++) {
        name.format("LAY_sel_money_item@%02d", i + 1);
        ui::UIObjectAcc layout(acc.unknown10, name.c_str());
        name.format("TXT_sel_money_item@%02d", i + 1);
        ui::UIObjectAcc text(acc.unknown10, name.c_str());
        bool isItem = i < param->unknown10.size();
        if (isItem) {
          u32 money = param->unknown10[i];
          if (money != 0) {
            if (money > GfDataUtil::getMoney()) {
              text.setAddColor("txt_disable_add");
              text.setMulColor("mer_cond_ng2");
            } else {
              text.loadDefColor();
            }
          }
          if (i < param->unknown28.size()) {
            text.setText(ui::UIStr(param->unknown00, param->unknown28[i]));
          } else {
            mm::mtl::FixStr<32> amount;
            amount.format("%dG", money);
            text.setText(ui::UIStr(amount.c_str(), true));
          }
        }
        layout.setDisp(isItem);
        if (i != 0) {
          name.format("IMG_sel_money_item_accent@%02d", i);
          acc.setDispChild(isItem, name.c_str());
        }
      }
      {
        u32 last = param->unknown10.size();
        name.format("LAY_sel_money_item@%02d", last + 1);
        ui::UIObjectAcc layout(acc.unknown10, name.c_str());
        name.format("TXT_sel_money_item@%02d", last + 1);
        ui::UIObjectAcc text(acc.unknown10, name.c_str());
        layout.setDisp(true);
        if (param->unknown0c == 0) {
          text.setText(ui::UIStr("cancel", false));
        } else {
          text.setText(ui::UIStr(param->unknown00, param->unknown0c));
        }
        text.loadDefColor();
        name.format("IMG_sel_money_item_accent@%02d", last);
        acc.setDispChild(true, name.c_str());
        unknown0c = cancel;
      }
    }
    m_menuObjBalloon->unknown48 = param->unknown10;
    GfMenuObject::setupInputSelection(handle, -1, cancel + 1);
    unknown005(handle);
    delete param;
    break;
  }
  case GfMenuTypes::unknown003_259:
    unknown004(acc.unknown10);
    GfMenuObject::disableInput(acc.unknown10);
    break;
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
