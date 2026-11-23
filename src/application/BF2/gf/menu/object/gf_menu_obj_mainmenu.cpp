#include "gf/menu/object/gf_menu_obj_mainmenu.h"

#include "gf/game/gf_game_party.h"
#include "gf/menu/adapter/gf_menu_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_common_jog.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/request/gf_req_command.h"
#include "mm_math/mm_col3.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "mm_math/mm_vec2.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/reference_object.h"
#include "types.h"
#include "ui/ctrl/ui_ctrl_object.h"
#include "ui/event/ui_event_data.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: multiply color of the bustup that is behind; original name unknown. The game reads it by address in setBustupCtrlChar (0x7100f706d4).
static const mm::Col3 unknown002(0.5f, 0.5f, 0.5f);

GfMenuObjMainMenu::GfMenuObjMainMenu(u32 handle)
    : GfMenuObject(handle), unknown68(this), m_menuCallContext(nullptr), unknown308(0), unknown30c(0), unknown310(0), unknown318(nullptr), unknown320(nullptr), unknown328(0), unknown350(-1),
      unknown354(0) {}

GfMenuObjMainMenu::~GfMenuObjMainMenu() { ; }

void GfMenuObjMainMenu::setBustupCtrlChar(u32 character, u32 flag, bool isDisp) {
  if (isDisp) {
    unknown350 = character;
    unknown354 = flag;
    unknown68.unknown005();
    unknown68.unknown002(&GfMenuObjMainMenu::seqStartCommon);
    unknown68.unknown002(&GfMenuObjMainMenu::seqSwapPhase1);
    unknown68.unknown002(&GfMenuObjMainMenu::seqSwapPhase2);
    unknown68.unknown002(&GfMenuObjMainMenu::seqEndCommon);
  } else {
    ui::UIObjectAcc acc(unknown320->getObject(character));
    if (acc.isValid()) {
      ui::UIObjectAcc driver(acc.unknown10, "IMG_bustup_dr");
      ui::UIObjectAcc blade(acc.unknown10, "IMG_bustup_bl");
      mm::Rect<s16> driverRect;
      mm::Rect<s16> bladeRect;
      acc.getLayoutRect("bustup_dr", driverRect);
      acc.getLayoutRect("bustup_bl", bladeRect);
      if (flag == 0) {
        driver.setScale(mm::Vec2(1.0f, 1.0f));
        driver.setPos(mm::Pnt<s16>(driverRect.unknown00));
        driver.setMulColor(mm::Col3(1.0f, 1.0f, 1.0f));
        driver.setDispPriority(9);
        s16 y = bladeRect.y + 0x28; // Places the load of y before the one of x (0x7100482b5c): the game loads the two halves apart, y first, never as one word.
        blade.setPos(mm::Pnt<s16>(bladeRect.x, y));
        blade.setScale(mm::Vec2(0.85f, 0.85f));
        blade.setMulColor(unknown002);
        blade.setDispPriority(8);
      } else {
        blade.setScale(mm::Vec2(1.0f, 1.0f));
        blade.setPos(mm::Pnt<s16>(bladeRect.unknown00));
        blade.setMulColor(mm::Col3(1.0f, 1.0f, 1.0f));
        blade.setDispPriority(9);
        s16 y = driverRect.y + 0x28; // Places the load of y before the one of x (0x7100482c04): the game loads the two halves apart, y first, never as one word.
        driver.setPos(mm::Pnt<s16>(driverRect.x, y));
        driver.setScale(mm::Vec2(0.85f, 0.85f));
        driver.setMulColor(unknown002);
        driver.setDispPriority(8);
      }
      if (unknown348 != nullptr) {
        if (flag == 0) {
          unknown348->changeCharData(3, GfGameParty::getDriverBdatId(character));
        } else {
          unknown348->changeCharData(4, GfGameParty::getBladeBdatId(character, -1));
        }
      }
      unknown330[character] = flag;
    }
  }
}

void GfMenuObjMainMenu::finalize() {
  mm::mtl::safeRelease(unknown320);
  mm::mtl::safeRelease(unknown318);
  mm::mtl::safeRelease(m_menuCallContext);
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
  if (m_menuCallContext == nullptr) {
    ui::UIObjectAcc acc(unknown18, "LAY_main");
    GfMenuObjCommonJog::OpenParam param;
    if (m_menuCallContext == nullptr) {
      m_menuCallContext = GfMenuCallContext::create();
    }
    GfMenuTypes::Param layerParam;
    if (getFSLayerParam(unknown20, layerParam)) {
      param.unknown04 = layerParam.get<unknown001>().unknown00;
      removeFSLayerParam(unknown20);
    }
    param.unknown00 = 1;
    GfMenuObjCommonJog::open(m_menuCallContext, param);
    GfMenuObject::setCallContextEventHandler(m_menuCallContext, acc.unknown10);
  }
  GfMenuCallContext::GfMenuResult result;
  return !m_menuCallContext->unknown18.empty() && m_menuCallContext->popResult(result) && result.unknown04 == 0;
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
  if (m_menuCallContext != nullptr) {
    GfMenuObjCommonJog::disable(m_menuCallContext);
  }
}

void GfMenuObjMainMenu::resumeInput() {
  ui::UIObjectAcc acc(unknown18, "LAY_main");
  GfMenuObject::enableInput(acc.unknown10);
  GfMenuObject::enableFSSwitching();
  if (m_menuCallContext != nullptr) {
    GfMenuObjCommonJog::enable(m_menuCallContext);
  }
}

bool GfMenuObjMainMenu::seqStartCommon() {
  suspendInput();
  return true;
}

bool GfMenuObjMainMenu::seqCloseJog() {
  if (m_menuCallContext != nullptr) {
    GfMenuObjCommonJog::close(m_menuCallContext);
  }
  GfMenuCallContext::GfMenuResult result;
  if (!m_menuCallContext->unknown18.empty() && m_menuCallContext->popResult(result) && result.unknown04 == 1) {
    m_menuCallContext->reset();
    return true;
  }
  return false;
}

bool GfMenuObjMainMenu::seqOpenJog() {
  if (!m_menuCallContext->isActive()) {
    ui::UIObjectAcc acc(unknown18, "LAY_main");
    GfMenuObjCommonJog::OpenParam param;
    param.unknown00 = unknown310;
    GfMenuObjCommonJog::open(m_menuCallContext, param);
    GfMenuObject::setCallContextEventHandler(m_menuCallContext, acc.unknown10);
  }
  GfMenuCallContext::GfMenuResult result;
  return !m_menuCallContext->unknown18.empty() && m_menuCallContext->popResult(result) && result.unknown04 == 0;
}

bool GfMenuObjMainMenu::seqSwapPhase2() { return true; }

void GfMenuObjMainMenu::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    m_menuObjMainMenu->unknown68.unknown005();
    m_menuObjMainMenu->unknown68.unknown002(&GfMenuObjMainMenu::seqStartOpen);
    m_menuObjMainMenu->unknown68.unknown002(&GfMenuObjMainMenu::seqAppearPhase1);
    m_menuObjMainMenu->unknown68.unknown002(&GfMenuObjMainMenu::seqAppearPhase2);
    m_menuObjMainMenu->unknown68.unknown002(&GfMenuObjMainMenu::seqAppearPhase3);
    m_menuObjMainMenu->unknown68.unknown002(&GfMenuObjMainMenu::seqAppearPhase4);
    m_menuObjMainMenu->unknown68.unknown002(&GfMenuObjMainMenu::seqEndCommon);
    break;
  case 2: {
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 2;
    param.unknown00 = 0.5f;
    param.unknown14 = 1;
    GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    RQ_SETUP_PARTY party;
    u32 index = m_menuObjMainMenu->unknown320->getIndex(false);
    u32 size = m_menuObjMainMenu->unknown320->getSize();
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
    if (m_menuObjMainMenu->unknown330[index] == 1) {
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
    m_menuObjMainMenu->unknown328 = m_menuObjMainMenu->unknown320->getSelectObject();
    m_menuObjMainMenu->unknown320->setIndex(index);
    break;
  }
  case 8: {
    u64 param = event.unknown08_u64;
    int type = param >> 32;
    int index = param;
    if (type == 9) {
      if (index != -1 && GfMenuObjUtil::isBladeContorolable(index, 0)) {
        m_menuObjMainMenu->setBustupCtrlChar(index, m_menuObjMainMenu->unknown330[index] ^ 1, true);
      }
    } else if (type == 2) {
      if (m_menuObjMainMenu->unknown30c == 0) {
        GfMenuObject::closeFSLayer(acc.unknown10, true, true);
      } else {
        GfMenuObjCommonJog::pop(m_menuObjMainMenu->m_menuCallContext);
      }
    } else if (type == 10) {
      GfMenuObject::changeFSSubLayer(acc.unknown10, 1, 0x1b, true);
    }
    GfMenuObjUtil::playSECommonFromInput(event.unknown0c);
    break;
  }
  case 0xe:
    if (ui::UICtrlObject::getEventCtrlObjID(event) == 1) {
      m_menuObjMainMenu->listenerPartySelect(event);
    }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  case 0x41: {
    if (m_menuObjMainMenu->m_menuCallContext == nullptr || m_menuObjMainMenu->m_menuCallContext->unknown0c != event.unknown08) {
      break;
    }
    u16 value = event.unknown14_u16;
    switch (event.unknown10_u16) {
    case 2:
      if (m_menuObjMainMenu->unknown30c == 0) {
        GfMenuTypes::Param layerParam;
        unknown001 layer;
        layer.unknown00 = value;
        layerParam.set(layer);
        GfMenuObject::registFSLayerParam(m_menuObjMainMenu->unknown20, layerParam);
      }
      break;
    case 3:
      GfMenuObject::changeFSSubLayer(acc.unknown10, 1, value, true);
      break;
    case 4:
      m_menuObjMainMenu->unknown30c = value;
      m_menuObjMainMenu->suspendInput();
      break;
    case 5:
      m_menuObjMainMenu->unknown30c = value;
      m_menuObjMainMenu->resumeInput();
      break;
    }
    break;
  }
  }
}

} // namespace gf
