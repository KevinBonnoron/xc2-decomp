#include "gf/menu/object/gf_menu_obj_quest_reward.h"

#include "gf/data/gf_data_quest.h"
#include "gf/game/quest/gf_quest_id.h"
#include "gf/game/quest/gf_quest_info.h"
#include "gf/menu/adapter/gf_menu_item_adapter.h"
#include "gf/menu/adapter/gf_menu_mission_adapter.h"
#include "gf/menu/adapter/gf_menu_quest_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: call id of the quest reward layout; original name unknown.
constexpr u32 CALL_UNKNOWN_33 = 33;

GfMenuObjQuestReward::GfMenuObjQuestReward(u32 handle) : GfMenuObject(handle) {}

GfMenuObjQuestReward::~GfMenuObjQuestReward() { ; }

void GfMenuObjQuestReward::initialize() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  if (main.isValid()) {
    attachExternalCall(CALL_UNKNOWN_33, main.unknown10);
    GfMenuObject::initialize();
    main.setSuspend(true);
  }
}

void GfMenuObjQuestReward::finalize() { GfMenuObject::finalize(); }

void GfMenuObjQuestReward::update() { GfMenuObject::update(); }

void GfMenuObjQuestReward::open(GfMenuCallContext *context, bool isAnim) {
  if (context != nullptr && GfMenuObjUtil::checkCCNext(context, CALL_UNKNOWN_33)) {
    ui::UIObjectAcc acc(context->unknown14);
    ui::EventData event;
    event.unknown00 = GfMenuTypes::unknown003_33;
    event.unknown08 = isAnim;
    event.unknown0c = 0;
    GfMenuObject::sendEvent(context->unknown14, event, 0.0f);
  }
}

void GfMenuObjQuestReward::close(GfMenuCallContext *context, bool isAnim) {
  if (context != nullptr && GfMenuObjUtil::checkCCNext(context, CALL_UNKNOWN_33)) {
    ui::UIObjectAcc acc(context->unknown14);
    ui::EventData event;
    event.unknown00 = GfMenuTypes::unknown003_34;
    event.unknown08 = isAnim;
    GfMenuObject::sendEvent(context->unknown14, event, 0.0f);
  }
}

void GfMenuObjQuestReward::RewardListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case GfMenuTypes::unknown003_257: {
    OpenParam *param = reinterpret_cast<OpenParam *>(event.unknown08_u64);
    if (param != nullptr) {
      unknown28 = GfMenuItemList::create();
      unknown30 = param->unknown00;
      unknown38 = param->unknown10;
      unknown40 = param->unknown0c;
      unknown44 = false;
      if (param->unknown0c == 1) {
        GfMenuMissionAdapter::createFromReference(acc.searchChild("TXT_reward_point_l3_num@01"), 8, param->unknown10, false);
        GfMenuMissionAdapter::createFromReference(acc.searchChild("TXT_reward_point_l3_num@02"), 10, param->unknown10, false);
        GfMenuMissionAdapter::createFromReference(acc.searchChild("TXT_reward_point_l3_num@03"), 15, param->unknown10, false);
        acc.setDispChild(false, "TXT_reward_point_l3_idx@03");
        acc.setDispChild(true, "TXT_reward_point_l3_idx_mer@03");
      } else {
        GfMenuQuestAdapter::createFromReference(acc.searchChild("TXT_reward_point_l3_num@01"), param->unknown00, 0x26, false);
        GfMenuQuestAdapter::createFromReference(acc.searchChild("TXT_reward_point_l3_num@02"), param->unknown00, 0x27, false);
        GfMenuQuestAdapter::createFromReference(acc.searchChild("TXT_reward_point_l3_num@03"), param->unknown00, 0x28, false);
      }
      acc.setDispChild(true, "LAY_reward_point_l3");
      mm::mtl::FixStr<32> name;
      for (u32 i = 0; i < 4; i++) {
        name.format("TXT_reward_item_name@%02d", i + 1);
        GfMenuItemAdapter *adapter = GfMenuItemAdapter::createFromList(acc.searchChild(name.c_str()), 0, unknown28, i, false);
        if (adapter != nullptr) {
          name.format("LAY_reward_item@%02d", i + 1);
          adapter->unknown24 = acc.searchChild(name.c_str());
        }
        name.format("TXT_reward_item_num@%02d", i + 1);
        GfMenuItemAdapter::createFromList(acc.searchChild(name.c_str()), 3, unknown28, i, false);
        name.format("IMG_reward_item_icon@%02d", i + 1);
        GfMenuItemAdapter::createFromList(acc.searchChild(name.c_str()), 2, unknown28, i, false);
      }
      delete param;
    }
    break;
  }
  case 2:
    mm::mtl::safeRelease(unknown28);
    acc.setTerm();
    break;
  case 3:
    if (event.unknown08 == 3) {
      unknown30 = nullptr;
      acc.setTerm();
    }
    break;
  case GfMenuTypes::unknown003_33: {
    unknown44 = event.unknown08 == 1;
    switch (unknown40) {
    case 0: {
      GfMenuItemList::QuestRewardSetup setup;
      QuestID quest;
      unknown30->getQuest(quest);
      QuestID parent = GfDataQuest::getListPRTQuestID(quest);
      if (!parent.empty()) {
        quest = parent;
      }
      setup.unknown00.unknown08 = 4;
      setup.unknown14 = GfDataQuest::getListRewardSetA(quest);
      if (GfQuestInfo::isQuestFin(quest)) {
        if (GfQuestInfo::getState(quest) == QSTATE_UNKNOWN_2) {
          setup.unknown14 = GfDataQuest::getListRewardSetA(quest);
        } else {
          setup.unknown14 = GfDataQuest::getListRewardSetB(quest);
        }
      }
      unknown28->clear();
      unknown28->setupFromQuestReward(setup);
      break;
    }
    case 1: {
      GfMenuItemList::MissionRewardSetup setup;
      setup.unknown14 = unknown38->unknown0c;
      setup.unknown00.unknown08 = 4;
      unknown28->clear();
      unknown28->setupFromMissionReward(setup);
      break;
    }
    }
    if (unknown44) {
      GfMenuObjUtil::CtrlParam param;
      param.unknown08 = 1;
      param.unknown00 = 0.1f;
      param.unknown11 = true;
      param.unknown04 = 1;
      GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    } else {
      acc.setDisp(true);
    }
    break;
  }
  case GfMenuTypes::unknown003_34: {
    int type = event.unknown08;
    if (unknown44) {
      GfMenuObjUtil::CtrlParam param;
      param.unknown08 = 2;
      param.unknown00 = 0.1f;
      param.unknown11 = true;
      param.unknown14 = 10;
      param.unknown04 = type == 1 ? 3 : 2;
      GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    } else {
      acc.setDisp(false);
      if (type == 1) {
        unknown30 = nullptr;
        acc.setTerm();
      }
    }
    break;
  }
  case 1:
    acc.setDisp(false);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf
