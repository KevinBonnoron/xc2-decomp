#include "gf/menu/object/gf_menu_obj_quest_reward.h"

#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_object_acc.h"

namespace gf {

constexpr u32 CALL_QUEST_REWARD = 33;

GfMenuObjQuestReward::GfMenuObjQuestReward(u32 handle) : GfMenuObject(handle) {}

GfMenuObjQuestReward::~GfMenuObjQuestReward() { ; }

void GfMenuObjQuestReward::initialize() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  if (main.isValid()) {
    attachExternalCall(CALL_QUEST_REWARD, main.unknown10);
    GfMenuObject::initialize();
    main.setSuspend(true);
  }
}

void GfMenuObjQuestReward::finalize() { GfMenuObject::finalize(); }

void GfMenuObjQuestReward::update() { GfMenuObject::update(); }

void GfMenuObjQuestReward::open(GfMenuCallContext *context, bool isAnim) {
  if (context != nullptr && GfMenuObjUtil::checkCCNext(context, CALL_QUEST_REWARD)) {
    ui::UIObjectAcc acc(context->unknown14);
    ui::EventData event;
    event.unknown00 = GfMenuTypes::unknown003_33;
    event.unknown08 = isAnim;
    event.unknown0c = 0;
    GfMenuObject::sendEvent(context->unknown14, event, 0.0f);
  }
}

void GfMenuObjQuestReward::close(GfMenuCallContext *context, bool isAnim) {
  if (context != nullptr && GfMenuObjUtil::checkCCNext(context, CALL_QUEST_REWARD)) {
    ui::UIObjectAcc acc(context->unknown14);
    ui::EventData event;
    event.unknown00 = GfMenuTypes::unknown003_34;
    event.unknown08 = isAnim;
    GfMenuObject::sendEvent(context->unknown14, event, 0.0f);
  }
}

} // namespace gf
