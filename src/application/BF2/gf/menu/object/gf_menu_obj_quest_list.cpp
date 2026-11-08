#include "gf/menu/object/gf_menu_obj_quest_list.h"

#include "gf/data/gf_bdat_quest.h"
#include "gf/game/quest/gf_quest_id.h"
#include "gf/game/quest/gf_quest_manager.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_flag.h"
#include "gf/menu/gf_menu_fullscreen.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/gf_menu_reference_quest.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "gf/menu/list/gf_menu_quest_list.h"
#include "gf/menu/object/gf_menu_obj_mainmenu2.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/reference_object.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
#include "ui/event/ui_event_data.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"

namespace gf {

GfMenuObjQuestList::GfMenuObjQuestList(u32 handle)
    : GfMenuObject(handle), unknown28(nullptr), unknown30(nullptr), unknown38(nullptr), unknown40(nullptr), unknown48(nullptr), unknown58(0), unknown5c(0), unknown60(0), unknown68(nullptr),
      unknown70(nullptr), unknown78(nullptr), unknown80(nullptr), unknown88(nullptr), unknown0a0(nullptr), unknown0b0(this), unknown340(0), unknown344(0), unknown358(nullptr), unknown360(true) {
  unknown0a0 = GfMenuCallContext::create();
  unknown0a8 = GfMenuCallContext::create();
}

GfMenuObjQuestList::~GfMenuObjQuestList() {
  unknown90 = nullptr;
  unknown98 = nullptr;
  unknown348 = nullptr;
  unknown350 = nullptr;
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown68);
  mm::mtl::safeRelease(unknown70);
  mm::mtl::safeRelease(unknown78);
  mm::mtl::safeRelease(unknown80);
  mm::mtl::safeRelease(unknown88);
  mm::mtl::safeRelease(unknown38);
  mm::mtl::safeRelease(unknown40);
  mm::mtl::safeRelease(unknown48);
  mm::mtl::safeRelease(unknown0a0);
  mm::mtl::safeRelease(unknown0a8);
  mm::mtl::safeRelease(unknown358);
}

void GfMenuObjQuestList::finalize() {
  GfMenuFlag::set4(1, unknown58);
  GfMenuFlag::set4(2, unknown5c);
  GfMenuFlag::set4(3, unknown60);
  GfMenuObject::finalize();
}

void GfMenuObjQuestList::update() {
  unknown0b0.unknown003();
  GfMenuObject::update();
}

void GfMenuObjQuestList::registOpenParam(const OpenParam &param) {
  GfMenuTypes::Param layerParam;
  layerParam.set(param);
  GfMenuFullScreen::registLayerParam(0x2f, layerParam);
}

void GfMenuObjQuestList::sendUpdateEvent(u32 handle, int param) {
  if (handle == 0) {
    handle = ui::UIObjectAcc(unknown18, "LAY_main").unknown10;
  }
  ui::EventData event;
  event.unknown08 = param;
  event.unknown0c = 0;
  event.unknown00 = GfMenuTypes::unknown003_260;
  sendEvent(handle, event, 0.0f);
}

void GfMenuObjQuestList::sendResumeEvent(u32 handle, int param) {
  if (handle == 0) {
    handle = ui::UIObjectAcc(unknown18, "LAY_main").unknown10;
  }
  ui::EventData event;
  event.unknown08 = param;
  event.unknown0c = 0;
  event.unknown00 = GfMenuTypes::unknown003_258;
  sendEvent(handle, event, 0.0f);
}

void GfMenuObjQuestList::sendSuspendEvent(u32 handle, int param) {
  if (handle == 0) {
    handle = ui::UIObjectAcc(unknown18, "LAY_main").unknown10;
  }
  ui::EventData event;
  event.unknown08 = param;
  event.unknown0c = 0;
  event.unknown00 = GfMenuTypes::unknown003_257;
  sendEvent(handle, event, 0.0f);
}

void GfMenuObjQuestList::changeView(u32 view) {
  if (unknown58 == view) {
    return;
  }
  ui::UIObjectAcc main(unknown18, "LAY_main");
  if (view == 1) {
    sendOpenEvent(main.searchChild("LAY_list"), 0, 0.0f);
    sendCloseEvent(main.searchChild("LAY_thumb"), 0, 0.0f);
  } else if (view == 0) {
    sendOpenEvent(main.searchChild("LAY_thumb"), 0, 0.0f);
    sendCloseEvent(main.searchChild("LAY_list"), 0, 0.0f);
  } else {
    return;
  }
  unknown58 = view;
}

bool GfMenuObjQuestList::seqActivateSelect() {
  if (unknown0a0 != nullptr) {
    if (unknown0a0->isActive()) {
      return false;
    }
    GfMenuCallContext::GfMenuResult result;
    if (unknown0a0->popResult(result) && result.unknown00 == 0 && result.unknown04 == 0) {
      if (GfQuestManager::getCurrentQuest(QTYPE_NONE).unknown00 == unknown340) {
        GfQuestManager::setCurrentQuestForScenario();
      } else {
        GfQuestManager::setCurrentQuest(toQuestID(unknown340));
      }
    }
  }
  return true;
}

bool GfMenuObjQuestList::seqEnd() {
  u32 handle = unknown344;
  if (handle == 0) {
    handle = ui::UIObjectAcc(unknown18, "LAY_main").unknown10;
  }
  ui::EventData event;
  event.unknown00 = GfMenuTypes::unknown003_259;
  sendEvent(handle, event, 0.0f);
  unknown344 = 0;
  return true;
}

bool GfMenuObjQuestList::seqActivateError() { return true; }

void GfMenuObjQuestList::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1: {
    unknown20->initializeSub(acc);
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown00 = 6;
    param.unknown04 = 0;
    param.unknown10 = 1;
    GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
    GfMenuObjOperationInfo::setGuideText(4, 0);
    break;
  }
  case 2:
  case GfMenuTypes::unknown003_34:
    if (!unknown20->unknown360) {
      unknown163(handle, 3, 2);
    } else {
      GfMenuObjUtil::PresetCtrlParam param;
      param.unknown00 = 6;
      param.unknown04 = 1;
      param.unknown10 = 2;
      GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
    }
    break;
  case 3:
    if (event.unknown08 == 1) {
      GfMenuObjMainMenu2::setCloseKeyEnable(true);
    } else if (event.unknown08 == 2) {
      acc.setDisp(false);
      acc.setTerm();
    }
    break;
  case 0x24: {
    GfMenuObject::disableInput(acc.searchChild("LAY_list"));
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown00 = 6;
    param.unknown04 = 1;
    param.unknown10 = 1;
    GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
    unknown20->unknown360 = false;
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjQuestList>(const mm::mtl::Delegate<bool()> *);
