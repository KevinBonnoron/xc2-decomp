#pragma once
#include "framework/object/component_object.h"
#include "framework/object/updatable_object.h"
#include "fw/fw_param_manager.h"
#include "gf/object/component/behavior/gf_com_behavior.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_agent.h"
#include "gf/object/component/pc/gf_pc_ai_agent.h"
#include "gf/object/component/pc/gf_pc_ai_agent_field.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/rtti.h"
#include "mm_mtl/unique_ptr.h"
#include "types.h"

namespace fw {
struct Transform;
} // namespace fw

namespace mm {
struct Vec2;
struct Vec3;
} // namespace mm

namespace navi {
class NvmshAcObj;
} // namespace navi

namespace gf {
namespace pc {

// Entries of the field AI param list, in the order of gf::pc::createReflectionFieldAI; the enumerator names are unknown.
enum PARAM_ID_FIELD_AI {
  PARAM_ID_FIELD_AI_UNKNOWN_0 = 0, // Inferred role: "follow_main" (FollowMainPcParam).
  PARAM_ID_FIELD_AI_UNKNOWN_1 = 1, // Inferred role: "follow_water_main" (FollowMainPcParam).
  PARAM_ID_FIELD_AI_UNKNOWN_2 = 2, // Inferred role: "follow_buddy" (FollowBuddyPcParam).
  PARAM_ID_FIELD_AI_UNKNOWN_3 = 3, // Inferred role: "follow_water_buddy" (FollowBuddyPcParam).
  PARAM_ID_FIELD_AI_UNKNOWN_4 = 4, // Inferred role: "ai_jump" (JumpAIParam).
  PARAM_ID_FIELD_AI_UNKNOWN_5 = 5, // Inferred role: "wall_ai" (WallAiParam).
  PARAM_ID_FIELD_AI_UNKNOWN_6 = 6, // Inferred role: "high_jump_ai" (ForceWarpAiParam).
  PARAM_ID_FIELD_AI_UNKNOWN_7 = 7, // Inferred role: "water_warp_ai" (ForceWarpAiParam).
};

class AgentUtilField {
public:
  static void setIdleInput(GfComPropertyPc &property);
  static f32 setFollowInput(f32 distance, navi::NvmshAcObj *naviObject, GfComPropertyPc &property);
  static mm::Vec2 calcFollowWallInput(const mm::Vec3 &position, GfComPropertyPc &property);
  static fw::ParamAdapter getAIParamAdapter(GfComPropertyPc &property, PARAM_ID_FIELD_AI id);
  static void setFollowWallEndInput(const mm::Vec3 &position, GfComPropertyPc &property);
  static bool getWallFollowTransform(const BlackBoardField &blackBoard, fw::Transform *transform);
  static bool isWallEndMove(const BlackBoardField &blackBoard);
  static bool calcParentPlayerPush(GfComPropertyPc &property, const mm::Vec3 &position, f32 range, mm::Vec3 *push);
  static bool isEnableWallMove(GfComPropertyPc &property, const mm::Vec2 &input);
  static bool existNearChimbPlayer(GfComPropertyPc &property, const mm::Vec3 &position);
  static bool isWallJumpAnyPlayer();

  // Inferred role: field AI param list of the AI agent of the player; original name unknown.
  static const mm::mtl::IntrusivePtr<fw::ParamList> &unknown001(GfComPropertyPc &property) {
    GfComBehaviorPc *behavior = mm::mtl::dynamicCast<GfComBehaviorPc>(property.unknown08->unknown38[GfComBehavior::COMPONENT_INDEX]);
    AIAgent *agent = mm::mtl::dynamicCast<AIAgent>(behavior->unknown98.get());
    return agent->unknown10.unknown88;
  }
};

} // namespace pc
} // namespace gf
