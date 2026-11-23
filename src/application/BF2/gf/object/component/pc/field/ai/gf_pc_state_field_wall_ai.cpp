#include "gf/object/component/pc/field/ai/gf_pc_state_field_wall_ai.h"

#include <math.h>

#include "fw/fw_transform.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_agent_util_field.h"
#include "gf/object/component/pc/gf_pc_ai_agent_field.h"
#include "gf/object/component/pc/gf_pc_property_field.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"
#include "mm_math/mm_vec3.h"
#include "navi/nvmsh_ac_obj.h"

namespace gf {
namespace pc {

void StateFieldWallAiWait::update(WallAiContextField *context, const fw::UpdateInfo &info) {
  BlackBoardField *blackBoard = context->m_blackBoardField;
  GfComPropertyPc *property = blackBoard->m_comPropertyPc;
  mm::Vec3 preparePosition = StateUtilField::calcWallPreparePosition(*property, blackBoard->unknown60, blackBoard->unknown70);
  if (StateUtilField::isEnableWallAdsorptionStart(*property, blackBoard->unknown60, preparePosition)) {
    reqState(2);
  } else if (StateUtilField::isEnableWallPrepare(*property)) {
    reqState(1);
  } else {
    AgentUtilField::setIdleInput(*property);
  }
}

void StateFieldWallAiPrepare::enter(WallAiContextField *context, ai::State *previous) { setNavi(context); }

void StateFieldWallAiPrepare::setNavi(WallAiContextField *context) {
  BlackBoardField *blackBoard = context->m_blackBoardField;
  GfComPropertyPc *property = blackBoard->m_comPropertyPc;
  navi::NvmshAcObj *naviObject = blackBoard->unknown10;
  naviObject->setBeginPos(property->unknown160.unknown00);
  mm::Vec3 preparePosition = StateUtilField::calcWallPreparePosition(*property, blackBoard->unknown60, blackBoard->unknown70);
  naviObject->setEndPos(preparePosition);
}

void StateFieldWallAiPrepare::update(WallAiContextField *context, const fw::UpdateInfo &info) {
  BlackBoardField *blackBoard = context->m_blackBoardField;
  GfComPropertyPc *property = blackBoard->m_comPropertyPc;
  mm::Vec3 preparePosition = StateUtilField::calcWallPreparePosition(*property, blackBoard->unknown60, blackBoard->unknown70);
  if (StateUtilField::isEnableWallAdsorptionStart(*property, blackBoard->unknown60, preparePosition)) {
    reqState(2);
    return;
  }

  if (StateUtilField::isWallPreparePosition(*property, preparePosition)) {
    AgentUtilField::setIdleInput(*property);
  } else {
    navi::NvmshAcObj *naviObject = blackBoard->unknown10;
    mm::Vec3 diff(preparePosition.x - property->unknown160.unknown00.x, 0.0f, preparePosition.z - property->unknown160.unknown00.z);
    AgentUtilField::setFollowInput(sqrtf(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z), naviObject, *property);
  }
  setNavi(context);
}

void StateFieldWallAiAdsorption::enter(WallAiContextField *context, ai::State *previous) {
  setNavi(context);
  context->m_blackBoardField->m_comPropertyPc->m_propertyField.unknown10_3 = true;
}

void StateFieldWallAiAdsorption::setNavi(WallAiContextField *context) {
  BlackBoardField *blackBoard = context->m_blackBoardField;
  const mm::Vec3 &position = blackBoard->m_comPropertyPc->unknown160.unknown00;
  navi::NvmshAcObj *naviObject = blackBoard->unknown10;
  naviObject->setBeginPos(position);
  naviObject->setEndPos(blackBoard->unknown60);
}

void StateFieldWallAiAdsorption::leave(WallAiContextField *context, ai::State *next) { context->m_blackBoardField->m_comPropertyPc->m_propertyField.unknown10_3 = false; }

void StateFieldWallAiAdsorption::update(WallAiContextField *context, const fw::UpdateInfo &info) {
  BlackBoardField *blackBoard = context->m_blackBoardField;
  GfComPropertyPc *property = blackBoard->m_comPropertyPc;
  navi::NvmshAcObj *naviObject = blackBoard->unknown10;
  mm::Vec3 diff(blackBoard->unknown60.x - property->unknown160.unknown00.x, 0.0f, blackBoard->unknown60.z - property->unknown160.unknown00.z);
  AgentUtilField::setFollowInput(sqrtf(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z), naviObject, *property);
  setNavi(context);
}

} // namespace pc
} // namespace gf
