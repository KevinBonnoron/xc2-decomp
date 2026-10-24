#include "gf/menu/object/gf_menu_obj_quest_reward.h"

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

} // namespace gf
