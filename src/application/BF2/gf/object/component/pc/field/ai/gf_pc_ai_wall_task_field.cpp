#include "gf/object/component/pc/field/ai/gf_pc_ai_wall_task_field.h"

#include "fw/fw_param_manager.h"
#include "fw/fw_transform.h"
#include "fw/fw_update_info.h"
#include "gf/gf_allocator.h"
#include "gf/object/component/pc/field/gf_pc_param_field.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_agent_util_field.h"
#include "gf/object/component/pc/gf_pc_property_field.h"
#include "gf/object/component/pc/gf_pc_state_util.h"
#include "gf/object/gf_obj.h"
#include "mm/mm_std_base.h"
#include "mm_math/mm_vec2.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/bitflag.h"
#include "mm_mtl/rtti.h"

namespace gf {
namespace pc {

void TaskFieldWallPrepare::onEvent(ai::BlackBoard &blackBoard, const ai::Event &event) {
  BlackBoardField *pBB = mm::mtl::dynamicCast<BlackBoardField>(&blackBoard);
  // __LINE__ must be 23 as in the original file: it is the line argument of the assert.
#line 23
  MM_ASSERT(pBB);
  switch (event.unknown00) {
  case ai::UNKNOWN002_UNKNOWN_1:
    onChangeActivate(*pBB, static_cast<const ai::ActivateEvent &>(event));
    break;
  case ai::UNKNOWN002_UNKNOWN_2:
    onCreate(*pBB, static_cast<const ai::CreateEvent &>(event));
    break;
  case ai::UNKNOWN002_UNKNOWN_4:
    onDestroy(*pBB, static_cast<const ai::DestroyEvent &>(event));
    break;
  }
}

void TaskFieldWallPrepare::onChangeActivate(BlackBoardField &blackBoard, const ai::ActivateEvent &event) {
  if (!event.unknown04) {
    unknown40.unknown00 = &blackBoard;
    unknown38->setState(0);
    unknown40.unknown00 = nullptr;
  }
}

void TaskFieldWallPrepare::onCreate(BlackBoardField &blackBoard, const ai::CreateEvent &event) {
  // __LINE__ must be 83 as in the original file: it is the line argument of the allocation.
#line 83
  unknown38.reset(new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ai::Fsm(getAllocator(ALLOCATOR_UNKNOWN_0)));
  unknown38->beginSetup(&unknown40, 3);
  unknown38->registerState<StateFieldWallAiWait>(0);
  unknown38->registerState<StateFieldWallAiPrepare>(1);
  unknown38->registerState<StateFieldWallAiAdsorption>(2);
  unknown38->endSetup();
  unknown40.unknown00 = &blackBoard;
  unknown38->setState(0);
  unknown40.unknown00 = nullptr;
}

void TaskFieldWallPrepare::onDestroy(BlackBoardField &blackBoard, const ai::DestroyEvent &event) {
  unknown40.unknown00 = &blackBoard;
  if (unknown38) {
    unknown38->cleanup();
  }
  unknown40.unknown00 = nullptr;
  unknown38.reset();
}

bool TaskFieldWallPrepare::testCondition(const BlackBoardField &blackBoard) {
  bool isRequest = blackBoard.unknown200.test(4);
  return !blackBoard.unknown08->unknown310.unknown10_4 && isRequest;
}

void TaskFieldWallPrepare::update(BlackBoardField &blackBoard) {
  unknown40.unknown00 = &blackBoard;
  unknown38->update(blackBoard.unknown18);
  unknown40.unknown00 = nullptr;
}

bool TaskFieldWallFollow::testCondition(const BlackBoardField &blackBoard) { return blackBoard.unknown08->unknown310.unknown10_5; }

void TaskFieldWallFollow::update(BlackBoardField &blackBoard) {
  GfComPropertyPc *property = blackBoard.unknown08;
  fw::Transform transform;
  if (AgentUtilField::getWallFollowTransform(blackBoard, &transform)) {
    mm::Vec2 input = AgentUtilField::calcFollowWallInput(transform.unknown00, *property);
    if (AgentUtilField::isEnableWallMove(*property, input)) {
      property->unknown60.unknown00 = input.x;
      property->unknown60.unknown04 = input.y;
      return;
    }
  }
  if (AgentUtilField::isWallEndMove(blackBoard)) {
    AgentUtilField::setFollowWallEndInput(blackBoard.unknown90, *property);
  } else {
    AgentUtilField::setIdleInput(*property);
  }
}

void TaskFieldWallFall::onEvent(ai::BlackBoard &blackBoard, const ai::Event &event) {
  BlackBoardField *pBB = mm::mtl::dynamicCast<BlackBoardField>(&blackBoard);
  // __LINE__ must be 165 as in the original file: it is the line argument of the assert.
#line 165
  MM_ASSERT(pBB);
  switch (event.unknown00) {
  case ai::UNKNOWN002_UNKNOWN_1:
    onChangeActivate(*pBB, static_cast<const ai::ActivateEvent &>(event));
    break;
  case ai::UNKNOWN002_UNKNOWN_2:
    onCreate(*pBB, static_cast<const ai::CreateEvent &>(event));
    break;
  }
}

void TaskFieldWallFall::onChangeActivate(BlackBoardField &blackBoard, const ai::ActivateEvent &event) {
  if (!event.unknown04) {
    unknown38 = 0.0f;
  }
}

void TaskFieldWallFall::onCreate(BlackBoardField &blackBoard, const ai::CreateEvent &event) { unknown38 = 0.0f; }

bool TaskFieldWallFall::testCondition(const BlackBoardField &blackBoard) { return blackBoard.unknown200.test(5) && blackBoard.unknown08->unknown310.unknown10_4; }

void TaskFieldWallFall::update(BlackBoardField &blackBoard) {
  unknown38 += blackBoard.unknown18->unknown04;
  GfComPropertyPc *property = blackBoard.unknown08;
  const WallAiParam *param = AgentUtilField::getAIParamAdapter(*property, PARAM_ID_FIELD_AI_UNKNOWN_5).get<WallAiParam>();
  if (unknown38 >= param->fallDelay) {
    property->unknown60.unknown08.set(3);
  }
}

bool TaskFieldWallEscape::testCondition(const BlackBoardField &blackBoard) {
  GfComPropertyPc *property = blackBoard.unknown08;
  const WallAiParam *param = AgentUtilField::getAIParamAdapter(*property, PARAM_ID_FIELD_AI_UNKNOWN_5).get<WallAiParam>();
  if (!property->unknown310.unknown10_4) {
    return false;
  }

  return AgentUtilField::calcParentPlayerPush(*property, property->unknown160.unknown00, param->escapeRange, &unknown40);
}

void TaskFieldWallEscape::update(BlackBoardField &blackBoard) {
  GfComPropertyPc *property = blackBoard.unknown08;
  property->unknown60.unknown04 = property->unknown290.x * unknown40.x + property->unknown290.y * unknown40.y + property->unknown290.z * unknown40.z >= 0.0f ? 1.0f : -1.0f;
  property->unknown60.unknown00 = property->unknown2d0.x * unknown40.x + property->unknown2d0.y * unknown40.y + property->unknown2d0.z * unknown40.z >= 0.0f ? 1.0f : -1.0f;
}

bool TaskFieldWallJumpWait::testCondition(const BlackBoardField &blackBoard) { return blackBoard.unknown200.test(8); }

void TaskFieldWallJumpWait::update(BlackBoardField &blackBoard) {
  GfComPropertyPc *property = blackBoard.unknown08;
  if (!AgentUtilField::existNearChimbPlayer(*property, property->unknown310.getWallJumpInfo()->unknown10) && !AgentUtilField::isWallJumpAnyPlayer()) {
    MsgPcFieldWallJump message;
    GfObj *obj = static_cast<GfObj *>(property->unknown08);
    obj->sendMessage(obj, message);
    if (message.unknown08) {
      blackBoard.unknown200.set(8, false);
    }
  }
}

} // namespace pc
} // namespace gf
