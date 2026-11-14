#include "gf/menu/object/gf_menu_obj_quest_list.h"

#include "gf/data/gf_bdat_quest.h"
#include "gf/game/quest/gf_quest_id.h"
#include "gf/game/quest/gf_quest_info.h"
#include "gf/game/quest/gf_quest_manager.h"
#include "gf/game/quest/gf_quest_task_param.h"
#include "gf/game/quest/gf_quest_util.h"
#include "gf/gf_allocator.h"
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
#include "gf/menu/object/gf_menu_obj_quest_reward.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/util/gf_item_util.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
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

void GfMenuObjQuestList::initialize() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  if (main.isValid()) {
    unknown28 = GfMenuQuestList::create();
    unknown30 = GfMenuQuestList::create();
    unknown364 = 0;
    unknown368 = false;
    GfMenuTypes::Param param;
    if (getFSLayerParam(unknown20, param)) {
      unknown364 = param.get<OpenParam>().unknown00;
      QuestID parent = GfQuestInfo::getParentQuest(toQuestID(unknown364));
      if (!parent.empty()) {
        unknown364 = parent.unknown00;
      }
      unknown368 = true;
      removeFSLayerParam(unknown20);
    }
    unknown58 = GfMenuFlag::get4(1);
    unknown5c = GfMenuFlag::get4(2);
    unknown60 = GfMenuFlag::get4(3);
// __LINE__ must be 169 as in the original file: it is the line argument of operator new.
#line 169
    MainListener *listener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
    listener->addRef();
    ui::UIEventManager::get()->registObjectListener(main.unknown10, listener);
    if (listener != nullptr) {
      listener->release();
    }
    disableInput(main.searchChild("LAY_list"));
    disableInput(main.searchChild("LAY_thumb"));
    disableInput(main.searchChild("LAY_tab"));
    disableInput(main.searchChild("LAY_tab_select"));
    disableInput(main.searchChild("LAY_tab_open"));
    disableInput(main.searchChild("LAY_detail"));
    disableInput(main.searchChild("LAY_detail_task"));
    GfMenuObject::initialize();
  }
}

void GfMenuObjQuestList::setupList(u32 quest) {
  GfMenuQuestList::SetupParam param;
  param.unknown08 = unknown68->getSize();
  param.unknown10 = true;
  switch (unknown5c) {
  case 0:
    param.unknown14 = 7;
    break;
  case 1:
    param.unknown14 = 4;
    break;
  case 2:
    param.unknown14 = 1;
    break;
  case 3:
    param.unknown14 = 2;
    break;
  }
  if (unknown60 == 0) {
    param.unknown18 = 1;
  } else if (unknown60 == 1) {
    param.unknown18 = 2;
  }
  unknown28->clear();
  unknown30->clear();
  unknown28->setup(param);
  if (unknown28->getSize() != 0) {
    for (u32 i = 0; i < unknown70->getSize(); i++) {
      if (i < unknown28->getSize()) {
        unknown30->addContents(unknown28->getContents(i));
      }
    }
  }
  u32 pageCount = unknown28->getSize() / unknown70->getSize();
  if (unknown28->getSize() % unknown70->getSize() != 0) {
    pageCount++;
  }
  unknown90->unknown162(0);
  unknown98->unknown162(pageCount);
  {
    ui::UIObjectAcc thumbPage(unknown18, "LAY_thumb_page");
    thumbPage.setDisp(unknown98->unknown0c > 0);
  }
  unknown28->setIndex(0);
  unknown30->setIndex(0);
  if (quest != 0) {
    QuestID id(quest, quest >> 16);
    if (!id.empty()) {
      id = GfQuestInfo::getParentQuest(id);
      for (u32 i = 0; i < unknown28->getSize(); i++) {
        if (unknown28->getContents(i) == id) {
          unknown28->setIndex(i);
        }
      }
    }
  }
}

bool GfMenuObjQuestList::changeThumbPage(int page) {
  int pageCount = unknown98->unknown0c;
  if (pageCount < 2) {
    return false;
  }
  int target = page;
  if (page < 0) {
    target = pageCount - 1;
  }
  if (page >= pageCount) {
    target = 0;
  }
  unknown30->clear();
  for (u32 i = 0; i < unknown70->getSize(); i++) {
    u32 index = i + unknown70->getSize() * target;
    if (index < unknown28->getSize()) {
      unknown30->addContents(unknown28->getContents(index));
    }
  }
  {
    ui::UIObjectAcc thumb(unknown18, "LAY_thumb");
    unknown30->setIndex(0);
    resetInputSelection(thumb.unknown10);
    setupInputSelectionFromList(thumb.unknown10, *unknown30);
    setupPadLineSelection(thumb.unknown10, 3);
  }
  unknown90->unknown162(target);
  return true;
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
      if (GfQuestManager::getCurrentQuest(QTYPE_UNKNOWN_0).unknown00 == unknown340) {
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

void GfMenuObjQuestList::ListListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    GfMenuObject::disableInput(acc.unknown10);
    acc.setDisp(false);
    break;
  case 6: {
    u32 index = event.unknown08;
    u32 previous = event.unknown0c;
    if (index != 0xffffffff) {
      unknown20->unknown28->setIndex(index);
      unknown20->unknown68->setIndex(unknown20->unknown28->getIndex(true));
    }
    if (previous != 0xffffffff && index != previous) {
      GfMenuObjUtil::playSECommonCursor();
    }
    break;
  }
  case 8:
    if (event.unknown0c == 1 && unknown20->unknown28->getSize() != 0) {
      if (unknown20->unknown28->getContents(unknown20->unknown28->getIndex(false)).unknown00 != 0) {
        unknown20->sendSuspendEvent(acc.unknown10, 0);
        unknown20->unknown340 = unknown20->unknown28->getContents(unknown20->unknown28->getIndex(false)).unknown00;
        GfMenuObject::sendOpenEvent(acc.searchSibiling("LAY_detail"), 0, 0.0f);
        GfMenuObjMainMenu2::setSystemKeyEnable(false);
        GfMenuObjUtil::playSECommonDecide();
        GfMenuObject::sendCloseEvent(acc.searchSibiling("LAY_tab_open"), 0, 0.0f);
        GfMenuObject::disableInput(acc.unknown10);
        GfMenuObjOperationInfo::remove(acc.unknown10, 0, 0, 0);
      }
    }
    break;
  case GfMenuTypes::unknown003_33:
    acc.setDisp(true);
    break;
  case GfMenuTypes::unknown003_34:
    acc.setDisp(false);
    break;
  case GfMenuTypes::unknown003_257:
    acc.setDispChild(false, "IMG_list_cursor");
    if (unknown20->unknown58 == 1) {
      GfMenuObject::disableInput(acc.unknown10);
      GfMenuObjOperationInfo::remove(acc.unknown10, 0, 0, 0);
    }
    break;
  case GfMenuTypes::unknown003_258:
    if (unknown20->unknown58 == 1) {
      GfMenuObject::enableInput(acc.unknown10);
      GfMenuObjMainMenu2::setSystemKeyEnable(true);
      GfMenuObjOperationInfo::add(acc.unknown10, 0, 0, 0);
      bool hasQuest = unknown20->unknown28->getSize() != 0;
      if (!hasQuest) {
        acc.setDispChild(false, "IMG_list_cursor");
      } else {
        acc.setDispChild(true, "IMG_list_cursor");
      }
      GfMenuObjOperationInfo::setActionEnable(acc.unknown10, 1, hasQuest);
      GfMenuObject::resetInputSelection(acc.unknown10);
      GfMenuObject::setupInputSelectionFromList(acc.unknown10, *unknown20->unknown28);
    }
    break;
  case GfMenuTypes::unknown003_260:
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjQuestList::TabOpenListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(false);
    GfMenuObject::disableInput(acc.unknown10);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  case 8:
    if (event.unknown0c == 9) {
      GfMenuObject::sendOpenEvent(acc.searchSibiling("LAY_tab"), 0, 0.0f);
      GfMenuObject::sendCloseEvent(acc.unknown10, 0, 0.0f);
      unknown20->sendSuspendEvent(acc.searchSibiling("LAY_thumb"), 0);
      unknown20->sendSuspendEvent(acc.searchSibiling("LAY_list"), 0);
      GfMenuObjMainMenu2::setSystemKeyEnable(false);
      GfMenuObjUtil::playSECommonOpenSubMenu();
    }
    break;
  case GfMenuTypes::unknown003_33:
    acc.setDisp(true);
    GfMenuObject::enableInput(acc.unknown10);
    GfMenuObjOperationInfo::add(acc.unknown10, 0, 0, 0);
    unknown20->sendResumeEvent(acc.searchSibiling("LAY_thumb"), 0);
    unknown20->sendResumeEvent(acc.searchSibiling("LAY_list"), 0);
    GfMenuObjMainMenu2::setSystemKeyEnable(true);
    break;
  case GfMenuTypes::unknown003_34:
    acc.setDisp(false);
    GfMenuObject::disableInput(acc.unknown10);
    GfMenuObjOperationInfo::remove(acc.unknown10, 0, 0, 0);
    break;
  }
}

void GfMenuObjQuestList::TaskListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    GfMenuObject::disableInput(acc.unknown10);
    acc.setDisp(false);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  case 3:
    if (event.unknown08 == 1) {
      GfMenuObject::enableInput(acc.unknown10);
      GfMenuObjOperationInfo::add(acc.unknown10, 0, 0, 0);
    }
    break;
  case 8:
    if (event.unknown0c == 2) {
      GfMenuObject::sendCloseEvent(acc.unknown10, 0, 0.0f);
      unknown20->sendResumeEvent(acc.getParentHandle(), 0);
      GfMenuObjUtil::playSECommonCloseSubMenu();
    }
    break;
  case GfMenuTypes::unknown003_33: {
    GfMenuObjUtil::CtrlParam param;
    param.unknown004("fade_in_l");
    param.unknown04 = 1;
    GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    QuestID quest;
    QuestID progress;
    unknown20->unknown348->getQuest(quest);
    progress = GfQuestInfo::getProgressQuest(quest);
    if (!progress.empty()) {
      quest = progress;
    }
    bool isNeedCharacter;
    {
      mm::mtl::FixedVector<u16, 32> characters;
      GfQuestUtil::getNeedCharacterByQuestTask(characters, quest, 0);
      isNeedCharacter = characters.size() != 0;
    }
    acc.setDispChild(isNeedCharacter, "LAY_detail_task_cond_pt");
    u32 count = acc.countChild("LAY_detail_task@%02d", 1);
    mm::mtl::FixStr<32> name;
    u32 taskCount;
    u32 completeCount;
    GfQuestInfo::getQuestTaskInfo(taskCount, completeCount, quest);
    unknown20->unknown358->clear();
    for (u32 i = 0; i < count; i++) {
      bool isDisp = false;
      MenuItemInfo info;
      if (i < taskCount) {
        QuestTaskParam taskParam(quest, i, TASK_STATE_UNKNOWN_0);
        GfQuestTaskLogResult result;
        if (GfQuestInfo::getTaskHide(taskParam) != 1) {
          if (GfQuestUtil::getMsgQuestTaskLog(result, taskParam)) {
            info.unknown04 = result.unknown1c;
            info.unknown08 = 1;
            info.unknown00 = GfItemUtil::getType(result.unknown1c);
            isDisp = result.unknown14 != 0;
          }
        }
      }
      unknown20->unknown358->addItem(info, false);
      name.format("LAY_detail_task_item@%02d", i + 1);
      acc.setDispChild(isDisp, name.c_str());
    }
    break;
  }
  case GfMenuTypes::unknown003_34: {
    GfMenuObjUtil::CtrlParam param;
    param.unknown004("fade_out_l");
    param.unknown14 = 10;
    GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    GfMenuObject::disableInput(acc.unknown10);
    GfMenuObjOperationInfo::remove(acc.unknown10, 0, 0, 0);
    break;
  }
  }
}

void GfMenuObjQuestList::ThumbListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    GfMenuObject::disableInput(acc.unknown10);
    acc.setDispChild(unknown20->unknown28->getSize() != 0 && unknown20->unknown98->unknown0c > 1, "LAY_thumb_input");
    acc.setDisp(false);
    break;
  case 6: {
    u32 index = event.unknown08;
    u32 previous = event.unknown0c;
    if (index != 0xffffffff) {
      unknown20->unknown30->setIndex(index);
      unknown20->unknown70->setIndex(unknown20->unknown30->getIndex(true));
    }
    if (previous != 0xffffffff && index != previous) {
      GfMenuObjUtil::playSECommonCursor();
    }
    break;
  }
  case 8:
    if (event.unknown0c == 1 && unknown20->unknown28->getSize() != 0) {
      if (unknown20->unknown28->getContents(unknown20->unknown28->getIndex(false)).unknown00 != 0) {
        unknown20->sendSuspendEvent(acc.unknown10, 0);
        unknown20->unknown340 = unknown20->unknown30->getContents(unknown20->unknown30->getIndex(false)).unknown00;
        GfMenuObject::sendOpenEvent(acc.searchSibiling("LAY_detail"), 0, 0.0f);
        GfMenuObjMainMenu2::setSystemKeyEnable(false);
        GfMenuObjUtil::playSECommonDecide();
        GfMenuObject::sendCloseEvent(acc.searchSibiling("LAY_tab_open"), 0, 0.0f);
        GfMenuObject::disableInput(acc.unknown10);
        GfMenuObjOperationInfo::remove(acc.unknown10, 0, 0, 0);
      }
    }
    break;
  case 9: {
    bool changed;
    if (event.unknown08 == 3) {
      changed = unknown20->changeThumbPage(unknown20->unknown90->unknown0c + 1);
    } else if (event.unknown08 == 4) {
      changed = unknown20->changeThumbPage(unknown20->unknown90->unknown0c - 1);
    } else {
      break;
    }
    if (changed) {
      GfMenuObjUtil::playSECommonCursor();
    }
    break;
  }
  case GfMenuTypes::unknown003_33:
    acc.setDisp(true);
    break;
  case GfMenuTypes::unknown003_34:
    acc.setDisp(false);
    break;
  case GfMenuTypes::unknown003_257:
    acc.setDispChild(false, "IMG_thumb_cursor");
    if (unknown20->unknown58 == 0) {
      GfMenuObject::disableInput(acc.unknown10);
      GfMenuObjOperationInfo::remove(acc.unknown10, 0, 0, 0);
    }
    break;
  case GfMenuTypes::unknown003_258:
    if (unknown20->unknown58 == 0) {
      GfMenuObject::enableInput(acc.unknown10);
      GfMenuObjMainMenu2::setSystemKeyEnable(true);
      GfMenuObjOperationInfo::add(acc.unknown10, 0, 0, 0);
      bool hasQuest = unknown20->unknown28->getSize() != 0;
      bool isDispInput;
      if (!hasQuest) {
        acc.setDispChild(false, "IMG_thumb_cursor");
        isDispInput = false;
      } else {
        acc.setDispChild(true, "IMG_thumb_cursor");
        isDispInput = unknown20->unknown98->unknown0c > 1;
      }
      acc.setDispChild(isDispInput, "LAY_thumb_input");
      GfMenuObjOperationInfo::setActionEnable(acc.unknown10, 1, hasQuest);
      GfMenuObject::resetInputSelection(acc.unknown10);
      GfMenuObject::setupInputSelectionFromList(acc.unknown10, *unknown20->unknown30);
      GfMenuObject::setupPadLineSelection(acc.unknown10, 3);
    }
    break;
  case GfMenuTypes::unknown003_260:
    unknown20->changeThumbPage(0);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjQuestList::DetailListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    GfMenuObject::disableInput(acc.unknown10);
    acc.setDisp(false);
    unknown0c = 0;
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  case 3:
    if (event.unknown08 == 1) {
      int finished = unknown0c;
      GfMenuObject::enableInput(acc.unknown10);
      GfMenuObjOperationInfo::add(acc.unknown10, 0, 0, 0);
      QuestID quest;
      unknown20->unknown348->getQuest(quest);
      GfMenuObjOperationInfo::setActionEnable(acc.unknown10, 9, finished != 1);
      GfMenuObjOperationInfo::setActionEnable(acc.unknown10, 10, finished != 1);
      if (finished != 1) {
        bool isCurrent = GfQuestManager::getCurrentQuest(QTYPE_UNKNOWN_0).unknown00 == unknown20->unknown340;
        if (unknown20->unknown364 == 0) {
          GfMenuObjOperationInfo::changeText(acc.unknown10, 10, isCurrent);
        } else {
          GfMenuObjOperationInfo::changeText(acc.unknown10, 10, isCurrent ? 2u : 0u);
        }
      }
    } else if (event.unknown08 == 2) {
      acc.setDisp(false);
    }
    break;
  case 8:
    if (event.unknown0c == 2) {
      GfMenuObject::sendCloseEvent(acc.unknown10, 0, 0.0f);
      GfMenuObject::sendOpenEvent(acc.searchSibiling("LAY_tab_open"), 0, 0.0f);
      GfMenuObjUtil::playSECommonCancel();
    } else if (event.unknown0c == 9) {
      QuestID quest;
      unknown20->unknown348->getQuest(quest);
      if (!GfQuestInfo::isQuestFin(quest)) {
        unknown20->sendSuspendEvent(acc.unknown10, 0);
        GfMenuObject::sendOpenEvent(acc.searchChild("LAY_detail_task"), 0, 0.0f);
        GfMenuObjUtil::playSECommonOpenSubMenu();
      }
    } else if (event.unknown0c == 10) {
      QuestID quest;
      unknown20->unknown348->getQuest(quest);
      if (!GfQuestInfo::isQuestFin(quest)) {
        unknown20->unknown344 = acc.unknown10;
        unknown20->unknown340 = quest.unknown00;
        unknown20->unknown0b0.unknown002(&GfMenuObjQuestList::seqActivateStart);
        GfMenuObject::disableInput(acc.unknown10);
      }
    }
    break;
  case GfMenuTypes::unknown003_33: {
    QuestID quest = toQuestID(unknown20->unknown340);
    unknown20->unknown348->unknown0c = quest;
    bool isFinished = GfQuestInfo::isQuestFin(quest);
    acc.setDispChild(!isFinished, "LAY_detail_summary");
    acc.setDispChild(isFinished, "LAY_detail_result");
    acc.setDispChild(isFinished, "TXT_detail_complete");
    if (!isFinished) {
      mm::mtl::FixStr<32> name;
      for (u32 i = 0; i < 4; i++) {
        GfQuestTaskLogResult result;
        name.format("LAY_detail_task_status@%02d", i + 1);
        bool isValid;
        {
          QuestTaskParam param(quest, i, TASK_STATE_UNKNOWN_0);
          isValid = GfQuestUtil::getMsgQuestTaskLog(result, param);
        }
        acc.setDispChild(isValid, name.c_str());
        if (isValid) {
          name.format("IMG_detail_task_st@%02d", i + 1);
          ui::UIObjectAcc status(acc.unknown10, name.c_str());
          status.setImageIndex(!result.unknown24);
        }
      }
      mm::mtl::FixedVector<u16, 32> characters;
      bool isNeedCharacter = GfQuestUtil::getNeedCharacterByQuestTask(characters, quest, 0);
      acc.setDispChild(isNeedCharacter && characters.size() != 0, "IMG_detail_cond_member");
    }
    acc.setDispChild(!isFinished, "LAY_detail_task_list");
    GfMenuObjUtil::CtrlParam param;
    param.unknown004("fade_in_l");
    param.unknown11 = true;
    param.unknown04 = 1;
    GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    GfMenuObjQuestReward::open(unknown20->unknown0a8, false);
    unknown0c = isFinished;
    break;
  }
  case GfMenuTypes::unknown003_34: {
    GfMenuObjUtil::CtrlParam param;
    param.unknown004("fade_out_l");
    param.unknown11 = true;
    param.unknown14 = 10;
    param.unknown04 = 2;
    GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    GfMenuObject::disableInput(acc.unknown10);
    GfMenuObjOperationInfo::remove(acc.unknown10, 0, 0, 0);
    GfMenuObjUtil::playSECommonCancel();
    break;
  }
  case GfMenuTypes::unknown003_257: {
    GfMenuObjUtil::CtrlParam param;
    param.unknown004("fade_out_l");
    param.unknown04 = 2;
    param.unknown14 = 10;
    GfMenuObjUtil::startCtrl(acc.searchChild("LAY_detail_main"), param, nullptr);
    GfMenuObject::disableInput(acc.unknown10);
    GfMenuObjOperationInfo::remove(acc.unknown10, 0, 0, 0);
    break;
  }
  case GfMenuTypes::unknown003_258: {
    GfMenuObjUtil::CtrlParam param;
    param.unknown004("fade_in_l");
    param.unknown04 = 1;
    int ctrl = GfMenuObjUtil::startCtrl(acc.searchChild("LAY_detail_main"), param, nullptr);
    GfMenuObject::hookCtrlEvent(acc.unknown10, ctrl);
    break;
  }
  case GfMenuTypes::unknown003_259: {
    bool isCurrent = GfQuestManager::getCurrentQuest(QTYPE_UNKNOWN_0).unknown00 == unknown20->unknown340;
    if (unknown20->unknown364 == 0) {
      GfMenuObjOperationInfo::changeText(acc.unknown10, 10, isCurrent);
    } else {
      GfMenuObjOperationInfo::changeText(acc.unknown10, 10, isCurrent ? 2u : 0u);
    }
    GfMenuObject::enableInput(acc.unknown10);
    break;
  }
  }
}

void GfMenuObjQuestList::TabListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(false);
    GfMenuObject::disableInput(acc.unknown10);
    break;
  case 6: {
    u32 index = event.unknown08;
    if (index != 0xffffffff) {
      u32 previous = event.unknown0c;
      if (previous != 0xffffffff) {
        ui::UIObjectAcc prev(unknown20->unknown78->getObject(previous));
        prev.loadDefColor();
        prev.setBorderWeight(-0.5f);
      }
      unknown20->unknown78->setIndex(index);
      {
        ui::UIObjectAcc select(unknown20->unknown78->getSelectObject());
        GfMenuObjUtil::setColMulandAdd(select.unknown10, "txt_normal");
        select.setBorderWeight(1.0f);
      }
      if (previous != 0xffffffff && index != previous) {
        GfMenuObjUtil::playSECommonTab();
      }
    }
    break;
  }
  case GfMenuTypes::unknown003_33:
    GfMenuObject::resetInputSelection(acc.unknown10);
    GfMenuObject::setupInputSelection(acc.unknown10, 0, unknown20->unknown78->getSize());
    for (u32 i = 0; i < unknown20->unknown78->getSize(); i++) {
      ui::UIObjectAcc tab(unknown20->unknown78->getObject(i));
      tab.loadDefColor();
      tab.setBorderWeight(-0.5f);
    }
    acc.setDisp(true);
    GfMenuObject::enableInput(acc.unknown10);
    GfMenuObjOperationInfo::add(acc.unknown10, 0, 0, 0);
    break;
  case 8:
    if (event.unknown0c == 2) {
      acc.setDisp(false);
      GfMenuObject::disableInput(acc.unknown10);
      GfMenuObjOperationInfo::remove(acc.unknown10, 0, 0, 0);
      GfMenuObject::sendOpenEvent(acc.searchSibiling("LAY_tab_open"), 0, 0.0f);
      GfMenuObjUtil::playSECommonCancel();
    } else if (event.unknown0c == 1) {
      GfMenuObject::sendOpenEvent(acc.searchChild("LAY_tab_select"), unknown20->unknown78->getIndex(false), 0.0f);
      unknown20->sendSuspendEvent(acc.unknown10, 0);
      unknown20->sendSuspendEvent(acc.searchSibiling("LAY_thumb"), 0);
      unknown20->sendSuspendEvent(acc.searchSibiling("LAY_list"), 0);
      GfMenuObjUtil::playSECommonDecide();
    }
    break;
  case GfMenuTypes::unknown003_257:
    GfMenuObject::disableInput(acc.unknown10);
    GfMenuObjOperationInfo::remove(acc.unknown10, 0, 0, 0);
    break;
  case GfMenuTypes::unknown003_258: {
    int param = event.unknown08;
    bool isUpdate = param == 2;
    if (param == 0) {
      GfMenuObject::enableInput(acc.unknown10);
      GfMenuObjOperationInfo::add(acc.unknown10, 0, 0, 0);
    } else {
      acc.setDisp(false);
      GfMenuObject::sendOpenEvent(acc.searchSibiling("LAY_tab_open"), 0, 0.0f);
    }
    if (isUpdate) {
      unknown20->sendUpdateEvent(acc.searchSibiling("LAY_thumb"), 0);
      unknown20->sendUpdateEvent(acc.searchSibiling("LAY_list"), 0);
    }
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjQuestList>(const mm::mtl::Delegate<bool()> *);
