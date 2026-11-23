#include "gf/object/component/pc/gf_pc_ai_agent_field.h"

#include "framework/memory/allocator.h"
#include "framework/message/message_object.h"
#include "framework/navi/navi_manager.h"
#include "framework/navi/navi_util.h"
#include "fw/fw_param_manager.h"
#include "gf/game/gf_game_player_formation.h"
#include "gf/object/component/pc/field/ai/gf_pc_ai_follow_task_field.h"
#include "gf/object/component/pc/field/ai/gf_pc_ai_idle_task_field.h"
#include "gf/object/component/pc/field/ai/gf_pc_ai_jump_task_field.h"
#include "gf/object/component/pc/field/ai/gf_pc_ai_retreat_task_field.h"
#include "gf/object/component/pc/field/ai/gf_pc_ai_sensor_task_field.h"
#include "gf/object/component/pc/field/ai/gf_pc_ai_wall_task_field.h"
#include "gf/object/component/pc/field/ai/gf_pc_ai_warp_task_field.h"
#include "gf/object/component/pc/field/gf_pc_param_field.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_property_field.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_util.h"
#include "ml/rand.h"
#include "mm_math/mm_quat.h"
#include "navi/nvmsh_ac_obj.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace gf {
namespace pc {

AIAgentField::AIAgentField() : unknown00(nullptr) {}

AIAgentField::~AIAgentField() {}

void AIAgentField::setup(GfComPropertyPc &property) {
  unknown00 = fw::NaviManager::get()->createObject();
  unknown88 = fw::ParamManager::get()->unknown408[16];
  mm::mtl::IAllocator *allocator = fw::Allocator::getProcAllocator();
  m_behaviorTree.beginSetup(20, allocator);
  m_behaviorTree.unknown003<BlackBoardField>();
  m_behaviorTree.createComposite<ai::ParallelNode>(0, "root_sequence", 3);
  m_behaviorTree.createTask<TaskFieldSensor>(1, "sensor_task");
  m_behaviorTree.createComposite<ai::SelectorNode>(2, "check_warp_selector", 3);
  m_behaviorTree.createTask<TaskFieldCheckWarp>(3, "check_warp_task");
  m_behaviorTree.createTask<TaskFieldCheckWarpBattleWaterDead>(4, "check_warp_water_dead_task");
  m_behaviorTree.createTask<TaskFieldCheckWarpFallDead>(5, "check_warp_fall_dead_task");
  m_behaviorTree.createComposite<ai::SelectorNode>(6, "move_selector", 6);
  m_behaviorTree.createTask<TaskFieldJump>(14, "jump_task");
  m_behaviorTree.createComposite<ai::SequenceNode>(15, "follow_sequence", 2);
  m_behaviorTree.createTask<TaskFieldFollowTarget>(16, "follow_target_task");
  GfGamePlayerFormation *formation = GfGamePlayerFormation::get();
  if (formation->unknown1a0[property.unknown38].unknown10) {
    m_behaviorTree.createTask<TaskFieldFollowMainPc>(17, "follow_task");
    m_behaviorTree.createComposite<ai::SelectorNode>(7, "wall_selector", 5);
    m_behaviorTree.createTask<TaskFieldWallFall>(8, "fall_wall_task");
    m_behaviorTree.createTask<TaskFieldWallJumpWait>(9, "wall_jump_wait_task");
    m_behaviorTree.createTask<TaskFieldWallPrepare>(10, "prepare_wall_task");
    m_behaviorTree.createTask<TaskFieldWallEscape>(11, "escape_wall_task");
    m_behaviorTree.createTask<TaskFieldWallFollow>(12, "follow_wall_task");
    m_behaviorTree.createTask<TaskFieldIdleTurn>(18, "idle_turn_task");
    m_behaviorTree.createTask<TaskFieldIdle>(19, "idle_task");
    m_behaviorTree.endSetup();
    m_behaviorTree.attachRoot(0);
    m_behaviorTree.attachComposite(0, 1, 0);
    m_behaviorTree.attachComposite(0, 2, 1);
    m_behaviorTree.attachComposite(2, 3, 0);
    m_behaviorTree.attachComposite(2, 4, 1);
    m_behaviorTree.attachComposite(2, 5, 2);
    m_behaviorTree.attachComposite(0, 6, 2);
    m_behaviorTree.attachComposite(6, 7, 0);
    m_behaviorTree.attachComposite(7, 8, 0);
    m_behaviorTree.attachComposite(7, 10, 1);
    m_behaviorTree.attachComposite(7, 9, 2);
    m_behaviorTree.attachComposite(7, 11, 3);
    m_behaviorTree.attachComposite(7, 12, 4);
  } else {
    m_behaviorTree.createTask<TaskFieldFollowBuddyPc>(17, "follow_task");
    m_behaviorTree.createTask<TaskFieldRetreat>(13, "retreat_task");
    m_behaviorTree.createTask<TaskFieldIdleTurn>(18, "idle_turn_task");
    m_behaviorTree.createTask<TaskFieldIdle>(19, "idle_task");
    m_behaviorTree.endSetup();
    m_behaviorTree.attachRoot(0);
    m_behaviorTree.attachComposite(0, 1, 0);
    m_behaviorTree.attachComposite(0, 2, 1);
    m_behaviorTree.attachComposite(2, 3, 0);
    m_behaviorTree.attachComposite(2, 4, 1);
    m_behaviorTree.attachComposite(2, 5, 2);
    m_behaviorTree.attachComposite(0, 6, 2);
    m_behaviorTree.attachComposite(6, 13, 2);
  }
  m_behaviorTree.attachComposite(6, 14, 1);
  m_behaviorTree.attachComposite(6, 15, 3);
  m_behaviorTree.attachComposite(15, 16, 0);
  m_behaviorTree.attachComposite(15, 17, 1);
  m_behaviorTree.attachComposite(6, 18, 4);
  m_behaviorTree.attachComposite(6, 19, 5);
}

void AIAgentField::cleanup(GfComPropertyPc &property) {
  m_behaviorTree.cleanup();
  fw::NaviManager *manager = fw::NaviManager::get();
  navi::NvmshAcObj *object = unknown00;
  if (manager != nullptr && object != nullptr) {
    manager->releaseObject(object);
    unknown00 = nullptr;
  }
}

void AIAgentField::onActivate(GfComPropertyPc &property) {
  if (unknown00 != nullptr) {
    unknown00->unknown10 |= 2;
  }
}

void AIAgentField::onDeactivate(GfComPropertyPc &property) {
  if (unknown00 != nullptr) {
    unknown00->unknown10 &= ~2;
  }
}

void AIAgentField::update(const fw::UpdateInfo &info, GfComPropertyPc &property) {
  property.unknown60.unknown00 = 0.0f;
  property.unknown60.unknown04 = 0.0f;
  property.unknown60.unknown08.clear();
  BlackBoardField *blackBoard = m_behaviorTree.unknown001<BlackBoardField>();
  blackBoard->m_comPropertyPc = &property;
  blackBoard->unknown10 = unknown00;
  blackBoard->unknown18 = &info;
  GfGamePlayerFormation *formation = GfGamePlayerFormation::get();
  u32 leaderId = formation->unknown1a0[property.unknown38].unknown00;
  bool isLeaderMoving = false;
  if (leaderId != PLAYER_ID_UNKNOWN_4294967295) {
    GfObj *obj = GfObjUtil::getObj(formation->unknown1a0[leaderId].m_playerHandle);
    if (obj != nullptr) {
      GfComPropertyPc *leader = obj->getComponent<GfComPropertyPc>();
      if (leader != nullptr) {
        const mm::Vec3 &velocity = leader->unknown80;
        f32 lengthSq = velocity.x * velocity.x + velocity.y * velocity.y + velocity.z * velocity.z;
        if (leader->unknownc0 > 0.0f || lengthSq > 0.0f) {
          isLeaderMoving = true;
        }
      }
    }
  }
  blackBoard->unknown200.set(10, isLeaderMoving);
  if (blackBoard->unknown200.test(4)) {
    // Inferred role: wall offsets of the buddies, one per player id pair; original name unknown.
    static const mm::Vec3 unknown001[] = {mm::Vec3(-3.0f, 0.0f, -2.0f), mm::Vec3(3.0f, 0.0f, -3.0f), mm::Vec3(-3.0f, 0.0f, -4.0f)};
    const mm::Vec3 &offset = unknown001[property.unknown38 / 2];
    const mm::Vec3 &up = mm::Vec3::unitY;
    mm::Vec3 front(-blackBoard->unknown70.normal.x, -blackBoard->unknown70.normal.y, -blackBoard->unknown70.normal.z);
    mm::Vec3 side(up.y * front.z - up.z * front.y, up.z * front.x - up.x * front.z, up.x * front.y - up.y * front.x);
    mm::Vec3 rotated(offset.x * side.x + offset.y * up.x + offset.z * front.x + 0.0f,
                     offset.x * side.y + offset.y * up.y + offset.z * front.y + 0.0f,
                     offset.x * side.z + offset.y * up.z + offset.z * front.z + 0.0f);
    mm::Vec3 target = blackBoard->unknown60 + rotated;
    if (fw::NaviUtil::testNaviStraightLine(blackBoard->unknown1f0, property.unknown160.unknown00, target, 1.0f, 3.0f) == 0) {
      blackBoard->unknown1f0 = property.unknown160.unknown00;
    }
  }
  m_behaviorTree.execute();
  blackBoard->unknown10 = nullptr;
  blackBoard->unknown18 = nullptr;
  blackBoard->m_comPropertyPc = nullptr;
}

bool AIAgentField::recieveMessage(GfComPropertyPc &property, fw::MessageObject *sender, fw::Message &message) {
  BlackBoardField *blackBoard = m_behaviorTree.unknown001<BlackBoardField>();
  blackBoard->m_comPropertyPc = &property;
  blackBoard->unknown10 = unknown00;
  blackBoard->unknown18 = nullptr;
  bool result = false;
  switch (message.unknown00) {
  case 0x100000f:
    procMsgPcFieldNotifyWall(sender, static_cast<MsgPcFieldNotifyWall &>(message));
    result = true;
    break;
  case MSG_PC_FIELD_NOTIFY_UNKNOWN_16777234:
    procMsgPcFieldNotifyWallJumpStart(sender, static_cast<MsgPcFieldNotifyWallJumpStart &>(message));
    result = true;
    break;
  case MSG_PC_FIELD_NOTIFY_UNKNOWN_16777237:
    procMsgPcFieldHighJump(sender, static_cast<MsgPcFieldNotifyHighJump &>(message));
    result = true;
    break;
  case MSG_PC_FIELD_NOTIFY_UNKNOWN_16777239:
    procMsgPcFieldNotifyWaterWarp(sender, static_cast<MsgPcFieldNotifyWaterWarp &>(message));
    result = true;
    break;
  case MSG_PC_FIELD_NOTIFY_UNKNOWN_16777247:
    procMsgPcFieldNotifyWaterWarpBuddy(sender, static_cast<MsgPcFieldNotifyWaterWarpBuddy &>(message));
    result = true;
    break;
  }
  blackBoard->unknown10 = nullptr;
  blackBoard->unknown18 = nullptr;
  blackBoard->m_comPropertyPc = nullptr;
  return result;
}

void AIAgentField::procMsgPcFieldNotifyWall(fw::MessageObject *sender, MsgPcFieldNotifyWall &message) {
  BlackBoardField *blackBoard = m_behaviorTree.unknown001<BlackBoardField>();
  switch (message.unknown50) {
  case 0:
    blackBoard->unknown200.set(5, false);
    blackBoard->unknown200.set(4, true);
    if (!blackBoard->m_comPropertyPc->m_propertyField.unknown10_4) {
      blackBoard->unknown70 = message.unknown10;
      blackBoard->unknown60 = message.m_transform.unknown00;
    }
    break;
  case 1:
    blackBoard->unknown200.set(4, false);
    blackBoard->unknown90 = message.m_transform.unknown00;
    blackBoard->unknowna0.clear();
    break;
  case 2:
    blackBoard->unknown200.set(4, false);
    blackBoard->unknown200.set(5, true);
    blackBoard->unknowna0.clear();
    break;
  case 3:
    if (blackBoard->unknowna0.full()) {
      blackBoard->unknowna0.pop_back();
    }
    blackBoard->unknowna0.unknown001(message.m_transform);
    break;
  }
}

void AIAgentField::procMsgPcFieldHighJump(fw::MessageObject *sender, MsgPcFieldNotifyHighJump &message) {
  BlackBoardField *blackBoard = m_behaviorTree.unknown001<BlackBoardField>();
  GfComPropertyPc *property = blackBoard->m_comPropertyPc;
  if (property->m_propertyField.unknown10_2) {
    const MsgPcFieldNotifyBigJump *info = message.m_msgPcFieldNotifyBigJump;
    fw::Transform transform;
    transform.unknown00 = info->unknown10;
    f32 angle = info->unknown20 * 0.5f;
    transform.unknown10.unknown001(angle);
    GfGamePlayerFormation *formation = GfGamePlayerFormation::get();
    MsgPcFieldNotifyBigJump bigJump;
    bigJump = *info;
    formation->calcTargetTransform(transform, property->unknown38, &bigJump.unknown10);
    property->m_propertyField.setBigJumpInfo(&bigJump);
    const fw::ParamList *paramList = unknown88.operator->();
    const ForceWarpAiParam *param = paramList->unknown0c > 6 ? static_cast<const ForceWarpAiParam *>(paramList->unknown10[6].param) : nullptr;
    blackBoard->unknown200.set(6);
    blackBoard->unknown204 = param->baseWaitTime + ml::mtRandf1() * param->waitTimeRange;
  }
}

void AIAgentField::procMsgPcFieldNotifyWaterWarp(fw::MessageObject *sender, MsgPcFieldNotifyWaterWarp &message) {
  BlackBoardField *blackBoard = m_behaviorTree.unknown001<BlackBoardField>();
  GfComPropertyPc *property = blackBoard->m_comPropertyPc;
  GfPropertyField &field = property->m_propertyField;
  if (property->unknown110_5) {
    const MsgPcFieldNotifyWarp *info = message.m_msgPcFieldNotifyWarp;
    fw::Transform transform;
    transform.unknown00 = info->unknown10;
    f32 angle = info->unknown20 * 0.5f;
    transform.unknown10.unknown001(angle);
    GfGamePlayerFormation *formation = GfGamePlayerFormation::get();
    MsgPcFieldNotifyWarp warp;
    warp = *info;
    formation->calcTargetTransform(transform, property->unknown38, &warp.unknown10);
    field.setWarpInfo(&warp);
    const fw::ParamList *paramList = unknown88.operator->();
    const ForceWarpAiParam *param = paramList->unknown0c > 7 ? static_cast<const ForceWarpAiParam *>(paramList->unknown10[7].param) : nullptr;
    blackBoard->unknown200.set(7);
    blackBoard->unknown204 = param->baseWaitTime + ml::mtRandf1() * param->waitTimeRange;
  }
}

void AIAgentField::procMsgPcFieldNotifyWaterWarpBuddy(fw::MessageObject *sender, MsgPcFieldNotifyWaterWarpBuddy &message) {
  BlackBoardField *blackBoard = m_behaviorTree.unknown001<BlackBoardField>();
  GfComPropertyPc *property = blackBoard->m_comPropertyPc;
  GfPropertyField &field = property->m_propertyField;
  if (property->unknown110_5) {
    const MsgPcFieldNotifyWarp *info = message.m_msgPcFieldNotifyWarp;
    fw::Transform transform;
    transform.unknown00 = info->unknown10;
    f32 angle = info->unknown20 * 0.5f;
    transform.unknown10.unknown001(angle);
    GfGamePlayerFormation *formation = GfGamePlayerFormation::get();
    MsgPcFieldNotifyWarp warp;
    warp = *info;
    formation->calcTargetTransform(transform, property->unknown38, &warp.unknown10);
    field.setWarpInfo(&warp);
    const fw::ParamList *paramList = unknown88.operator->();
    const ForceWarpAiParam *param = paramList->unknown0c > 7 ? static_cast<const ForceWarpAiParam *>(paramList->unknown10[7].param) : nullptr;
    blackBoard->unknown200.set(9);
    blackBoard->unknown204 = param->baseWaitTime + ml::mtRandf1() * param->waitTimeRange;
  }
}

void AIAgentField::procMsgPcFieldNotifyWallJumpStart(fw::MessageObject *sender, MsgPcFieldNotifyWallJumpStart &message) {
  BlackBoardField *blackBoard = m_behaviorTree.unknown001<BlackBoardField>();
  if (blackBoard->m_comPropertyPc->m_propertyField.unknown10_4) {
    blackBoard->m_comPropertyPc->m_propertyField.setWallJump(message.m_msgPcFieldNotifyWallJump);
    blackBoard->unknown200.set(8);
  }
}

const mm::mtl::RTTI *BlackBoardField::getRTTI() const { return &m_rtti; }

} // namespace pc
} // namespace gf
