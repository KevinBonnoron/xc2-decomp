#include "gf/menu/object/gf_menu_obj_mainmenu.h"

#include "gf/game/gf_game_party.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_common_jog.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/request/gf_req_command.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/reference_object.h"
#include "types.h"
#include "ui/ctrl/ui_ctrl_object.h"
#include "ui/event/ui_event_data.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"

namespace gf {

GfMenuObjMainMenu::GfMenuObjMainMenu(u32 handle)
    : GfMenuObject(handle), unknown68(this), unknown300(nullptr), unknown308(0), unknown30c(0), unknown310(0), unknown318(nullptr), unknown320(nullptr), unknown328(0), unknown350(0xffffffff),
      unknown354(0) {}

GfMenuObjMainMenu::~GfMenuObjMainMenu() { ; }

void GfMenuObjMainMenu::finalize() {
  mm::mtl::safeRelease(unknown320);
  mm::mtl::safeRelease(unknown318);
  mm::mtl::safeRelease(unknown300);
  GfMenuObject::finalize();
}

void GfMenuObjMainMenu::update() {
  unknown68.unknown003();
  GfMenuObject::update();
}

bool GfMenuObjMainMenu::seqStartOpen() {
  unknown2f8 = -1;
  suspendInput();
  return true;
}

bool GfMenuObjMainMenu::seqAppearPhase1() {
  if (unknown2f8 == -1) {
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 1;
    param.unknown00 = 0.25f;
    ui::UIObjectAcc acc(unknown18);
    unknown2f8 = GfMenuObjUtil::startCtrl(acc.searchChild("IMG_bg"), param, nullptr);
  }
  if (GfMenuObjUtil::isBusyCtrl(unknown2f8)) {
    return false;
  }
  unknown2f8 = -1;
  return true;
}

bool GfMenuObjMainMenu::seqAppearPhase2() {
  if (unknown2f8 == -1) {
    ui::UIObjectAcc acc(unknown18, "LAY_title");
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown10 = 0;
    param.unknown00 = 1;
    param.unknown04 = 0;
    unknown2f8 = GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
  }
  if (GfMenuObjUtil::isBusyCtrl(unknown2f8)) {
    return false;
  }
  unknown2f8 = -1;
  return true;
}

bool GfMenuObjMainMenu::seqAppearPhase3() {
  if (unknown300 == nullptr) {
    ui::UIObjectAcc acc(unknown18, "LAY_main");
    GfMenuObjCommonJog::OpenParam param;
    if (unknown300 == nullptr) {
      unknown300 = GfMenuCallContext::create();
    }
    GfMenuTypes::Param layerParam;
    if (getFSLayerParam(unknown20, layerParam)) {
      param.unknown04 = layerParam.get<unknown001>().unknown00;
      removeFSLayerParam(unknown20);
    }
    param.unknown00 = 1;
    GfMenuObjCommonJog::open(unknown300, param);
    GfMenuObject::setCallContextEventHandler(unknown300, acc.unknown10);
  }
  GfMenuCallContext::GfMenuResult result;
  return !unknown300->unknown18.empty() && unknown300->popResult(result) && result.unknown04 == 0;
}

bool GfMenuObjMainMenu::seqAppearPhase4() {
  if (unknown2f8 == -1) {
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 1;
    param.unknown00 = 0.25f;
    ui::UIObjectAcc acc(unknown18);
    unknown2f8 = GfMenuObjUtil::startCtrl(acc.searchChild("LAY_info_top"), param, nullptr);
  }
  if (GfMenuObjUtil::isBusyCtrl(unknown2f8)) {
    return false;
  }
  unknown2f8 = -1;
  return true;
}

bool GfMenuObjMainMenu::seqEndCommon() {
  resumeInput();
  return true;
}

void GfMenuObjMainMenu::suspendInput() {
  ui::UIObjectAcc acc(unknown18, "LAY_main");
  GfMenuObject::disableInput(acc.unknown10);
  GfMenuObject::disableFSSwitching();
  if (unknown300 != nullptr) {
    GfMenuObjCommonJog::disable(unknown300);
  }
}

void GfMenuObjMainMenu::resumeInput() {
  ui::UIObjectAcc acc(unknown18, "LAY_main");
  GfMenuObject::enableInput(acc.unknown10);
  GfMenuObject::enableFSSwitching();
  if (unknown300 != nullptr) {
    GfMenuObjCommonJog::enable(unknown300);
  }
}

bool GfMenuObjMainMenu::seqStartCommon() {
  suspendInput();
  return true;
}

bool GfMenuObjMainMenu::seqCloseJog() {
  if (unknown300 != nullptr) {
    GfMenuObjCommonJog::close(unknown300);
  }
  GfMenuCallContext::GfMenuResult result;
  if (!unknown300->unknown18.empty() && unknown300->popResult(result) && result.unknown04 == 1) {
    unknown300->reset();
    return true;
  }
  return false;
}

bool GfMenuObjMainMenu::seqOpenJog() {
  if (!unknown300->isActive()) {
    ui::UIObjectAcc acc(unknown18, "LAY_main");
    GfMenuObjCommonJog::OpenParam param;
    param.unknown00 = unknown310;
    GfMenuObjCommonJog::open(unknown300, param);
    GfMenuObject::setCallContextEventHandler(unknown300, acc.unknown10);
  }
  GfMenuCallContext::GfMenuResult result;
  return !unknown300->unknown18.empty() && unknown300->popResult(result) && result.unknown04 == 0;
}

bool GfMenuObjMainMenu::seqSwapPhase2() { return true; }

void GfMenuObjMainMenu::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    unknown20->unknown68.unknown005();
    unknown20->unknown68.unknown002(&GfMenuObjMainMenu::seqStartOpen);
    unknown20->unknown68.unknown002(&GfMenuObjMainMenu::seqAppearPhase1);
    unknown20->unknown68.unknown002(&GfMenuObjMainMenu::seqAppearPhase2);
    unknown20->unknown68.unknown002(&GfMenuObjMainMenu::seqAppearPhase3);
    unknown20->unknown68.unknown002(&GfMenuObjMainMenu::seqAppearPhase4);
    unknown20->unknown68.unknown002(&GfMenuObjMainMenu::seqEndCommon);
    break;
  case 2: {
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 2;
    param.unknown00 = 0.5f;
    param.unknown14 = 1;
    GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    RQ_SETUP_PARTY party;
    u32 index = unknown20->unknown320->getIndex(false);
    u32 size = unknown20->unknown320->getSize();
    bool isRotated;
    if (index == 0) {
      GfGameParty::getCurrentPartyInfo(party);
      isRotated = false;
    } else {
      RQ_SETUP_PARTY current;
      GfGameParty::getCurrentPartyInfo(current);
      for (u32 i = 0; i < size; i++) {
        u32 source = index + i;
        if (source >= size) {
          source -= size;
        }
        party.unknown00[i] = current.unknown00[source];
        if (i == 0) {
          party.unknowncc = current.unknown00[source].unknown00;
          party.unknownc8 = 3;
        }
      }
      isRotated = true;
    }
    if (unknown20->unknown330[index] == 1) {
      party.unknowncc = party.unknown00[0].unknown08[0];
      party.unknownc8 = 4;
    } else if (!isRotated) {
      break;
    }
    GfReqCommand::reqChangeParty(party);
    break;
  }
  case 6: {
    u32 index = event.unknown08;
    unknown20->unknown328 = unknown20->unknown320->getSelectObject();
    unknown20->unknown320->setIndex(index);
    break;
  }
  case 8: {
    u64 param = event.unknown08_u64;
    int type = param >> 32;
    int index = param;
    if (type == 9) {
      if (index != -1 && GfMenuObjUtil::isBladeContorolable(index, 0)) {
        unknown20->setBustupCtrlChar(index, unknown20->unknown330[index] ^ 1, true);
      }
    } else if (type == 2) {
      if (unknown20->unknown30c == 0) {
        GfMenuObject::closeFSLayer(acc.unknown10, true, true);
      } else {
        GfMenuObjCommonJog::pop(unknown20->unknown300);
      }
    } else if (type == 10) {
      GfMenuObject::changeFSSubLayer(acc.unknown10, 1, 0x1b, true);
    }
    GfMenuObjUtil::playSECommonFromInput(event.unknown0c);
    break;
  }
  case 0xe:
    if (ui::UICtrlObject::getEventCtrlObjID(event) == 1) {
      unknown20->listenerPartySelect(event);
    }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  case 0x41: {
    if (unknown20->unknown300 == nullptr || unknown20->unknown300->unknown0c != event.unknown08) {
      break;
    }
    u16 value = event.unknown14_u16;
    switch (event.unknown10_u16) {
    case 2:
      if (unknown20->unknown30c == 0) {
        GfMenuTypes::Param layerParam;
        unknown001 layer;
        layer.unknown00 = value;
        layerParam.set(layer);
        GfMenuObject::registFSLayerParam(unknown20->unknown20, layerParam);
      }
      break;
    case 3:
      GfMenuObject::changeFSSubLayer(acc.unknown10, 1, value, true);
      break;
    case 4:
      unknown20->unknown30c = value;
      unknown20->suspendInput();
      break;
    case 5:
      unknown20->unknown30c = value;
      unknown20->resumeInput();
      break;
    }
    break;
  }
  }
}

} // namespace gf
